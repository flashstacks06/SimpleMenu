# SimpleMenu

**SimpleMenu** es una librería ligera para Arduino que facilita la creación de menús interactivos en pantallas LCD I2C de 20x4 líneas usando un encoder rotatorio con botón integrado.  
Ideal para proyectos que requieren interfaces de usuario compactas y fáciles de usar, como controles de sistemas embebidos.

## Características

- Soporta menús jerárquicos con submenús.
- Navegación sencilla con encoder rotatorio.
- Selección de opciones con botón integrado.
- Compatible con pantallas LCD 20x4 I2C (LiquidCrystal_I2C).
- Código limpio y fácil de integrar en cualquier proyecto.
- Ejemplo de uso incluido.

## Instalación

1. Copia la carpeta `SimpleMenu` en la carpeta `libraries` de tu instalación de Arduino IDE.
2. Reinicia Arduino IDE.
3. Encuentra el ejemplo en `Archivo > Ejemplos > SimpleMenu > SimpleMenuExample`.

## Uso Básico

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <SimpleMenu.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Encoder encoder(4, 5);
MenuSystem menu(lcd, 6);

void accion1() {
  lcd.clear();
  lcd.print("Accion 1");
}

std::vector<MenuItem> menuRoot = {
  { "Opcion 1", accion1, {} },
  { "Salir", nullptr, {} }
};

void setup() {
  pinMode(6, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();

  menu.setRootMenu(&menuRoot);
  menu.resetPosition();
  menu.setOldPosition(0);
  menu.showMenu();
}

void loop() {
  long pos = encoder.read() / 5;
  bool btn = (digitalRead(6) == LOW);
  menu.update(pos, btn);
}
