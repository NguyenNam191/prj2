#include <Arduino.h>
#include <OneButton.h>

#define BUTTON1_PIN 22
#define BUTTON2_PIN 21
#define LED1_PIN 5
#define LED2_PIN 18

OneButton button1(BUTTON1_PIN, true);
OneButton button2(BUTTON2_PIN, true);

bool led1State = false;
bool led2State = false;
bool blinkMode = false;
bool controlLED1 = true;  
unsigned long previousMillis = 0;
const long blinkInterval = 200;

void handleSingleClick();
void handleDoubleClick();
void handleLongPressStart();

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  button1.attachClick(handleSingleClick);
  button1.attachDoubleClick(handleDoubleClick);
  button1.attachLongPressStart(handleLongPressStart);

  button2.attachClick(handleSingleClick);
  button2.attachDoubleClick(handleDoubleClick);
  button2.attachLongPressStart(handleLongPressStart);

  Serial.begin(115200);
  Serial.println("Ready...");
}

void loop() {
  button1.tick();
  button2.tick();

  if (blinkMode) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;

      if (controlLED1) {
        led1State = !led1State;
        digitalWrite(LED1_PIN, led1State);
      } else {
        led2State = !led2State;
        digitalWrite(LED2_PIN, led2State);
      }
    }
  }
}

void handleSingleClick() {
  if (blinkMode) {
    blinkMode = false;
  
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    led1State = false;
    led2State = false;
    Serial.println("Exit blink mode");
  } else {
    if (controlLED1) {
      led1State = !led1State;
      digitalWrite(LED1_PIN, led1State);
      Serial.print("LED1: ");
      Serial.println(led1State ? "ON" : "OFF");
    } else {
      led2State = !led2State;
      digitalWrite(LED2_PIN, led2State);
      Serial.print("LED2: ");
      Serial.println(led2State ? "ON" : "OFF");
    }
  }
}

void handleDoubleClick() {
  controlLED1 = !controlLED1;  
  Serial.print("Now controlling: ");
  Serial.println(controlLED1 ? "LED1" : "LED2");
}

void handleLongPressStart() {
  blinkMode = true;
  Serial.println("Blink mode ON");
}
