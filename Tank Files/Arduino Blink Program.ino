const int ledPin = 13;

void setup(){
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop(){
    int delayPeriod = 250;
    digitalWrite(ledPin, HIGH);
    Serial.println("Light's on");
    delay(delayPeriod);
    digitalWrite(ledPin, LOW);
    Serial.println("Light's off");
    delay(delayPeriod);
}