# Google-Dino-Game (Arduino Hardware Clone)

[cite_start]A standalone hardware implementation of the classic Chrome "No Internet" Dinosaur game[cite: 66, 72]. [cite_start]This project translates software-based mechanics into a physical system using an Arduino Uno, custom C++ logic, and real-time hardware-software integration[cite: 85, 107].

## 🚀 Project Overview
[cite_start]This project focuses on creating an engaging learning tool that demonstrates efficient resource management on microcontrollers[cite: 80, 87]. [cite_start]It features custom-bitmapped graphics, dynamic difficulty scaling, and a dedicated audio feedback system [cite: 1-10, 49, 100].

### Key Features
* [cite_start]**Custom 8-Bit Graphics:** Designed 10 unique character sprites (Dinosaur frames, birds, and obstacles) using custom byte arrays for the LCD [cite: 1-10, 35].
* [cite_start]**Real-Time Collision Detection:** Implemented logic to detect overlaps between the dinosaur and randomly generated obstacles across 16 grid columns[cite: 58, 59].
* [cite_start]**Dynamic Difficulty:** Game speed increases automatically as the score rises, decreasing the movement interval from 100ms down to a minimum of 30ms [cite: 12-14, 30].
* [cite_start]**Non-Blocking Logic:** Utilized `millis()` for all timing functions to ensure the system remains responsive to button inputs without using restrictive `delay()` calls[cite: 32, 44, 45].
* [cite_start]**Audio Feedback:** Features a piezo buzzer system with unique melodies for game start, jumps, and game over sequences [cite: 15-17, 25-29, 112].

## 🛠️ Hardware Architecture
[cite_start]The system is built on a custom-soldered PCB for enhanced durability and easier user access compared to standard breadboard setups[cite: 181].

* [cite_start]**Microcontroller:** Arduino Uno[cite: 107, 183].
* [cite_start]**Display:** 16x2 LCD with an I2C module to minimize wiring complexity[cite: 111, 180].
* [cite_start]**Input:** Tactile push button for jump mechanics[cite: 103, 184].
* [cite_start]**Feedback:** Piezo buzzer for multi-tone audio[cite: 112, 185].


## 💻 Software Implementation
[cite_start]The core logic manages three distinct game states: the Start Screen (blinking prompt), Active Gameplay, and the Game Over sequence [cite: 32, 41, 163-171].

```cpp
// Example of the collision logic used for ground-based obstacles
if ((column_part == b || column_part == c) && row_part == 1) {
    gameOver(); // Triggered when obstacle coordinates match Dino position
}
