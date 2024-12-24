/*
Desarrolla un programa que controle un LED utilizando un potenciómetro para ajustar su brillo. 
El control del brillo solo debe funcionar cuando el modo esté habilitado, y este se alternará 
al presionar un botón (sin usar interrupciones). Cuando el modo esté deshabilitado, el LED debe 
mantener la intensidad que tenía previamente, y cualquier cambio en el potenciómetro no afectará el brillo. 
Asegúrate de que el brillo del LED se modifique en un rango adecuado.
*/

#define BUTTON D3
#define LED D4
#define ADC A0

bool status;
bool buttonState;
bool prevButtonState;

void setup() {
  status = false; 
  buttonState = true;
  prevButtonState = false;
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
}

void loop() {
  buttonState = digitalRead(BUTTON);
  if(prevButtonState != buttonState) {
    prevButtonState = buttonState;
    if(buttonState == true) {
      status = !status;
    }
  }
  if(status==LOW) {
    analogWrite(LED, analogRead(ADC)/4 );
  }
  delay(30);
}