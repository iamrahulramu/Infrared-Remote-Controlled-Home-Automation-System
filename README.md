# Infrared Remote-Controlled Home Automation System
A simple Arduino-based home automation system that allows users to control multiple electrical appliances using any Infrared (IR) remote. In this prototype, two appliances - a light bulb and a miniature fan - are connected to an Arduino board through a relay component. The system operates based on signals received from a TSOP1738 IR receiver, which detects and decodes signals from an IR remote.

---

## Table of Contents
- [Infrared Remote-Controlled Home Automation System](#infrared-remote-controlled-home-automation-system)
  - [Table of Contents](#table-of-contents)
  - [Project Overview](#project-overview)
  - [Hardware Components](#hardware-components)
  - [Software Requirements](#software-requirements)
  - [Implementation Steps](#implementation-steps)
    - [Identifying Hexadecimal Code of Each Button on IR Remote](#identifying-hexadecimal-code-of-each-button-on-ir-remote)
    - [Linking Buttons on IR Remote to Specific Appliances](#linking-buttons-on-ir-remote-to-specific-appliances)
  - [Implementation Description](#implementation-description)
    - [IR Code Identification](#ir-code-identification)
    - [Appliance Control](#appliance-control)
  - [Future Improvements](#future-improvements)
  - [License](#license)
  - [Acknowledgements](#acknowledgements)

---

## Project Overview
When any button on the IR remote is pressed, the TSOP1738 IR receiver (connected to the Arduino board) detects the signal and sends it to the Arduino Uno. The Arduino decodes this incoming signal into a hexadecimal value and compares it with predefined codes stored in the source code. If a match is found, the corresponding relay channel is toggled, switching the connected appliance ON or OFF.

---

## Hardware Components
This section lists the hardware components used in the project, along with their functionalities.

| Component | Function |
|------------|-------------|
| Arduino Uno | Main controller board |
| TSOP1738 IR Receiver | To receive signals from the IR remote |
| Relay Module (2-Channel) | To switch the appliances ON/OFF |
| Light Bulb | Load/Appliance |
| Miniature Fan | Load/Appliance |
| IR Remote | To provide user control input |
| Jumper Wires | To connect various hardware components |
| Breadboard | To provide a prototype platform for assembling the system |

---

## Software Requirements
To set up and run this project, ensure the following software tools and libraries are installed:
- **Arduino IDE:** Version 1.8.x or later (or Arduino CLI)
- **Operating System:** Windows / macOS / Linux
- **Required Arduino Library**: IRremote library (for decoding IR signals). It can be installed directly from the `Arduino Library Manager`
  - Open `Arduino IDE` → `Sketch` → `Include Library` → `Manage Libraries`
  - Search for `IRremote`
  - Click `Install`

   or install manually using Arduino CLI:

   ```bash
   arduino-cli lib install "IRremote"
   ```

---

## Implementation Steps
The hexadecimal code associated with each button on an IR remote varies between remotes and is not the same for all models. Therefore, the hexadecimal codes for each button must first be identified. 

### Identifying Hexadecimal Code of Each Button on IR Remote
1. Connect the TSOP1738 IR receiver to the Arduino as described below:
   | Arduino Pin | TSOP1738 Pin |
   |--------------|--------------|
   | 11 | OUT |
   | 5V | VCC |
   | GND | GND |
2. Upload the **IR code receiver sketch** from [`Arduino/hex_identifier.ino`](Arduino/hex_identifier.ino) to the Arduino
3. Open the **Serial Monitor** and set the baud rate to 9600
4. Press different buttons on the IR remote and note the hexadecimal values displayed for each button

After successfully identifying the hexadecimal codes for each button on the IR remote, specific buttons can be linked to corresponding appliances.

### Linking Buttons on IR Remote to Specific Appliances
1. Open [`Arduino/ir_remote_home_automation.ino`](Arduino/ir_remote_home_automation.ino)
2. Replace the example hexadecimal codes with the codes obtained in the previous step
3. Upload the code to the Arduino board
4. Connect the relay module, light bulb, and miniature fan as described below:
    | Arduino Pin                 | Connected Component      | Component Pin     |
    | --------------------------- | ------------------------ | ----------------- |
    | 11                          | TSOP1738 IR Receiver     | OUT               |
    | 5V                          |                          | VCC               |
    | GND                         |                          | GND               |
    | 7                           | Relay Module             | IN1 (Channel 1)   |
    | 8                           |                          | IN2 (Channel 2)   |
    | 5V                          |                          | VCC               |
    | GND                         |                          | GND               |
    | Relay Output ( NO1 / COM1 ) | Light Bulb               | + / –             |
    | Relay Output ( NO2 / COM2 ) | Miniature Fan            | + / –             |

    The setup is ready - pressing the assigned buttons on the IR remote will toggle the light and fan accordingly.

---

## Implementation Description
This section provides a brief description of the source code implemented on the Arduino board.

### IR Code Identification
**Script**: [Arduino/hex_identifier.ino](Arduino/hex_identifier.ino)

The `hex_identifier.ino` sketch detects and displays the hexadecimal code transmitted by each button on the IR remote.

**IR Receiver Initialization**
```cpp
#include <IRremote.h>

#define IR_RECEIVE_PIN 11
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;
```
The TSOP1738 IR receiver is connected to digital pin 11 of the Arduino. The `IRremote` library handles decoding of incoming IR signals.

**Reading and Printing Hexadecimal Codes**
```cpp
if (irrecv.decode(&results)) {
  Serial.print("Hex Code: ");
  Serial.println(results.value, HEX);
  irrecv.resume();
}
```
When a button on the remote is pressed, the Arduino receives a hexadecimal code, which is displayed on the Serial Monitor.

### Appliance Control 
**Script**: [Arduino/ir_remote_home_automation.ino](Arduino/ir_remote_home_automation.ino)

The `ir_remote_home_automation.ino` sktech uses the identified IR codes to toggle appliances (light and fan) via relay modules.

**Pin Definitions and Setup**
```cpp
#define IR_RECEIVE_PIN 11
#define RELAY1 7   
#define RELAY2 8  
```
The IR receiver is connected to pin 11, while pins 7 and 8 control the relays for the light and fan, respectively.

**Relay Initialization**
```cpp
pinMode(RELAY1, OUTPUT);
pinMode(RELAY2, OUTPUT);
digitalWrite(RELAY1, HIGH);
digitalWrite(RELAY2, HIGH);
```
Both relays are set to `HIGH` initially, ensuring that appliances remain OFF when the system starts.

**Decoding and Matching IR Codes**
```cpp
if (results.value == lightCode) {
  digitalWrite(RELAY1, !digitalRead(RELAY1));
  Serial.println("Light Toggled");
}
else if (results.value == fanCode) {
  digitalWrite(RELAY2, !digitalRead(RELAY2));
  Serial.println("Fan Toggled");
}
irrecv.resume();
```
The Arduino continuously listens for IR signals. When a received code matches the predefined value for the light, the light relay toggles its state. Similarly, a matching code for the fan toggles its corresponding relay. After processing each valid signal, the receiver resumes to detect subsequent button presses (or signals).

---

## Future Improvements
While the current implementation successfully controls home appliances using an infrared remote, several enhancements can be made to improve its functionality and usability:
- **Support for More Devices:** Extend the system to control additional household appliances.
- **Wi-Fi or Bluetooth Integration:** Incorporate wireless communication modules for smartphone-based control alongside IR functionality.

---

## License
This project is licensed under the terms specified in the ``LICENSE`` file **(MIT License)**.

---

## Acknowledgements
This project was a collaborative effort developed between April 2022 and June 2022. Special thanks to fellow contributors M. Pradheep and S. Vignesh Kumar for their support in the development and testing of this prototype.