#include <SPI.h>
#include <WiFiNINA.h>

//Establish pin names for ease of reference
//R/L (Right/Left) F/R (Forward/Reverse)
const int RF = 2;
const int RR = 3;
const int LF = 4;
const int LR = 5;

//set default connection status
int connectionStatus = WL_IDLE_STATUS;

//Variables for network id and password
char ssid[] = "ssid";
char pass[] = "password";

// server is a WiFi server to be hosted on port 80
WiFiServer server(80);

void setup() {
  //Setup serial monitor
  Serial.begin(9600);

  //Set motor pin modes
  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);

  //Check firmware (if the program SHOULD connect but doesnt, un-comment this and check for updates)
  //if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
    //Serial.print("Firmware needs an update.");
  //}

  //Connect to the network (if it says connecting more than once, it probably won't connect)
  while (connectionStatus != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(ssid);
    connectionStatus = WiFi.begin(ssid, pass);
    delay(10000); //10 sec delay before trying again
  }

  //Once connected start the server
  server.begin();

  //Print the servers IP address
  Serial.print("My IP is: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //creates a 'client' to send and recieve data
  WiFiClient client = server.available();

  //once there is a client, print to the serial monitor
  if (client) {
    Serial.print("we have connection!");
    
    //'currentLine' will store the incoming data from the client
    String currentLine = "";

    //while there is unread data from the client
    while (client.connected()) {
      
      //if the client has data available to read
      if (client.available()) {
        
        //read the incoming data
        char input = client.read();
        
        //write the data on the serial monitor
        Serial.write("Recieving: " + input);
        
        //if the client hasn't sent data, display the webpage
        if (input == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Click <a href=\"/F\">here</a> move forward<br>");
            client.print("Click <a href=\"/B\">here</a> move backwards<br>");
            client.print("Click <a href=\"/L\">here</a> move left<br>");
            client.print("Click <a href=\"/R\">here</a> move right<br>");
            client.print("Click <a href=\"/S\">here</a> stop<br>");
            client.println();
            break;
          } 
          else {
            currentLine = "";
          }
        }
        //if there is input, add it to 'currentLine'
        else if (input != '\r') {
          currentLine += input;
        }
        //Read 'currentLine' and preform an action accordingly
        //Move forward
        if (currentLine.endsWith("GET /F")) {
          Serial.print("\nRecieving F\n");
          digitalWrite(RF, HIGH);
          digitalWrite(RR, LOW);
          digitalWrite(LF, HIGH);
          digitalWrite(LR, LOW);
        }
        //Back up
        if (currentLine.endsWith("GET /B")) {
          Serial.print("\nRecieving B\n");
          digitalWrite(RF, LOW);
          digitalWrite(RR, HIGH);
          digitalWrite(LF, LOW);
          digitalWrite(LR, HIGH);
        }
        //Turn left
        if (currentLine.endsWith("GET /L")) {
          Serial.print("\nRecieving L\n");
          digitalWrite(RF, HIGH);
          digitalWrite(RR, LOW);
          digitalWrite(LF, LOW);
          digitalWrite(LR, HIGH);
        }
        //Turn right
        if (currentLine.endsWith("GET /R")) {
          Serial.print("\nRecieving R\n");
          digitalWrite(RF, LOW);
          digitalWrite(RR, HIGH);
          digitalWrite(LF, HIGH);
          digitalWrite(LR, LOW);
        }
        //Stop
        if (currentLine.endsWith("GET /S")) {
          Serial.print("\nRecieving S\n");
          digitalWrite(RF, LOW);
          digitalWrite(RR, LOW);
          digitalWrite(LF, LOW);
          digitalWrite(LR, LOW);
        }
        //If the tank looses wifi connection, make it stop moving
        if (WiFi.status() != WL_CONNECTED){
          digitalWrite(RF, LOW);
          digitalWrite(RR, LOW);
          digitalWrite(LF, LOW);
          digitalWrite(LR, LOW);
        }
      }
    }
    //remove the client
    client.stop();
    Serial.println("connection terminated");
  }
}
