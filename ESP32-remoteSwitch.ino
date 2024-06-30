// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "R1";
const char* password = "raspberrypi";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

String outputfanstate = "off";
String outputlightstate = "off";
// Assign output variables to GPIO pins
const int Fan = 33;
const int Light = 04;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(Fan, OUTPUT);
  pinMode(Light, OUTPUT);
  // Set outputs to LOW
  digitalWrite(Fan, LOW);
  digitalWrite(Light, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /Fan/on") >= 0) {
              Serial.println("GPIO 33 on");
              outputfanstate = "on";
              digitalWrite(Fan, HIGH);
            } else if (header.indexOf("GET /Fan/off") >= 0) {
              Serial.println("GPIO 33 off");
              outputfanstate = "off";
              digitalWrite(Fan, LOW);
            } else if (header.indexOf("GET /Light/on") >= 0) {
              Serial.println("GPIO 04 on");
              outputlightstate = "on";
              digitalWrite(Light, HIGH);
            } else if (header.indexOf("GET /Light/off") >= 0) {
              Serial.println("GPIO 04 off");
              outputlightstate = "off";
              digitalWrite(Light, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>IETE CBE  ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 33  
            client.println("<p>GPIO Fan - State " + outputfanstate + "</p>");
            // If the outputfantate is off, it displays the ON button       
            if (outputfanstate=="off") {
              client.println("<p><a href=\"/Fan/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Fan/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 04  
            client.println("<p>GPIO Light - State " + outputlightstate + "</p>");
            // If the outputlightstate is off, it displays the ON button       
            if (outputlightstate=="off") {
              client.println("<p><a href=\"/Light/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/Light/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
