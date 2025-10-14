#include <IRremote.h>

#define IR_RECEIVE_PIN 11
#define RELAY1 7   // Light
#define RELAY2 8   // Fan

unsigned long lightCode = 0x1FB51AF; // Example Hexadecimal value for Light button
unsigned long fanCode   = 0xFAD117; // Example Hexadecimal value for Fan button

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == lightCode) {
      digitalWrite(RELAY1, !digitalRead(RELAY1));
      Serial.println("Light Toggled");
    }
    else if (results.value == fanCode) {
      digitalWrite(RELAY2, !digitalRead(RELAY2));
      Serial.println("Fan Toggled");
    }

    irrecv.resume(); // Receive the next value
  }
}
