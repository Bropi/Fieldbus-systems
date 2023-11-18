void setup() {
  Serial.begin(9600);
  while (!Serial) {

  }
  
  int KLOKBIT_PIN = 10;

  for (int i = 2 ; i < 11 ; i++) {
    pinMode(i, OUTPUT);
  }

  digitalWrite(KLOKBIT_PIN, 0);

  Serial.println("\nTyp \"ja\" om Cookies te accepteren en verder te gaan.");
  while (Serial.available() == 0) {}
}

void loop() {
  int KLOKBIT_PIN = 10;
  digitalWrite(KLOKBIT_PIN, 0);

  while (Serial.available() > 0) {
    char outputChar = Serial.read();
    
    boolean outputs[8];
    for (int i = 7 ; i > -1 ; i--) {
      outputs[i] = bitRead(outputChar, i);
      Serial.print(outputs[i]);
      digitalWrite(i + 2, outputs[i]);
    }

    Serial.print(" (");
    Serial.print(outputChar);
    Serial.println(")");

    digitalWrite(KLOKBIT_PIN, 1);
    delay(100);
    digitalWrite(KLOKBIT_PIN, 0);
  }
}