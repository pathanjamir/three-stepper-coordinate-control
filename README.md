# Three Stepper Coordinate Control  
Arduino Mega + L298P + L293D – 3-Axis Stepper Control

This project controls **three stepper motors** (X, Y, Z) using an **Arduino Mega**,  
**L298P** (Motor 1) and **two L293D** drivers (Motor 2 & 3).  
Movement is controlled by simple parameters inside the `.ino` file:

- Travel distance in mm  
- Manual motor direction (CW / CCW)  
- Steps per mm (mechanical calibration)  
- Motor speed  
- Continuous or one-shot motion  

No GUI or Python required.

---

## 🔧 Hardware

- Arduino Mega 2560  
- 1× L298P driver (Motor 1)  
- 2× L293D drivers (Motor 2 & 3)  
- 3× Bipolar stepper motors  
- 12V power supply  
- Jumper wires / breadboard  

---

## 🔌 Wiring (Arduino → Driver)

**Motor 1 (L298P)**  
22 → IN1  
23 → IN2  
24 → IN3  
25 → IN4  

**Motor 2 (L293D)**  
26 → IN1  
27 → IN2  
28 → IN3  
29 → IN4  

**Motor 3 (L293D)**  
30 → IN1  
31 → IN2  
32 → IN3  
33 → IN4  

Stepper coils → OUT1/OUT2 and OUT3/OUT4.

---

## ⚙️ Key Firmware Settings
Edit these at the top of the `.ino` file:

```cpp
#define X_TARGET_MM   10.0
#define Y_TARGET_MM    5.0
#define Z_TARGET_MM    3.0

#define M1_DIR  1     // CW
#define M2_DIR -1     // CCW
#define M3_DIR  1

#define STEPS_PER_MM  25.0
#define MOTOR_SPEED    3
#define CONTINUOUS_MODE 0   // 1 = repeat forever
