int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 4;
int motor2pin2 = 5;

void setup() {
    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
}

void loop() {
    //Forward
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    delay(2000);

    //Right
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    delay(2000);

    //Backwards
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    delay(2000);

    //Left
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    delay(2000);
}