#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <serial/SerialPort.h>
#include "oled.h"
#include "fonts.h"

using namespace std;

SerialPort gnss;
I2C i2c1(1);
Oled lcd(&i2c1);

double lat;
double lon;
double alt;
int fix_mode;
int timeout;
char msg[32] = {0};
char buffer[1024] = {0};

void handle_Ctrl_C (int s) {
    try {
        cout << "Terminating..." << endl;
        gnss.writeString("unlog\r\n");
        gnss.closeDevice();
    } catch (...) {
       cout << "error while closing..." << endl;
    }

    exit(0);
}


vector<string> stringSplit(const string &s, const char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

template <class Type>
Type stringToNum(const string &str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

double convertNmeaToDouble(const std::string &val, const std::string &dir) {
    int dot = val.find('.');
    std::string degree = val.substr(0, dot-2);
    std::string minute = val.substr(dot-2);

    double ret = stringToNum<double>(degree) + stringToNum<double>(minute)/60;

    if (dir == "S" || dir == "W") {
        ret = -ret;
    }

    return ret;
}

void Oled_msg(char *msg) {
    lcd.clear();
    lcd.text(0, 26, msg, Oled::DOUBLE_SIZE);
    lcd.display();
}

void Oled_pos(double &lat, double &lon, double &alt, int &fix_mode) {
    lcd.clear();

    snprintf(msg, 32, "%10.6f", lat);
    lcd.text(8, 4, msg /*, Oled::DOUBLE_SIZE*/);

    snprintf(msg, 32, "%10.6f", lon);
    lcd.text(8, 4+12, msg /*, Oled::DOUBLE_SIZE*/);

    snprintf(msg, 32, "%10.6f", alt);
    lcd.text(8, 4+24, msg /*, Oled::DOUBLE_SIZE */);

    switch(fix_mode) {
        case 0:
            snprintf(msg, 32, "%s", "INVALID");
            break;
        case 1:
            snprintf(msg, 32, "%s", "SINGLE ");
            break;
        case 2:
            snprintf(msg, 32, "%s", "DIFFPOS");
            break;
        case 4:
            snprintf(msg, 32, "%s", "RTK-FIX");
            break;
        case 5:
            snprintf(msg, 32, "%s", "RTK-FLT");
            break;
        case 6:
            snprintf(msg, 32, "%s", "INSPOS ");
            break;
        case 7:
            snprintf(msg, 32, "%s", "BASEFIX");
            break;
        default:
            snprintf(msg, 32, "%s", "-------");
            break;
    }
    lcd.text(4, 8+36, msg, Oled::DOUBLE_SIZE);

    if (fix_mode != 7) {
        snprintf(msg, 32, "%3d", timeout);
        lcd.text(8*12, 8+36, msg /*, Oled::DOUBLE_SIZE */);
    }

    lcd.display();
}

int main (/*int argc, char *argv[]*/) {

    // register handler
    struct sigaction sigHandler;
    sigHandler.sa_handler = handle_Ctrl_C;
    sigemptyset(&sigHandler.sa_mask);
    sigHandler.sa_flags = 0;
    sigaction(SIGINT, &sigHandler, NULL);

    // start OLED
    lcd.init();
    lcd.text(0, 26, "Initializing...");
    lcd.display();

    // talk to GNSS module
    if (gnss.openDevice("/dev/ttyS0", 115200) != 1) {
        snprintf(msg, 32, "%s", "ERROR!");
        Oled_msg(msg);
        return -1;
    }

    snprintf(msg, 32, "%s", "GNSS OK!");
    Oled_msg(msg);

RESTART:

    timeout = 120;

    // request base mode
    gnss.writeString("unlog\r\n");
    gnss.writeString("mode base time 60\r\n");
    gnss.writeString("gngga 1\r\n");
    gnss.flushReceiver();

    while(1) {
       int n = gnss.readString(buffer, '\n', 1024);
       if (n > 0) {
            string line = string(buffer, n);
            cout << line;

            // $GNGGA,090031.00,2057.59811809,N,10546.17292292,E,1,18,2.2,16.4378,M,-28.2478,M,,*64
            vector<string> message = stringSplit(line, ',');
            if (message[0] == "$GNGGA" && message[2] != "") {
                lat = convertNmeaToDouble(message[2], message[3]);
                lon = convertNmeaToDouble(message[4], message[5]);
                alt = stringToNum<double>(message[9]);
                fix_mode = stringToNum<int>(message[6]);

                Oled_pos(lat, lon, alt, fix_mode);

                if (fix_mode == 7) {
                    cout << "Base fixed at " << lat << ", " << lon << ", " << alt << endl;
                    break;
                }
            } else {
                snprintf(msg, 32, "WAIT %d", timeout);
                Oled_msg(msg);
            }

            timeout--;
            if (timeout == 0) {
                goto RESTART;
            }
       }
    }

    gnss.writeString("unlog\r\n");

    // Stream RTCM3 to local ntripcaster
    // password = test
    // mountpoint = test

    char cmd[1024] =
    "/home/pi/base/str2str "
        "-in serial://ttyS0:115200 "
        "-out ntrips://:test@localhost:2101/test "
        "-c /home/pi/base/gnss.cmd ";

    cout << "Run:" << endl;
    cout << cmd << endl;
    system(cmd);

    // Close the serial device
    cout << "Closing..." << endl;
    gnss.writeString("unlog\r\n");
    gnss.closeDevice();

    return 0;
}


