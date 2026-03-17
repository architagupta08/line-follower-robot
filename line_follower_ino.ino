#define PWMA 5
#define AIN1 18
#define AIN2 19

#define PWMB 4
#define BIN1 16
#define BIN2 17

#define STBY 21


#define LEFT_SENSOR 34
#define CENTER_SENSOR 35
#define RIGHT_SENSOR 32

int baseSpeed = 180;

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  digitalWrite(STBY, HIGH); 
}

void loop() {
  int left = digitalRead(LEFT_SENSOR);
  int center = digitalRead(CENTER_SENSOR);
  int right = digitalRead(RIGHT_SENSOR);

 
  if (center == LOW && left == HIGH && right == HIGH) {
    moveForward(baseSpeed, baseSpeed);
  }
  else if (left == LOW) {
    turnLeft(baseSpeed, baseSpeed);
  }
  else if (right == LOW) {
    turnRight(baseSpeed, baseSpeed);
  }
  else {
    stopMotors();
  }
}



void moveForward(int speedA, int speedB) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speedA);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speedB);
}

void turnLeft(int speedA, int speedB) {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, speedA);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speedB);
}

void turnRight(int speedA, int speedB) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speedA);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, speedB);
}

void stopMotors() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
