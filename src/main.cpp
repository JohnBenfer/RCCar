#include <Arduino.h>
#include <ArduinoGraphics.h>
#include <Arduino_LED_Matrix.h>
#include <TaskScheduler.h> // Include TaskScheduler library

ArduinoLEDMatrix matrix;

int enA = 8;
int in1 = 9;
int in2 = 10;

// Task Scheduler
Scheduler runner;

// Forward declarations of the tasks
void scrollText();
void controlMotor();

// Define tasks
Task taskScrollText(1000, TASK_FOREVER, &scrollText, &runner, true);
Task taskControlMotor(10000, TASK_FOREVER, &controlMotor, &runner, true);

void setup() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    matrix.begin();

    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    const char text[] = "UNO r4";
    matrix.textFont(Font_4x6);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(text);
    matrix.endText();
    matrix.endDraw();

    delay(2000);
}

void loop() {
    runner.execute();
}

void scrollText() {
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(55);

    const char text[] = "    Hello World!   ";
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
}

void controlMotor() {
    analogWrite(enA, 50); // set the speed
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(5000);

    analogWrite(enA, 100); // a little bit faster now
    delay(2000);
    analogWrite(enA, 180); // a little bit faster now
    delay(2000);
    analogWrite(enA, 255); // Shout! Hey! Hey! Hey!
    delay(2000);
    analogWrite(enA, 200); // a little bit softer now
    delay(2000);
    analogWrite(enA, 75); // a little bit softer now
    delay(2000);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}