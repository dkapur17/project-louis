#include <Arduino.h>
#include <BleKeyboard.h>

const int NUM_BUTTONS = 6;
const int BUTTON_PINS[NUM_BUTTONS] = {19, 18, 5, 23, 22, 21};
const int DEBOUNCE_DELAY = 50;

bool buttonStates[NUM_BUTTONS] = {false};
bool lastButtonStates[NUM_BUTTONS] = {false};
unsigned long lastDebounceTime[NUM_BUTTONS] = {0};

uint8_t currentButtonMask = 0;
uint8_t maxButtonMask = 0;
bool sequenceStarted = false;

BleKeyboard bleKeyboard = BleKeyboard("Louis v0");


char mode = 'L'; //L, U, N, S, M
bool connected = false;


void handleLowerCase(uint8_t pattern) {

  switch(pattern) {
    case 1: bleKeyboard.print('a'); break;
    case 3: bleKeyboard.print('b'); break;
    case 9: bleKeyboard.print('c'); break;
    case 25: bleKeyboard.print('d'); break;
    case 17: bleKeyboard.print('e'); break;
    case 11: bleKeyboard.print('f'); break;
    case 27: bleKeyboard.print('g'); break;
    case 19: bleKeyboard.print('h'); break;
    case 10: bleKeyboard.print('i'); break;
    case 26: bleKeyboard.print('j'); break;
    case 5: bleKeyboard.print('k'); break;
    case 7: bleKeyboard.print('l'); break;
    case 13: bleKeyboard.print('m'); break;
    case 29: bleKeyboard.print('n'); break;
    case 21: bleKeyboard.print('o'); break;
    case 15: bleKeyboard.print('p'); break;
    case 31: bleKeyboard.print('q'); break;
    case 23: bleKeyboard.print('r'); break;
    case 14: bleKeyboard.print('s'); break;
    case 30: bleKeyboard.print('t'); break;
    case 37: bleKeyboard.print('u'); break;
    case 39: bleKeyboard.print('v'); break;
    case 58: bleKeyboard.print('w'); break;
    case 45: bleKeyboard.print('x'); break;
    case 61: bleKeyboard.print('y'); break;
    case 53: bleKeyboard.print('z'); break;
  }

}

void handleUpperCase(uint8_t pattern) {

  switch(pattern) {
    case 1: bleKeyboard.print('A'); break;
    case 3: bleKeyboard.print('B'); break;
    case 9: bleKeyboard.print('C'); break;
    case 25: bleKeyboard.print('D'); break;
    case 17: bleKeyboard.print('E'); break;
    case 11: bleKeyboard.print('F'); break;
    case 27: bleKeyboard.print('G'); break;
    case 19: bleKeyboard.print('H'); break;
    case 10: bleKeyboard.print('I'); break;
    case 26: bleKeyboard.print('J'); break;
    case 5: bleKeyboard.print('K'); break;
    case 7: bleKeyboard.print('L'); break;
    case 13: bleKeyboard.print('M'); break;
    case 29: bleKeyboard.print('N'); break;
    case 21: bleKeyboard.print('O'); break;
    case 15: bleKeyboard.print('P'); break;
    case 31: bleKeyboard.print('Q'); break;
    case 23: bleKeyboard.print('R'); break;
    case 14: bleKeyboard.print('S'); break;
    case 30: bleKeyboard.print('T'); break;
    case 37: bleKeyboard.print('U'); break;
    case 39: bleKeyboard.print('V'); break;
    case 58: bleKeyboard.print('W'); break;
    case 45: bleKeyboard.print('X'); break;
    case 61: bleKeyboard.print('Y'); break;
    case 53: bleKeyboard.print('Z'); break;
  }
}

void handleNumber(uint8_t pattern) {

  switch(pattern) {
    case 1: bleKeyboard.print('1'); break;
    case 3: bleKeyboard.print('2'); break;
    case 9: bleKeyboard.print('3'); break;
    case 25: bleKeyboard.print('4'); break;
    case 17: bleKeyboard.print('5'); break;
    case 11: bleKeyboard.print('6'); break;
    case 27: bleKeyboard.print('7'); break;
    case 19: bleKeyboard.print('8'); break;
    case 10: bleKeyboard.print('9'); break;
    case 26: bleKeyboard.print('0'); break;
  }

}

