# Crypto Game (C++)

A simple command-line C++ game where players solve 3 levels of cryptographic challenges using an in-game decoder/encoder tool.

## Features
- **3 Cryptographic Levels:**
  1. **Level 1:** Atbash Cipher (Alphabet Mirror)
  2. **Level 2:** Caesar Cipher (Shift Key: 7)
  3. **Level 3:** Vigenere Cipher (Keyword: `CPU`)
- **In-Game Decoder/Encoder Tool:** Test decryption and encryption directly inside the terminal.
- **Scoring & Lives System:** Start with 100 points and 3 lives. Earn points for solving levels and bonus encryption tasks, or spend 20 points on clues.
- **High Scores:** Automatically saves player scores to `scores.txt`.

## How to Compile and Run

```bash
g++ main.cpp -o game
./game