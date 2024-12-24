//version 1
void setup() {
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(D3) == LOW) {
    Serial.println("pressed");
    digitalWrite(D4, LOW);
  } else {
    Serial.println("not pressed");
    digitalWrite(D4, HIGH);
  }
  delay(200);
}

/*
//version 2

#define LED D4
#define BUTTON D3

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(BUTTON));
  digitalWrite(LED,digitalRead(BUTTON));
  delay(500);
}

*/