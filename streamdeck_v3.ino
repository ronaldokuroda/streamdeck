#include "Keyboard.h"

// Pin definitions
#define BUTTON_PIN1 2
#define BUTTON_PIN2 3
#define BUTTON_PIN3 4
#define BUTTON_PIN4 5
#define BUTTON_PIN5 6
#define BUTTON_PIN6 7
#define BUTTON_PIN7 8
#define BUTTON_PIN8 9
#define BUTTON_PIN9 10
#define BUTTON_PIN10 14
#define BUTTON_PIN11 15
#define BUTTON_PIN12 16

const uint8_t ledPin = 17;

// Classe botão com função de ação personalizada
class button {
  public:
  const uint8_t pin;
  void (*onPress)();

  button(uint8_t p, void (*f)()) : pin(p), onPress(f) {}

  void update(){
    bool state = !digitalRead(pin); // botão pressionado
    if(state && !pressed && (millis() - lastPressed > debounceTime)){
      lastPressed = millis();
      onPress();
      pressed = true;
    }
    if (!state) {
      pressed = false;
    }
  }

  private:
  const unsigned long debounceTime = 30;
  unsigned long lastPressed = 0;
  boolean pressed = false;
};

// ---------- Funções para cada botão (Ctrl + número) ----------
void ctrl1() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('1'); delay(10); Keyboard.release('1'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl2() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('2'); delay(10); Keyboard.release('2'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl3() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('3'); delay(10); Keyboard.release('3'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl4() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('4'); delay(10); Keyboard.release('4'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl5() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('5'); delay(10); Keyboard.release('5'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl6() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('6'); delay(10); Keyboard.release('6'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl7() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('7'); delay(10); Keyboard.release('7'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl8() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('8'); delay(10); Keyboard.release('8'); Keyboard.release(KEY_LEFT_CTRL); }
void ctrl9() { Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('9'); delay(10); Keyboard.release('9'); Keyboard.release(KEY_LEFT_CTRL); }

void alt1() { Keyboard.press(KEY_LEFT_ALT); Keyboard.press('1'); delay(10); Keyboard.release('1'); Keyboard.release(KEY_LEFT_ALT); }
void alt2() { Keyboard.press(KEY_LEFT_ALT); Keyboard.press('2'); delay(10); Keyboard.release('2'); Keyboard.release(KEY_LEFT_ALT); }
void alt3() { Keyboard.press(KEY_LEFT_ALT); Keyboard.press('3'); delay(10); Keyboard.release('3'); Keyboard.release(KEY_LEFT_ALT); }

// Array de botões
button buttons[] = {
  {BUTTON_PIN1, ctrl1},
  {BUTTON_PIN2, ctrl2},
  {BUTTON_PIN3, ctrl3},
  {BUTTON_PIN4, ctrl4},
  {BUTTON_PIN5, ctrl5},
  {BUTTON_PIN6, ctrl6},
  {BUTTON_PIN7, ctrl7},
  {BUTTON_PIN8, ctrl8},
  {BUTTON_PIN9, ctrl9},
  {BUTTON_PIN10, alt1},
  {BUTTON_PIN11, alt2},
  {BUTTON_PIN12, alt3},
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(button);

void setup() { 
  pinMode(1, INPUT_PULLUP); // failsafe
  if(!digitalRead(1)){
    failsafe();
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  TXLED0;

  for(int i = 0; i < NumButtons; i++){
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {
  for(int i = 0; i < NumButtons; i++){
    buttons[i].update();
  }
}

void failsafe(){
  for(;;){}
}
