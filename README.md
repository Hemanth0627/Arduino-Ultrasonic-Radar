# Arduino 180° Radar

A beginner-friendly laptop display for an Arduino Uno, an HC-SR04 ultrasonic sensor, and a servo. The Python program reads comma-separated `angle,distance` lines over USB and plots the latest readings on a semicircular radar.

## Requirements

- Python 3
- Arduino connected on `COM7`
- Arduino Serial Monitor and Serial Plotter closed while Python is running
- Arduino sketch sending lines such as `66,6.33` at **115200 baud**

## Install the Python libraries

Open Command Prompt and run:

```text
py -m pip install pyserial matplotlib
```

## Run the radar

Open Command Prompt in this folder and run:

```text
py radar.py
```

Close the radar window to stop the program and release COM7. If your Arduino uses a different COM port, change `PORT = "COM7"` near the top of `radar.py`.

## Arduino sketch

The Arduino program is included as `Arduino_Radar.ino`. It uses these pins:

- HC-SR04 TRIG: pin 9
- HC-SR04 ECHO: pin 10
- Servo signal: pin 6
- Serial baud rate: 115200

It sends one `angle,distance` pair per line, for example:

```text
66,6.33
68,6.24
```

## Hardware Connections
- HC-SR04 VCC → Arduino 5V
- HC-SR04 TRIG → Arduino digital pin 9
- HC-SR04 ECHO → Arduino digital pin 10
- HC-SR04 GND → Arduino GND
- Servo signal wire (usually orange or yellow) → Arduino digital pin 6
- Servo power wire (usually red) → regulated 5V supply
- Servo ground wire (usually brown or black) → supply ground and Arduino GND
- Connect the Arduino Uno to the laptop with a USB cable. The laptop runs the Python radar program on COM7.
The external servo supply and Arduino must share a ground connection. The Arduino code uses pins 9, 10, and 6, and sends data at 115200 baud.


