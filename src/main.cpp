#include <Arduino.h>

#define PIN_OUT        16
#define PIN_IN         17
#define POLL_PERIOD_MS 1000

u32_t lastTimeChanged = 0;
u32_t react_time_OUT = 0;
u32_t react_time_IN = 0;
u32_t react_time = 0;
bool measured = false;

void setup(){
  Serial.begin(115200);
  pinMode(PIN_OUT, OUTPUT);
  pinMode(PIN_IN, INPUT_PULLUP);

  Serial.println("SETUP DONE");
}

void loop(){
  u32_t now = millis();

  if(now-lastTimeChanged >= POLL_PERIOD_MS){
    lastTimeChanged = millis();
    digitalWrite(PIN_OUT, HIGH);
    react_time_OUT = millis();
    
  }
  if(digitalRead(PIN_IN) == LOW){
      digitalWrite(PIN_OUT, LOW);
      react_time_IN = millis();
      measured = true;
    }

  if(measured){
    react_time = react_time_IN - react_time_OUT;
    Serial.printf("Relay react time is: %d \n", react_time);
    measured = false;
    //delay(1000);
  }

}