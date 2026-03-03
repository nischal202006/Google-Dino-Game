# Google-Dino-Game (Arduino Hardware Clone)

A standalone hardware implementation of the classic Chrome "No Internet" Dinosaur game[cite: 66, 72]. [cite_start]This project translates software-based mechanics into a physical system using an Arduino Uno, custom C++ logic, and real-time hardware-software integration.

##  Project Overview
[cite_start]This project focuses on creating an engaging learning tool that demonstrates efficient resource management on microcontrollers[cite: 80, 87]. [cite_start]It features custom-bitmapped graphics, dynamic difficulty scaling, and a dedicated audio feedback system [cite: 1-10, 49, 100].

### Key Features
* **Custom 8-Bit Graphics:** Designed 10 unique character sprites (Dinosaur frames, birds, and obstacles) using custom byte arrays for the LCD 
* **Real-Time Collision Detection:** Implemented logic to detect overlaps between the dinosaur and randomly generated obstacles across 16 grid columns.
* **Dynamic Difficulty:** Game speed increases automatically as the score rises, decreasing the movement interval from 100ms down to a minimum of 30ms 
* **Non-Blocking Logic:** Utilized `millis()` for all timing functions to ensure the system remains responsive to button inputs without using restrictive `delay()` calls
* **Audio Feedback:** Features a piezo buzzer system with unique melodies for game start, jumps, and game over sequences 

##  Hardware Architecture
The system is built on a custom-soldered PCB for enhanced durability and easier user access compared to standard breadboard setups

* **Microcontroller:** Arduino Uno.
* **Display:** 16x2 LCD with an I2C module to minimize wiring complexity.
* **Input:** Tactile push button for jump mechanics
* **Feedback:** Piezo buzzer for multi-tone audio


## 💻 Software Implementation
The core logic manages three distinct game states: the Start Screen (blinking prompt), Active Gameplay, and the Game Over sequence 

```cpp
// Example of the collision logic used for ground-based obstacles
if ((column_part == b || column_part == c) && row_part == 1) {
    gameOver(); // Triggered when obstacle coordinates match Dino position
}
