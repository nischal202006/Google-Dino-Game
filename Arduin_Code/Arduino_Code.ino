#include <LiquidCrystal.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Character definitions remain the same
byte DINO_BODY_PART_1[8] = {B00000, B00000, B00100, B00100, B00111, B00111, B00011, B00010}; 
byte DINO_BODY_PART_2[8] = {B01110, B01011, B01111, B11000, B11110, B11010, B10000, B10000};
byte DINO_RIGHTFOOT_PART_1[8] = {B00000, B00000, B00100, B00100, B00111, B00111, B00011, B00010};
byte DINO_RIGHTFOOT_PART_2[8] = {B01110, B01011, B01111, B11000, B11110, B11010, B10000, B00000};
byte DINO_LEFTFOOT_PART_1[8] = {B00000, B00000, B00100, B00100, B00111, B00111, B00011, B00000};
byte DINO_LEFTFOOT_PART_2[8] = {B01110, B01011, B01111, B11000, B11110, B11010, B10000, B10000};
byte BRANCH_PART_1[8] = {B00000, B00100, B00100, B10100, B10100, B11100, B00100, B00100};
byte BRANCH_PART_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100};
byte BIRD_PART1[8] = {B00001, B00001, B00001, B00001, B01001, B11111, B00000, B00000};
byte BIRD_PART2[8] = {B00000, B10000, B11000, B11100, B11110, B11111, B00000, B00000};

const int buttonPin = 7;
const int buzzerPin = 6;

// Game speed constants
const int INITIAL_SPEED = 100;  // Initial time between obstacle movements
const int MIN_SPEED = 30;       // Minimum time between movements (maximum speed)
const int SPEED_DECREASE = 5;   // How much to decrease the time interval per level

// Musical notes frequencies 
#define NOTE_G3  196
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698

// Melodies 
int startMelody[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5};
int startDurations[] = {150, 150, 150, 300};
int gameOverMelody[] = {NOTE_C5, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_G3};
int gameOverDurations[] = {200, 200, 200, 200, 400};
int highObstacleSound[] = {NOTE_C5, NOTE_E5};
int highObstacleDurations[] = {50, 50};
int lowObstacleSound[] = {NOTE_C4, NOTE_G4};
int lowObstacleDurations[] = {50, 50};

// Game state variables
bool gameStarted = false;
int column_dino1 = 1;
int column_dino2 = 2;
int row_dino = 1;
unsigned long clock1 = 0;
int time1 = 100;
int flag = 1;
int row_part = 0;
int column_part = 13;
int time2 = INITIAL_SPEED;  // Initialize with starting speed
unsigned long clock2 = 0;
int a = 0;
int b = 1;
int c = 2;
int d = 0;
unsigned long clock3 = 0;
int time3 = 100;
int point1 = 0;
int point2 = 0;
int num_random = 0;
int column_bird = 13;
int e = 0;
int row_bird = 1;
int current = 0;
int prev = 0;
int f = 13;

// Start screen variables
unsigned long blinkClock = 0;
const int blinkInterval = 500;
bool blinkState = true;

// Sound functions remain the same
void playStartSound() {
    for (int i = 0; i < 4; i++) {
        tone(buzzerPin, startMelody[i]);
        delay(startDurations[i]);
        noTone(buzzerPin);
        delay(30);
    }
}

void playGameOverMelody() {
    for (int i = 0; i < 5; i++) {
        tone(buzzerPin, gameOverMelody[i]);
        delay(gameOverDurations[i]);
        noTone(buzzerPin);
        delay(50);
    }
}

void playHighObstacleSound() {
    for (int i = 0; i < 2; i++) {
        tone(buzzerPin, highObstacleSound[i]);
        delay(highObstacleDurations[i]);
        noTone(buzzerPin);
        delay(20);
    }
}

void playLowObstacleSound() {
    for (int i = 0; i < 2; i++) {
        tone(buzzerPin, lowObstacleSound[i]);
        delay(lowObstacleDurations[i]);
        noTone(buzzerPin);
        delay(20);
    }
}

// Function to update game speed based on score
void updateGameSpeed() {
    // Calculate new speed based on score
    int newSpeed = INITIAL_SPEED - (point2 * SPEED_DECREASE);
    
    // Ensure speed doesn't go below minimum
    time2 = max(newSpeed, MIN_SPEED);
}

void showStartScreen() {
    if (millis() - blinkClock >= blinkInterval) {
        blinkClock = millis();
        blinkState = !blinkState;
        
        lcd.clear();
        if (blinkState) {
            lcd.setCursor(3, 0);
            lcd.print("GAME START");
            lcd.setCursor(1, 1);
            lcd.print("Press Button!");
        }
    }
}

