int KLOKBIT_PIN = 10;

bool COMPACT = true;

void setup() {
  Serial.begin(9600);
  while(!Serial){
  }

  for (int i =2; i<11; i++){
    pinMode(i, INPUT);
  }

  Serial.println("\nTyp \"ja\" om Cookies te accepteren en verder te gaan.");
  Serial.println("Anders mag je niet verder, Ik verkoop wel al je persoonlijke informatie aan derden.");
  while (Serial.available()==0){}
  Serial.println("Bedankt voor je consent, en nou wegwezen!");
}

void loop() {

  if (digitalRead(KLOKBIT_PIN) > 0) {
     boolean inputs[8];
    for(int i = 7; i >= 0; i--) {
      inputs[i] = digitalRead(i+2);
      if (!COMPACT) {
        Serial.print(inputs[i]);
      }
    }
    
    if (!COMPACT) {
      Serial.println("");
    }

    int asciiValue=0;
    int convertedInputs[8];
    for (int i = 0; i < 8; i++){
      int deelresultaat = inputs[i] * (int)round(pow(2, i));
      asciiValue += deelresultaat;
    }

    char character = (char) asciiValue;

    if (character == '/') {
      COMPACT = !COMPACT;
    } else if (asciiValue == 13) {
      Serial.println("");
    } else {
      if (!COMPACT) {
        Serial.println(asciiValue);
      }

      if (!COMPACT) {
        Serial.println(character);
      } else {
        Serial.print(character);
      }
    }
    delay(100);
  }
}
