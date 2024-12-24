#define LED D4

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for(int brillo=0; brillo <=255; brillo++) {
    analogWrite(LED,brillo);
    delay(20);
  }
  delay(1000);
}