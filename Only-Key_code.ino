#include "USB.h"
#include "USBHIDKeyboard.h"
#include "U8g2lib.h"
#include "Wire.h"

USBHIDKeyboard Keyboard;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

// The GIPOs for the buttons
const int KeyPins[9] = {1,2,4,6,7,8,10,11,12};

// ===============================
// Change Your Key Characters Here
//================================
// "copy" for copy
// "paste" for paste
// "cut" for cut
// "undo" for undo
// "redo" for redo
// "save" for save
// "selectall" to select all
// "mute"   for mute
// "volup" for volume up
// "voldown" for volume down
// "playpause" for play/pause
// "ctrl:X" control + X (X being any key you want to send)

const char* KeyActions[9] = {
    "copy",      // Key 1
    "paste",     // Key 2
    "cut",       // Key 3
    "undo",      // Key 4
    "redo",      // Key 5
    "save",      // Key 6
    "mute", // Key 7
    "voldown",   // Key 8
    "volup"      // Key 9
};

const char* KeyLabels[9] = {
    "copy", "paste", "undo",
    "cut", "redo", "save",
    "mute", "voldown", "volup"
};

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
void sendShortcut(int index) {
    String action = keyActions[index];

    if (action == "copy") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('c');
        Keyboard.releaseAll();
    } else if (action == "paste") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('v');
        Keyboard.releaseAll();
    } else if (action == "cut") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('x');
        Keyboard.releaseAll();
    } else if (action == "undo") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('z');
        Keyboard.releaseAll();
    } else if (action == "redo") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('y');
        Keyboard.releaseAll();
    } else if (action == "save") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('s');
        Keyboard.releaseAll();
    } else if (action == "selectall") {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('a');
        Keyboard.releaseAll();
    } else if (action == "mute") {
        Keyboard.press(KEY_MEDIA_MUTE);
        Keyboard.releaseAll();
    } else if (action == "volup") {
        Keyboard.press(KEY_MEDIA_VOLUME_UP);
        Keyboard.releaseAll();
    } else if (action == "voldown") {
        Keyboard.press(KEY_MEDIA_VOLUME_DOWN);
        Keyboard.releaseAll();
    } else if (action == "playpause") {
        Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
        Keyboard.releaseAll();
    } else if (action.startsWith("ctrl:")) {
        char key = action.charAt(5);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(key);
        Keyboard.releaseAll();
    } else if (action.startsWith("char:")) {
        char key = action.charAt(5);
        Keyboard.press(key);
        Keyboard.releaseAll();
    }

}

