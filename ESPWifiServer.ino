/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>

const char* ssid = "mywifi";
const char* password = "password";
IPAddress ip(192, 168, 1, xx); // where xx is the desired IP Address
IPAddress gateway(192, 168, 1, 254); // set gateway to match your wifi network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your wifi network

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
int status = LOW;
const int pin = 2;
void setup() {
  Serial.begin(115200);
  delay(100);

  // prepare GPIO2
  pinMode(pin, OUTPUT);
  digitalWrite(pin, status);


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(3000);
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('$');
  Serial.println(req);
  client.flush();

  // Match the request

  if (req.indexOf("status") != -1 || req.indexOf("/status") != -1)
    Serial.println("Switch is: "+ status);
  else if (req.indexOf("on") != -1 || req.indexOf("/on") != -1)
    status = HIGH;
  else if (req.indexOf("off") != -1 || req.indexOf("/off") != -1)
    status = LOW;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  digitalWrite(pin, status);
  // Prepare the response
  String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nSwitch is now ";
  response += status;
  response += "</html>\n";
  // Send the response to the client
  client.print(response);
  client.flush();

  delay(1);
  Serial.println("Client disonnected"+ status);

  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
