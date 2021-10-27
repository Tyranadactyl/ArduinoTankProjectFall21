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
          
        }
      }
    }
  }
}
