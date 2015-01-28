/* hw1_2_helloBlink
 Blink(LED)
 Modified from OpenCM example of Blink(LED)
 
 Turns on the built-in LED(Status LED) on for 0.1 second, then off for 0.1 second,
 repeatedly. BOARD_LED_PIN is defined previously, so just use it without declaration.
 BOARD_LED_PIN was connected to pin 16 in CM-900, but connected to pin 14 in OpenCM9.04.

                Compatibility
CM900                  O
OpenCM9.04             0

 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */
  int grnLED = 14;
  int ptime = 1000;
void setup() {
  // Set up the built-in LED pin as an output:
  //pinMode(BOARD_LED_PIN, OUTPUT);

  pinMode(grnLED, OUTPUT);
}

void loop() {
  digitalWrite(grnLED, HIGH); // set to as HIGH LED is turn-off
  delay(ptime);          // Wait for 1 second
  digitalWrite(grnLED, LOW);  // set to as LOW LED is turn-on
  delay(ptime);          // Wait for 1 second
}

