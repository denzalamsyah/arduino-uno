                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #include <ESP8266WiFi.h>

// Enter your wifi network name and Wifi Password
const char* ssid = "Culametan";
const char* password = "02092002";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// These variables store current output state of LED
String outputLED1 = "off";
String outputLED2 = "off";
String outputLED3 = "off";
String outputLED4 = "off";
String outputLED5 = "off";

// Assign output variables to GPIO pins
const int LED1 = 2;
const int LED2 = 0;
const int LED3= 4;
const int LED4 = 5;
const int LED5 = 16;



// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
Serial.begin(115200);
// Initialize the output variables as outputs
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3,OUTPUT);
pinMode(LED4,OUTPUT);
pinMode(LED5,OUTPUT);
// Set outputs to LOW
digitalWrite(LED1, LOW);
digitalWrite(LED2, LOW);
digitalWrite(LED3, LOW);
digitalWrite(LED4, LOW);
digitalWrite(LED5, LOW);

// Connect to Wi-Fi network with SSID and password
Serial.print("Menghubungkan ke ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
// Print local IP address and start web server
Serial.println("");
 Serial.println("Terhubungn..");

// memulai
 server.begin();
 Serial.println("Server siap");

// Print the IP address
 Serial.print("Masukan link ini pada browser: ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
}

void loop(){
WiFiClient client = server.available(); // Listen for incoming clients

if (client) { // If a new client connects,
Serial.println("Client Baru."); // print a message out in the serial port
String currentLine = ""; // make a String to hold incoming data from the client
currentTime = millis();
previousTime = currentTime;
while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
currentTime = millis(); 
if (client.available()) { // if there's bytes to read from the client,
char c = client.read(); // read a byte, then
Serial.write(c); // print it out the serial monitor
header += c;
if (c == '\n') { // if the byte is a newline character
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
if (header.indexOf("GET /2/on") >= 0) {
Serial.println("Lampu Menyala");
outputLED1 = "on";
digitalWrite(LED1, HIGH);
} else if (header.indexOf("GET /2/off") >= 0) {
Serial.println("Lampu Mati");
outputLED1 = "off";
digitalWrite(LED1, LOW);

} else if (header.indexOf("GET /0/on") >= 0) {
Serial.println("Musik Aktif");
outputLED2 = "on";
digitalWrite(LED2, HIGH);
} else if (header.indexOf("GET /0/off") >= 0) {
Serial.println("Musik Mati");
outputLED2 = "off";
digitalWrite(LED2, LOW);

} else if (header.indexOf("GET /4/on") >= 0) {
Serial.println("Fitur Keamanan Aktif");
outputLED3 = "on";
digitalWrite(LED3, HIGH);
} else if (header.indexOf("GET /4/off") >= 0) {
Serial.println("Fitur Keamanan Mati");
outputLED3 = "off";
digitalWrite(LED3, LOW);

} else if (header.indexOf("GET /5/on") >= 0) {
Serial.println("Sensor RainDrop Aktif");
outputLED4 = "on";
digitalWrite(LED4, HIGH);
} else if (header.indexOf("GET /5/off") >= 0) {
Serial.println("Sensor RainDrop Mati");
outputLED4 = "off";
digitalWrite(LED4, LOW);

} else if (header.indexOf("GET /16/on") >= 0) {
Serial.println("AC Aktif");
outputLED5 = "on";
digitalWrite(LED5, HIGH);
} else if (header.indexOf("GET /16/off") >= 0) {
Serial.println("AC Mati");
outputLED5 = "off";
digitalWrite(LED5, LOW);
}

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
// CSS to style the on/off buttons 
client.println("<style>html { font-family: Times New Roman; display: inline-block; margin: 0px auto; text-align: center;}");
client.println("body {background-color: #00ff00;}");
client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 100%;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 100%;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 100%;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 100%;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 100%;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
client.println(".buttonOff { background-color: #EAECEE; border-style: solid; border-color: #17202A; color: #17202A; padding: 16px 40px; border-radius: 100%;");
client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}</style></head>");

// Web Page Heading
client.println("<body><h1>E-Home</h1>");

// Display current state, and ON/OFF buttons for GPIO 2 LED1 
client.println("<p>Lampu " + outputLED1 + "</p>");
// If the outputLED1 is off, it displays the OFF button 
if (outputLED1=="off") {
client.println("<p><a href=\"/2/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/2/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
} 

// Display current state, and ON/OFF buttons for GPIO 0 LED2 
client.println("<p>Musik " + outputLED2 + "</p>");
// If the outputLED2 is off, it displays the OFF button 
if (outputLED2 =="off") {
client.println("<p><a href=\"/0/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/0/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
}
client.println("</body></html>");

// Display current state, and ON/OFF buttons for GPIO 4 LED3 
client.println("<p>Fitur Keamanan " + outputLED3 + "</p>");
// If the outputLED3 is off, it displays the OFF button 
if (outputLED3 =="off") {
client.println("<p><a href=\"/4/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/4/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
}
client.println("</body></html>");

// Display current state, and ON/OFF buttons for GPIO 5 LED4 
client.println("<p>Sensor RainDrop " + outputLED4 + "</p>");
// If the outputLED4 is off, it displays the OFF button 
if (outputLED4 =="off") {
client.println("<p><a href=\"/5/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/5/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
}
client.println("</body></html>");

// Display current state, and ON/OFF buttons for GPIO 16 LED5 
client.println("<p>AC " + outputLED5 + "</p>");
// If the outputLED5 is off, it displays the OFF button 
if (outputLED5 =="off") {
client.println("<p><a href=\"/16/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/16/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
}
client.println("</body></html>");

// The HTTP response ends with another blank line
client.println();
// Break out of the while loop
break;
} else { // if you got a newline, then clear currentLine
currentLine = "";
}
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
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
