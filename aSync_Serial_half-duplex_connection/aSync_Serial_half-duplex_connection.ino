int CLAIM_PIN = 3;
int DATA_PIN = 2;
bool COMPACT = true;

void setup() {

  Serial.begin(9600);
  while (!Serial) {
  }

  pinMode(DATA_PIN, INPUT);
  pinMode(CLAIM_PIN, INPUT);

  Serial.println("\n Verzend aub maximaal 20 characters per keer.");
  Serial.println("ALs je data binnenkrijgt, niet gaan sturen!");
}

void loop() {
  if (digitalRead(CLAIM_PIN) > 0) {

    delay(20);
    boolean inputs[10];
    for (int i = 7; i >= 0; i--) {
      inputs[i] = digitalRead(DATA_PIN);
      delay(100);
      if (!COMPACT) {
        Serial.print(inputs[i]);
      }
    }

    if (!COMPACT) {
      Serial.println("");
    }

    int asciiValue = 0;
    for (int i = 0; i < 8; i++) {
      int deelresultaat = inputs[i] * (int)round(pow(2, i));
      asciiValue += deelresultaat;
    }

    char character = (char)asciiValue;

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
  }

  if (digitalRead(CLAIM_PIN) == 0 && Serial.available() > 0) {

    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLAIM_PIN, OUTPUT);
    digitalWrite(CLAIM_PIN, 1);
    char outputChar = Serial.read();

    for (int i = 7; i > -1; i--) {
      bool output = bitRead(outputChar, i);
      Serial.print(output);
      digitalWrite(DATA_PIN, output);
      delay(100);
    }

    Serial.print(" (");
    Serial.print(outputChar);
    Serial.println(")");

    delay(21);

    digitalWrite(CLAIM_PIN, 0);
    pinMode(DATA_PIN, INPUT);
    pinMode(CLAIM_PIN, INPUT);
  }
}
