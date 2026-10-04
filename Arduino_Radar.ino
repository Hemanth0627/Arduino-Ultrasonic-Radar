#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6

Servo radarServo;

float measureDistance() {
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

 
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo is received
  if (duration == 0) {
    return -1;
  }

  
  return duration * 0.0343 / 2.0;
}

void setup() {
  
  Serial.begin(115200);

 
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  
  radarServo.attach(SERVO_PIN);

  
  radarServo.write(90);

  delay(1000);
}

void loop() {
  
  for (int angle = 0; angle <= 180; angle += 2) {
    radarServo.write(angle);
    delay(30);

    float distance = measureDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }


  for (int angle = 180; angle >= 0; angle -= 2) {
    radarServo.write(angle);
    delay(30);

    float distance = measureDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}
