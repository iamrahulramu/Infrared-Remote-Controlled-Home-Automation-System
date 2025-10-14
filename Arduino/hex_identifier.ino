#include <IRremote.h>

#define IR_RECEIVE_PIN 11
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("Press any button on the IR remote");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Hex Code: ");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}
