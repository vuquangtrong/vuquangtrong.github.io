#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Set these to your desired credentials.
const char *ssid = "ESP32-AP";
const char *password = "password";

// Run a webser at port 80
WiFiServer server(80);

// A sample webpage show a solid background color
enum BG_COLOR {
  NONE,
  RED,
  GREEN
};

BG_COLOR bg_color = NONE;

const char* red = "red";
const char* green = "green";
const char* none = "initial";

const char *get_bg_color() {
  switch(bg_color) {
    case RED:
      return red;
    case GREEN:
      return green;
    default:
      return none;
  }
}

void send_response(WiFiClient *client) {
  // send Header with OK response
  client->println(
    "HTTP/1.1 200 OK\n"
    "Content-type:text/html\n"
  );

  // send Content
  client->println(
    "<html>"
      "<body "
        "style=\""
          "background-color:" + String(get_bg_color()) + ";"
          "text-align:center;"
      "\">"
        "<a href=\"/\"><button>NONE</a></button>"
        "<a href=\"/red\"><button>RED</a></button>"
        "<a href=\"/green\"><button>GREEN</a></button>"
      "</body>"
    "</html>"
  );
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  
  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);

  // Show AP address
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Start Web Server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New Client.");
    // string to hold client HTTP request
    String clientString = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);

        // newline char means end of string
        if (c == '\n') {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (clientString.length() == 0) {
            send_response(&client);
            // break out of the while loop:
            break;
          } else { // if you got a newline, then process the completed string
            Serial.println(clientString);
            // Check to see if the client request was "GET /red" or "GET /green":
            if (clientString.startsWith("GET /red ")) {
              Serial.println("RED");
              bg_color = RED;
            } else if (clientString.startsWith("GET /green ")) {
              Serial.println("GREEN");
              bg_color = GREEN;
            } else if (clientString.startsWith("GET / ")) {
              Serial.println("NONE");
              bg_color = NONE;
            }
            clientString = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          clientString += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
