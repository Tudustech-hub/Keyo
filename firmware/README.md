# Keyo Firmware

This directory contains the firmware for the **Keyo** macropad.

## Hardware Specifications
- **MCU**: ESP32-S3
- **Keys**: 9 Mechanical Cherry MX-style switches
- **Display**: 0.91" 128x32 I2C OLED (SSD1306)

## Pinout Mapping

| Component | Pin / GPIO | Notes |
| :--- | :--- | :--- |
| **Key 1** | GPIO 1 | Active LOW (INPUT_PULLUP) |
| **Key 2** | GPIO 2 | Active LOW (INPUT_PULLUP) |
| **Key 3** | GPIO 4 | Active LOW (INPUT_PULLUP) |
| **Key 4** | GPIO 6 | Active LOW (INPUT_PULLUP) |
| **Key 5** | GPIO 7 | Active LOW (INPUT_PULLUP) |
| **Key 6** | GPIO 8 | Active LOW (INPUT_PULLUP) |
| **Key 7** | GPIO 10 | Active LOW (INPUT_PULLUP) |
| **Key 8** | GPIO 11 | Active LOW (INPUT_PULLUP) |
| **Key 9** | GPIO 12 | Active LOW (INPUT_PULLUP) |
| **OLED SDA** | GPIO 13 | I2C Data |
| **OLED SCL** | GPIO 14 | I2C Clock |

## Flashing Instructions (Arduino IDE)

1. Install the **ESP32** board package by Espressif in Arduino IDE:
   - Go to **Boards Manager** and install `esp32` (by Espressif Systems).
2. Install the required library:
   - In **Library Manager**, search for and install **`U8g2`** by olikraus.
3. Open `keyo_firmware/keyo_firmware.ino`.
4. Configure board settings under **Tools**:
   - **Board**: `ESP32S3 Dev Module`
   - **USB CDC On Boot**: `Enabled`
   - **USB DFU On Boot**: `Disabled`
   - **Upload Mode**: `UART0 / Hardware CDC`
   - **USB Mode**: `Hardware CDC and JTAG`
5. Connect your Keyo macropad via USB-C, select the COM/Serial port, and click **Upload**.

## Default Shortcuts
- **Key 1**: Copy (`Ctrl + C`)
- **Key 2**: Paste (`Ctrl + V`)
- **Key 3**: Cut (`Ctrl + X`)
- **Key 4**: Undo (`Ctrl + Z`)
- **Key 5**: Redo (`Ctrl + Y`)
- **Key 6**: Save (`Ctrl + S`)
- **Key 7**: Mute (Media Mute)
- **Key 8**: Volume Down (Media Volume Down)
- **Key 9**: Volume Up (Media Volume Up)
