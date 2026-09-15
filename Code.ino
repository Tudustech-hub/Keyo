#include "USB.h"
#include "USBHIDKeyboard.h"
#include "U8g2lib.h"
#include "Wire.h"

USBHIDKeyboard Keyboard;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// The GIPOs for the buttons
const int KeyPins[9] = {1,2,4,6,7,8,10,11,12};

// What each button will send
const char KeyChars[9] = {'1','2','3','4','5','6','7','8','9'};

bool KeyState[9] = {false};
String lastKey = "";

void setup() {
    for (int i = 0; i < 9; i++) {
        pinMode(KeyPins[i], INPUT_PULLUP);
    }
    Keyboard.begin();
    USB.begin();
    Wire.begin(13, 14); // SDA AND SCL
    display.begin();

    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.drawStr(10, 20, "Keyo");
    display.sendBuffer();
    delay(1000);

    showIdleScreen();
}
void loop() {
    for (int i = 0; i < 9; i++) {
        bool pressed = (digitalRead(KeyPins[i]) == LOW);

        if (pressed && !KeyState[i]) {
            Keyboard.press(KeyChars[i]) ;
            KeyState[i] = true;
            lastKey = "Key " + String(i + 1);
            updateDisplay();
        } else if (!pressed && KeyState[i]) {
            Keyboard.release(KeyChars[i]);
            KeyState[i] = false;
        }
    }
    delay(10);
}
void showIdleScreen() {
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.drawStr(10, 20 , "Press a key");
    display.sendBuffer();
}
void updateDisplay() {
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.drawStr(10, 20, lastKey.c_str());
    display.sendBuffer();
}
