# SimpleMenu

SimpleMenu es una librería para Arduino que facilita la creación de menús interactivos en pantallas LCD 20x4 con conexión I2C, usando un encoder rotativo con botón para navegación y selección.

## Características

- Navegación sencilla y fluida con encoder rotativo.
- Soporte para submenús y acciones asociadas a cada opción.
- Manejo eficiente de la pantalla LCD sin parpadeos innecesarios.
- Diseño modular para fácil integración en cualquier proyecto Arduino.
- Ejemplos incluidos para rápida implementación.

## Requisitos

- Arduino IDE (compatible con versiones recientes).
- Librería `LiquidCrystal_I2C`.
- Librería `Encoder`.

## Instalación

1. Descarga o clona este repositorio.
2. Copia la carpeta `SimpleMenu` en tu carpeta de librerías de Arduino, normalmente:
   - Windows: `Documentos\Arduino\libraries\`
   - macOS/Linux: `~/Arduino/libraries/`
3. Reinicia el IDE Arduino.
4. Encuentra los ejemplos en: **Archivo > Ejemplos > SimpleMenu**.

## Uso básico

```cpp
#include <SimpleMenu.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

// Configura LCD y encoder
LiquidCrystal_I2C lcd(0x27, 20, 4);
Encoder myEnc(4, 5);
MenuSystem menu(lcd, 6);

// Define menú con opciones y submenús usando std::vector<MenuItem>
// Inicializa el menú con menu.setRootMenu(&menuPrincipal);

void setup() {
  lcd.init();
  lcd.backlight();
  menu.setRootMenu(&menuPrincipal);
  // Resto de configuración...
}

void loop() {
  // Lee encoder, botón y actualiza menú con menu.update()
}
