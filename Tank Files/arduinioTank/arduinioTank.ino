int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

void setup() {
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    char data = Serial.read();
    //Forward
    if(data == 'w') {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);
      delay(250);

    }
    
    if(data =='d') {
      //Right
      digitalWrite(motor2pin1, HIGH);
      digitalWrite(motor2pin2, LOW);

      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      delay(250);
    }

    if(data =='s') {
      //Backwards
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
      delay(250);
    }

    if(data =='a') {
      //Left
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);

      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, HIGH);
      delay(1250);
    }

    if(data == '/') {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);
    }
}
