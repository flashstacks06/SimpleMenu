#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SimpleMenu.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Definición de acciones
void verRiegos() {
  lcd.clear();
  lcd.print("Ver riegos...");
}

void encenderRiego() {
  lcd.clear();
  lcd.print("Riego Encendido");
}

void apagarRiego() {
  lcd.clear();
  lcd.print("Riego Apagado");
}

std::vector<MenuItem> menuRoot = {
  { "Ver riegos", verRiegos, {} },
  { "Control manual", nullptr, {
      { "Encender riego", encenderRiego, {} },
      { "Apagar riego", apagarRiego, {} },
      { "Volver", nullptr, {} }
  }},
  { "Salir", nullptr, {} }
};

SimpleMenu menu(lcd, 4, 5, 6);

void mostrarEstado() {
  lcd.clear();
  lcd.print("Estado sistema:");
  lcd.setCursor(0,1);
  lcd.print("Humedad: 45%");
  lcd.setCursor(0,2);
  lcd.print("Riego: Apagado");
  lcd.setCursor(0,3);
  lcd.print("Hora: 12:34");
}

void setup() {
  menu.begin(&menuRoot, mostrarEstado);
}

void loop() {
  menu.update();
}