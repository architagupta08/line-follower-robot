// ===== MOTOR PINS =====
#define PWMA 5
#define AIN1 18
#define AIN2 19

#define PWMB 4
#define BIN1 16
#define BIN2 17

#define STBY 21

// ===== SENSORS =====
#define LEFT_SENSOR 34
#define CENTER_SENSOR 35
#define RIGHT_SENSOR 32

// ===== PWM SETTINGS =====
const int pwmChannelA = 0;
const int pwmChannelB = 1;
const int pwmFreq = 5000;
const int pwmResolution = 8;

// ===== PID =====
float Kp = 40;
float Ki = 0;
float Kd = 20;

int baseSpeed = 150;

int error = 0, previousError = 0;
float integral = 0, derivative = 0, correction = 0;

void setup() {

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  pinMode(LEFT_SENSOR, INPUT);
  pinMode(CENTER_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);

  // PWM setup (ESP32)
  ledcSetup(pwmChannelA, pwmFreq, pwmResolution);
  ledcAttachPin(PWMA, pwmChannelA);

  ledcSetup(pwmChannelB, pwmFreq, pwmResolution);
  ledcAttachPin(PWMB, pwmChannelB);

  digitalWrite(STBY, HIGH);

  Serial.begin(115200);
}

void loop() {

  int left = digitalRead(LEFT_SENSOR);
  int center = digitalRead(CENTER_SENSOR);
  int right = digitalRead(RIGHT_SENSOR);

  // Error calculation
  if (left == LOW) error = -1;
  else if (right == LOW) error = 1;
  else error = 0;

  // PID
  integral += error;
  derivative = error - previousError;
  correction = Kp * error + Ki * integral + Kd * derivative;

  previousError = error;

  // Speed adjustment
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  moveForward(leftSpeed, rightSpeed);
}

void moveForward(int speedA, int speedB) {

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  ledcWrite(pwmChannelA, speedA);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(pwmChannelB, speedB);
}