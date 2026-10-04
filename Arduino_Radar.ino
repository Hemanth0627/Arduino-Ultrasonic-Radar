#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 6

Servo radarServo;

float measureDistance() {
  // Send ultrasonic trigger pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // If no echo is received
  if (duration == 0) {
    return -1;
  }

  // Convert time to distance in cm
  return duration * 0.0343 / 2.0;
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Configure ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Attach servo
  radarServo.attach(SERVO_PIN);

  // Start servo at center
  radarServo.write(90);

  delay(1000);
}

void loop() {
  // Scan from 0° to 180°
  for (int angle = 0; angle <= 180; angle += 2) {
    radarServo.write(angle);
    delay(30);

    float distance = measureDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }

  // Scan back from 180° to 0°
  for (int angle = 180; angle >= 0; angle -= 2) {
    radarServo.write(angle);
    delay(30);

    float distance = measureDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(distance);
  }
}