void setup() {
    // Initialize pins
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);
    
    // Initialize LCD
    lcd.begin(16, 2);
    lcd.backlight();
    
    // Create custom characters
    lcd.createChar(0, DINO_BODY_PART_1);
    lcd.createChar(1, DINO_BODY_PART_2);
    lcd.createChar(2, DINO_RIGHTFOOT_PART_1);
    lcd.createChar(3, DINO_RIGHTFOOT_PART_2);
    lcd.createChar(4, DINO_LEFTFOOT_PART_1);
    lcd.createChar(5, DINO_LEFTFOOT_PART_2);
    lcd.createChar(6, BRANCH_PART_1);
    lcd.createChar(7, BRANCH_PART_2);  
    lcd.createChar(8, BIRD_PART1);  
    lcd.createChar(9, BIRD_PART2);
    
    // Initialize game state
    gameStarted = false;
    blinkClock = millis();
    
    // Test buzzer
   // tone(buzzerPin, NOTE_C4, 100);
    //delay(100);
    //noTone(buzzerPin);
}

void gameOver() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(3, 1);
    lcd.print("Score: ");
    lcd.print(point1);
    
    playGameOverMelody();
    delay(2000);
    
    // Reset game state
    gameStarted = false;
    lcd.clear();
    column_part = 15;
    time2 = INITIAL_SPEED;  // Reset speed to initial value
    point1 = 0;
    point2 = 0;
}

void loop() {
    if (!gameStarted) {
        showStartScreen();
        if (digitalRead(buttonPin) == LOW) {
            gameStarted = true;
            lcd.clear();
            playStartSound();
            delay(500);
        }
        return;
    }

    if (millis() > clock1 + time1) {
        clock1 = millis();
        flag = (flag == 1) ? 2 : 1;
    }

    if (millis() > clock2 + time2) {
        clock2 = millis();
        column_part -= 1;

        if (column_part == 0) {
            point1++;
            // Different sounds for high and low obstacles
            if (row_part == 0) {
                playHighObstacleSound();
            } else {
                playLowObstacleSound();
            }
            
            if (point1 % 10 == 0) {
                point2++;
                updateGameSpeed();  // Update game speed when level increases
            }
        }

        if (column_part < 0) {
            column_part = 13;
            num_random = random(0, 3);
        }

        f = column_part + 1;
        lcd.setCursor(f, 1);
        lcd.print(" ");
        lcd.setCursor(f, 0);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 0);
        lcd.print(" ");
        a = 1;
    }

    if (d == 0) {
        if (flag == 1) {
            lcd.setCursor(column_dino1, row_dino);
            lcd.write(byte(2));
            lcd.setCursor(column_dino2, row_dino);
            lcd.write(byte(3));
        } else {
            lcd.setCursor(column_dino1, row_dino);
            lcd.write(byte(4));
            lcd.setCursor(column_dino2, row_dino);
            lcd.write(byte(5));
        }
    }

    if (a == 1) {
        if (num_random == 1 || num_random == 2) {
            row_part = 1;
            lcd.setCursor(column_part, row_part);
            lcd.write(byte(6 + num_random - 1));
        } else {
            row_part = 0;
            lcd.setCursor(column_part - 1, row_part);
            lcd.write(byte(8));
            lcd.setCursor(column_part, row_part);
            lcd.write(byte(9));
        }
        a = 0;
    }

    if (digitalRead(buttonPin) == LOW && (column_part == 1 || column_part == 2 || column_bird == 1 || column_bird == 2) && row_part == 0) {
        gameOver();
    }

    if ((column_part == b || column_part == c) && row_part == 1) {
        gameOver();
    }

    if (digitalRead(buttonPin) == LOW) {
        b = 50;
        c = 50;
        if (d == 0) {
            lcd.setCursor(0, 1);       
            lcd.print("    ");   
        }
        d = 1;
        lcd.setCursor(column_dino1, 0);
        lcd.write(byte(2));
        lcd.setCursor(column_dino2, 0);
        lcd.write(byte(3)); 
    } else {    
        b = 1;
        c = 2; 
        d = 0;
    }

    lcd.setCursor(13, 0);         
    lcd.print(point1);
   // lcd.setCursor(14, 0);         
    //lcd.print(point2);

    current = digitalRead(buttonPin);
    if (current != prev) {
        lcd.setCursor(1, 0);          
        lcd.print("  "); 
    }
    prev = current;
}