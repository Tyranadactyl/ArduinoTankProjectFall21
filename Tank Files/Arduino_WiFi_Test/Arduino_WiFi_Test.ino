#include<SPI.h>
#include<WiFiNINA.h>

//R/L (Right/Left) F/R (Forward/Reverse)
const int RF = 3;
const int RR = 4;
const int LF = 5;
const int LR = 6;

int connectionStatus = WL_IDLE_STATUS;

char ssid[] = //network SSID;
char pass[] = //network password;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  pinMode(RF, OUTPUT);
  pinMode(RR, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LR, OUTPUT);

  //Check firmware
  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.print("Firmware needs an update.");
  }

  while (connectionStatus != WL_CONNECTED) {
    Serial.print("Connecting to" + ssid + "...");
    connection = WiFi.begin(ssid, pass);
    delay(5000); //5 sec delay before trying again
  }

  server.begin();
  printWiFiStatus();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.print("we have connection!");
    String currentLine = "";
    while (client.connected()) {
      
      if (client.available()) {
        
        char input = client.read();
        Serial.write(input);
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
