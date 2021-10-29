#include<SPI.h>
#include<WiFiNINA.h>

//Establish variables for ease of use
//R/L (Right/Left) F/R (Forward/Reverse)
const int RF = 3;
const int RR = 4;
const int LF = 5;
const int LR = 6;

//set default connection status
int connectionStatus = WL_IDLE_STATUS;

//Variables for network id and password
char ssid[] = //network SSID;
char pass[] = //network password;

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

  //Check firmware
  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.print("Firmware needs an update.");
  }

  //While not connected, repeatedly attempt to connect to the network
  while (connectionStatus != WL_CONNECTED) {
    Serial.print("Connecting to" + ssid + "...");
    connection = WiFi.begin(ssid, pass);
    delay(5000); //5 sec delay before trying again
  }

  //Start the server
  server.begin();

  //Print the servers IP address
  Serial.print("The boards IP is:");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Client states wether or not we have a connected client
  WiFiClient client = server.available();

  if (client) {
    Serial.print("we have connection!");
    //currentline will store the incoming data from the client
    String currentLine = "";
    //while a client is connected
    while (client.connected()) {
      //if the client is sending data
      if (client.available()) {
        //read the incoming data
        char input = client.read();
        //write the data on the serial monitor
        Serial.write(input);
        //if the client isn't requesting any data, then display the webpage for them
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
        //if 
        else if (c != '\r') {
          currentLine += c;
        }
        //Move forward
        if (currentLine.endsWith("GET /F")) {
          digitalWrite(RF, HIGH);
          digitalWrite(RR, LOW);
          digitalWrite(LF, HIGH);
          digitalWrite(LR, LOW);
        }
        //Back up
        if (currentLine.endsWith("GET /B")) {
          digitalWrite(RF, LOW);
          digitalWrite(RR, HIGH);
          digitalWrite(LF, LOW);
          digitalWrite(LR, HIGH);
        }
        //Turn left
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(RF, HIGH);
          digitalWrite(RR, LOW);
          digitalWrite(LF, LOW);
          digitalWrite(LR, HIGH);
        }
        //Turn right
        if (currentLine.endsWith("GET /R")) {
          digitalWrite(RF, LOW);
          digitalWrite(RR, HIGH);
          digitalWrite(LF, HIGH);
          digitalWrite(LR, LOW);
        }
        //Stop
        if (currentLine.endsWith("GET /S")) {
          digitalWrite(RF, LOW);
          digitalWrite(RR, LOW);
          digitalWrite(LF, LOW);
          digitalWrite(LR, LOW);
        }
      }
    }
    client.stop();
    Serial.println("connection terminated");
  }
}
