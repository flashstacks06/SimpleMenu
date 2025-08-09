#include "SimpleMenu.h"

SimpleMenu::SimpleMenu(LiquidCrystal_I2C& lcd, int clkPin, int dtPin, int swPin, int sensitivity)
  : lcd(lcd), encoder(clkPin, dtPin), swPin(swPin), encoderSensitivity(sensitivity) {}

void SimpleMenu::begin(std::vector<MenuItem>* rootMenu, std::function<void()> showDefaultState) {
  this->rootMenu = rootMenu;
  this->currentMenu = rootMenu;
  this->showDefaultState = showDefaultState;

  this->state = ESTADO;
  this->logicalPosition = 0;
  this->encoderBase = encoder.read();
  this->menuVisible = false;
  this->lastInteraction = millis();
  this->actionActive = false;

  pinMode(swPin, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();

  showDefaultState();
}

void SimpleMenu::update() {
  unsigned long now = millis();
  bool buttonRaw = digitalRead(swPin) == LOW;

  if (buttonRaw) {
    if (now - lastButtonPress > 200) {
      buttonPressed = true;
      lastButtonPress = now;
    } else {
      buttonPressed = false;
    }
  } else {
    buttonPressed = false;
  }

  switch(state) {
    case ACCION:
      if (now - actionStart >= actionDuration) {
        actionActive = false;
        state = MENU;
        showMenu();
        lastInteraction = now;
      }
      break;

    case MENU: {
      int maxIndex = (int)currentMenu->size() - 1;
      long encoderPos = encoder.read();
      long delta = (encoderPos - encoderBase) / encoderSensitivity;

      if (delta < 0) {
        delta = 0;
        encoder.write(encoderBase + delta * encoderSensitivity);
      }
      if (delta > maxIndex) {
        delta = maxIndex;
        encoder.write(encoderBase + delta * encoderSensitivity);
      }

      if (delta != logicalPosition || buttonPressed) {
        logicalPosition = delta;
        lastInteraction = now;
        if (!menuVisible) {
          menuVisible = true;
          showMenu();
        }
        if (buttonPressed) {
          MenuItem &item = (*currentMenu)[logicalPosition];
          if (!item.subMenu.empty()) {
            menuStack.push_back(currentMenu);
            currentMenu = &item.subMenu;
            logicalPosition = 0;
            encoderBase = encoder.read();
            resetPosition();
            showMenu();
          } else if (item.action) {
            item.action();
            actionActive = true;
            actionStart = now;
            state = ACCION;
          } else if (item.name == "Volver") {
            if (!menuStack.empty()) {
              currentMenu = menuStack.back();
              menuStack.pop_back();
              logicalPosition = 0;
              encoderBase = encoder.read();
              resetPosition();
              showMenu();
            } else {
              state = ESTADO;
              menuVisible = false;
              showDefaultState();
            }
          } else if (item.name == "Salir") {
            state = ESTADO;
            menuVisible = false;
            showDefaultState();
          }
        } else {
          showMenu();
        }
      }

      if (menuVisible && now - lastInteraction > timeout) {
        menuVisible = false;
        state = ESTADO;
        showDefaultState();
      }
      break;
    }

    case ESTADO: {
      long encoderPos = encoder.read();
      long delta = (encoderPos - encoderBase) / encoderSensitivity;

      if (delta != logicalPosition || buttonPressed) {
        lastInteraction = now;
        menuVisible = true;
        state = MENU;
        currentMenu = rootMenu;
        menuStack.clear();
        encoderBase = encoderPos;
        logicalPosition = 0;
        resetPosition();
        showMenu();
      }
      break;
    }
  }
}

void SimpleMenu::resetPosition() {
  // No hace nada, queda para posible futura expansión
}

void SimpleMenu::showMenu() {
  lcd.clear();
  int lines = 4;
  int start = (logicalPosition < lines) ? 0 : logicalPosition - lines + 1;

  for (int i = 0; i < lines; i++) {
    int idx = start + i;
    if (idx >= (int)currentMenu->size()) break;

    lcd.setCursor(0, i);
    lcd.print(idx == logicalPosition ? "> " : "  ");
    lcd.print((*currentMenu)[idx].name);

    // Borrar resto de la línea
    int len = (*currentMenu)[idx].name.length();
    for (int j = len + 2; j < 20; j++) lcd.print(" ");
  }
}