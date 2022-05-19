#include <WiFi.h>

// Set these to your desired credentials.
const char *ssid = "HomeSweetHome";
const char *password = "password";

// URI
const char *host = "192.168.5.94";
const int   port = 80;
const char *request_time = "/time";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // connect to the WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Create a client
  WiFiClient client;
  // connect to the host using TCP
  if (!client.connect(host, port)) {
    Serial.println("HTTP connection failed");
    return;
  }

  // send GET request to HTTP Webserver
  client.print(
    "GET " + String(request_time) + " HTTP/1.1\r\n" +
    "Host: " + String(host) + "\r\n" +
    "Connection: close\r\n" + 
    "\r\n"
    );

  // wait for response in 5s
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
    }
  }

  //
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
  }

  Serial.println();
}
