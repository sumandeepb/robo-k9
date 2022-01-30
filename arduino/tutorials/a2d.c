const int POT = 0; // sensor connected to A0
int val = 0; // store sensor value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // setup serial port baud rate
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(POT); // read sensor value
  Serial.println(val); // print sensor value to serial bus
  delay(500); // wait 500ms before next poll
}