void handleSymbol(uint8_t pattern) {

  switch(pattern) {
    case 1: bleKeyboard.print('!'); break;
    case 3: bleKeyboard.print('@'); break;
    case 9: bleKeyboard.print('#'); break;
    case 25: bleKeyboard.print('$'); break;
    case 17: bleKeyboard.print('%'); break;
    case 11: bleKeyboard.print('^'); break;
    case 27: bleKeyboard.print('&'); break;
    case 19: bleKeyboard.print('*'); break;
    case 10: bleKeyboard.print('('); break;
    case 26: bleKeyboard.print(')'); break;
    case 5: bleKeyboard.print('-'); break;
    case 7: bleKeyboard.print('_'); break;
    case 13: bleKeyboard.print('='); break;
    case 29: bleKeyboard.print('+'); break;
    case 21: bleKeyboard.print('['); break;
    case 15: bleKeyboard.print(']'); break;
    case 31: bleKeyboard.print('{'); break;
    case 23: bleKeyboard.print('}'); break;
    case 14: bleKeyboard.print(';'); break;
    case 30: bleKeyboard.print(':'); break;
    case 37: bleKeyboard.print('\''); break;
    case 39: bleKeyboard.print('"'); break;
    case 58: bleKeyboard.print(','); break;
    case 45: bleKeyboard.print('.'); break;
    case 61: bleKeyboard.print('?'); break;
    case 53: bleKeyboard.print('/'); break;
  }
}

void handleMovement(uint8_t pattern) {

  switch(pattern) {
    case 7: bleKeyboard.write(KEY_LEFT_ARROW); break;
    case 56: bleKeyboard.write(KEY_RIGHT_ARROW); break;
    case 9: bleKeyboard.write(KEY_UP_ARROW); break;
    case 36: bleKeyboard.write(KEY_DOWN_ARROW); break;
  }

}


void handleButtonCombination(uint8_t pattern) {

  Serial.print("Pattern: ");
  Serial.println(pattern);
  if(pattern == 2)
  {
    Serial.println("Switching to Lowercase mode");
    mode = 'L';
  }
  else if(pattern == 32)
  {
    Serial.println("Switching to Uppercase mode");
    mode = 'U';
  }
  else if(pattern == 60)
  {
    Serial.println("Switching to Number mode");
    mode = 'N';
  }
  else if(pattern == 16)
  {
    Serial.println("Switching to Symbol mode");
    mode = 'S';
  }
  else if(pattern == 48)
  {
    Serial.println("Switching to Movement mode");
    mode = 'M';
  }
  else if(pattern == 63)
    bleKeyboard.print(" ");
  else if(pattern == 4)
    bleKeyboard.write(KEY_BACKSPACE);
  else {
    switch (mode) {
      case 'L':
        handleLowerCase(pattern);
        break;
      case 'U':
        handleUpperCase(pattern);
        break;
      case 'N':
        handleNumber(pattern);
        break;
      case 'S':
        handleSymbol(pattern);
        break;
      case 'M':
        handleMovement(pattern);
        break;
    }
  }
}


void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  Serial.println("Pumpernickle Keyboard");
  Serial.print("Starting BLE...");
  bleKeyboard.begin();
  Serial.println("Done!");
}

void loop() {

  if(!connected) {
    if(bleKeyboard.isConnected()) {
      connected = true;
      bleKeyboard.println("Connected!");
    }
    else
      return;
  }
  else
  {
    if(!bleKeyboard.isConnected()) {
      connected = false;
      bleKeyboard.println("Disconnected!");
      return;
    }
  }

  bool anyButtonPressed = false;

  for (int i = 0; i < NUM_BUTTONS; i++) {
    int reading = digitalRead(BUTTON_PINS[i]);
    
    if (reading != lastButtonStates[i]) {
      lastDebounceTime[i] = millis();
    }
    
    if ((millis() - lastDebounceTime[i]) > DEBOUNCE_DELAY) {
      if (reading != buttonStates[i]) {
        buttonStates[i] = reading;
        
        if (buttonStates[i] == LOW) {  // Button is pressed (active low)
          currentButtonMask |= (1 << i);  // Set the bit
          sequenceStarted = true;
        } else {
          currentButtonMask &= ~(1 << i);  // Clear the bit
        }
        
        if (currentButtonMask > maxButtonMask) {
          maxButtonMask = currentButtonMask;
        }
      }
    }
    
    lastButtonStates[i] = reading;
    
    if (buttonStates[i] == LOW) {
      anyButtonPressed = true;
    }
  }

  if (sequenceStarted && !anyButtonPressed) {
    handleButtonCombination(maxButtonMask);

    // Reset for the next sequence
    sequenceStarted = false;
    maxButtonMask = 0;
    currentButtonMask = 0;
  }

}

