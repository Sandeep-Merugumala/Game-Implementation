# 🎮 Arduino OLED Game Console

This project is a simple yet engaging **Arduino-based multi-game console** using the **SSD1306 OLED display** and push buttons for input. It includes three games:

- 🚗 **Dodger Game**
- 💡 **LED Memory Game**
- 🔢 **Guess the Number Game**

The games are controlled using three input buttons and provide visual output on the OLED screen and audio feedback through a buzzer.

---

## 📷 Hardware Components

- Arduino UNO/Nano
- SSD1306 OLED Display (128x64)
- 3 Push Buttons (Digital Pins 9, 10, 11)
- 3 LEDs (Digital Pins 5, 6, 7)
- Buzzer (Digital Pin 8)
- Resistors (for buttons and LEDs)
- Breadboard & Jumper Wires

---

## 🕹️ Game Descriptions

### 1. Dodger Game
- Dodge falling lines by switching left and right using Button 1.
- A circle at the bottom represents the player.
- If you collide, a **Game Over** screen appears.

### 2. Memory Game
- Watch a sequence of blinking LEDs.
- Reproduce the sequence using Buttons 1, 2, and 3.
- Get feedback on whether your memory was correct.

### 3. Guess the Number
- A random number is generated between 0 and 100.
- Input your guesses via Serial Monitor.
- OLED displays whether your guess is **high**, **low**, or **correct**.

---

## ⚙️ Setup Instructions

1. Connect all components as per the pin mapping.
2. Install the required libraries:
   - `Adafruit_SSD1306`
   - `Adafruit_GFX`
3. Upload the code to the Arduino board using the Arduino IDE.
4. Open Serial Monitor (9600 baud) for the "Guess the Number" game.
5. Use push buttons to navigate and play games.

---

## 📌 Pin Configuration

| Function               | Pin   |
|------------------------|-------|
| Button 1 (Game 1 / Confirm) | D11   |
| Button 2 (Game 2)      | D10   |
| Button 3 (Game 3)      | D9    |
| LED 1                  | D7    |
| LED 2                  | D6    |
| LED 3                  | D5    |
| Buzzer                 | D8    |
| OLED SDA               | A4    |
| OLED SCL               | A5    |

---

## 📎 Features

- Simple game selection menu
- Dynamic visuals on OLED
- Real-time button inputs
- EEPROM-free memory usage
- Buzzer sound effects

---

## 🧠 Concepts Demonstrated

- Function pointers
- Struct usage
- OLED graphics with `Adafruit_GFX`
- Debouncing and input reading
- Random number generation
- Dynamic memory allocation and cleanup

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 🤝 Contributions

Feel free to fork the repository and submit pull requests to:
- Add new games
- Improve game logic
- Optimize memory or performance

---

## 💬 Contact

Made with ❤️ for embedded electronics learning and fun.

---

