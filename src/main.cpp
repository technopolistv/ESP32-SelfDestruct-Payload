/*
  https://www.technopolis.tv/PlatformIO-Self-destructing-Arduino-ESP32-Firmware/ 
*/ 

#include <Arduino.h>

#define NAME "Self Destruct Payload"
#define VERSION "v1.0.0"
#define BUILD NAME " " VERSION
#define RED_LED 26
#define BUTTON 32

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  // turn on the red LED to indicate second stage
  digitalWrite(RED_LED, HIGH);

  Serial.begin(115200);
  Serial.println(BUILD);

  // erase everything except the own partition (APP1)
  Serial.print("Erase NVS: ");
  if(esp_flash_erase_region(NULL, 0x9000, 0x9000) == ESP_OK) {
    Serial.println("OK");
  } else {
    Serial.println("ERR"); 
  }

  Serial.print("Erase OTA Data: ");
  if(esp_flash_erase_region(NULL, 0xe000, 0x2000) == ESP_OK) {
    Serial.println("OK");
  } else {
    Serial.println("ERR"); 
  }

  Serial.print("Erase SPIFFS: ");
  if(esp_flash_erase_region(NULL, 0x290000, 0x160000) == ESP_OK) {
    Serial.println("OK");
  } else {
    Serial.println("ERR"); 
  }

  Serial.print("Erase APP0: ");
  if(esp_flash_erase_region(NULL, 0x10000, 0x140000) == ESP_OK) {
    Serial.println("OK");
  } else {
    Serial.println("ERR"); 
  }

  // uncommenting this part would crash the ESP
  // Serial.print("Erase APP1: ");
  // if(esp_flash_erase_region(NULL, 0x150000, 0x140000) == ESP_OK) {
  //   Serial.println("OK");
  // } else {
  //   Serial.println("ERR"); 
  // }

  // turn off red LED to indicate that erasing process is finished
  digitalWrite(RED_LED, LOW);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    digitalWrite(RED_LED, !digitalRead(RED_LED));
    
    Serial.println("Nothing to see here...");

    delay(500);
  }
}
