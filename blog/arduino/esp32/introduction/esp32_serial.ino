void setup() {
  // start Serial port
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  // print a message
  Serial.print("Enter a number: ");

  // wait for user input
  while(!Serial.available()) delay(10);
  
  // read user input, convert it to a number
  int num = Serial.parseInt();

  // look for the newline (enter) character
  // if found, feedback a message
  if (Serial.read() == '\n') {
    Serial.print("You entered ");
    Serial.print(num);
    Serial.println();
  }
}
