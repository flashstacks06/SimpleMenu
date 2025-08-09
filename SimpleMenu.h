#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <vector>
#include <functional>

struct MenuItem {
  String name;
  std::function<void()> action;
  std::vector<MenuItem> subMenu;
};

class SimpleMenu {
public:
  enum State { ESTADO, MENU, ACCION };

  SimpleMenu(LiquidCrystal_I2C& lcd, int clkPin, int dtPin, int swPin, int sensitivity = 6);

  void begin(std::vector<MenuItem>* rootMenu, std::function<void()> showDefaultState);
  void update();

private:
  void resetPosition();
  void showMenu();

  LiquidCrystal_I2C& lcd;
  Encoder encoder;
  int swPin;
  int encoderSensitivity;

  std::vector<MenuItem>* rootMenu = nullptr;
  std::vector<MenuItem>* currentMenu = nullptr;
  std::vector<std::vector<MenuItem>*> menuStack;

  bool menuVisible = false;
  int logicalPosition = 0;
  long encoderBase = 0;

  bool buttonPressed = false;
  unsigned long lastButtonPress = 0;
  unsigned long lastInteraction = 0;

  State state = ESTADO;

  bool actionActive = false;
  unsigned long actionStart = 0;
  const unsigned long actionDuration = 1500;

  std::function<void()> showDefaultState;
  const unsigned long timeout = 5000;
};

#endif