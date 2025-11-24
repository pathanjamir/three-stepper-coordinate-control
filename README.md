# Three Stepper Coordinate Control (Arduino Mega + L298P + L293D)

This repository contains a complete 3-axis stepper motor motion-control system
implemented on an **Arduino Mega 2560**.  
The system allows the user to configure:

- travel distance in mm for X, Y, Z
- manual direction (CW / CCW)
- steps-per-mm conversion
- motor speed
- continuous or one-shot motion

The firmware is fully parameterized and easy to modify, making it ideal for  
robotics, CNC-style movement, 3D positioning, or educational motion control projects.

---

## ✨ Features

### ✔ 3 Independent Stepper Motors
- Motor 1 → X Axis  
- Motor 2 → Y Axis  
- Motor 3 → Z Axis  
- Driven by **L298P** (Motor1) and **two L293D** drivers (Motor2, Motor3).

### ✔ Manual Direction Control
Each motor can be set to **CW** (`+1`) or **CCW** (`-1`) behavior.

### ✔ Coordinate-Based Movement
User configures movement in **millimeters**, firmware converts it to motor steps.

### ✔ Adjustable Mechanical Conversion
Configure:
```cpp
#define STEPS_PER_MM 25.0
