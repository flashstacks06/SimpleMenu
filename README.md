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
#include "SimpleMenu.h"

// Inicializar LCD I2C (0x27, 20x4)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Funciones para las opciones del menú
void accion1() {
  lcd.clear();
  lcd.print("Accion 1 ejecutada");
}

void accion2() {
  lcd.clear();
  lcd.print("Accion 2 ejecutada");
}

void submenuOpcion1() {
  lcd.clear();
  lcd.print("Submenu opcion 1");
}

void submenuOpcion2() {
  lcd.clear();
  lcd.print("Submenu opcion 2");
}

void salir() {
  lcd.clear();
  lcd.print("Saliendo...");
}

// Definición del menú
std::vector<MenuItem> menuRoot = {
  { "Accion 1", accion1, {} },
  { "Accion 2", accion2, {} },
  { "Submenu", nullptr, {
      { "Subopcion 1", submenuOpcion1, {} },
      { "Subopcion 2", submenuOpcion2, {} },
      { "Volver", nullptr, {} }
    }
  },
  { "Salir", salir, {} }
};

// Pines botones: UP, DOWN, SELECT
SimpleMenu menu(lcd, 4, 5, 6);

// Estado general mostrado cuando no se está en menú
void mostrarEstadoGeneral() {
  lcd.clear();
  lcd.print("Sistema Operativo");
  lcd.setCursor(0,1);
  lcd.print("Menu listo...");
  lcd.setCursor(0,2);
  lcd.print("Use botones");
  lcd.setCursor(0,3);
  lcd.print("para navegar");
}

void setup() {
  lcd.init();
  lcd.backlight();
  menu.begin(&menuRoot, mostrarEstadoGeneral);
}

void loop() {
  menu.update();
}
