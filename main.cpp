#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string toUpper(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = s[i] - 32;
        }
    }
    return s;
}

string atbash(string s) {
    s = toUpper(s);
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = 'Z' - (s[i] - 'A');
        }
    }
    return s;
}

string caesar(string s, int shift) {
    s = toUpper(s);
    shift = (shift % 26 + 26) % 26;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (s[i] - 'A' + shift) % 26 + 'A';
        }
    }
    return s;
}

string vigenere(string s, string key, bool encrypt) {
    s = toUpper(s);
    key = toUpper(key);
    int k = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            int shift = key[k % key.length()] - 'A';
            if (!encrypt) shift = 26 - shift;
            s[i] = (s[i] - 'A' + shift) % 26 + 'A';
            k++;
        }
    }
    return s;
}

void decoderTool() {
    int ch;
    cout << "\n--- DECODER / ENCODER TOOL ---\n";
    cout << "1. Atbash Cipher\n";
    cout << "2. Caesar Decrypt\n";
    cout << "3. Caesar Encrypt\n";
    cout << "4. Vigenere Decrypt\n";
    cout << "Choice: ";
    cin >> ch;
    cin.ignore();

    string text;
    cout << "Enter text: ";
    getline(cin, text);

    if (ch == 1) {
        cout << "Result: " << atbash(text) << "\n";
    } else if (ch == 2) {
        int shift;
        cout << "Enter shift key: ";
        cin >> shift;
        cout << "Result: " << caesar(text, 26 - (shift % 26)) << "\n";
    } else if (ch == 3) {
        int shift;
        cout << "Enter shift key: ";
        cin >> shift;
        cout << "Result: " << caesar(text, shift) << "\n";
    } else if (ch == 4) {
        string key;
        cout << "Enter keyword: ";
        getline(cin, key);
        cout << "Result: " << vigenere(text, key, false) << "\n";
    }
}

void saveScore(string name, int score) {
    ofstream file("scores.txt", ios::app);
    file << name << " : " << score << " pts\n";
    file.close();
}

void showScores() {
    ifstream file("scores.txt");
    string line;
    cout << "\n--- HIGH SCORES ---\n";
    if (!file) {
        cout << "No scores yet.\n";
    }
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

int main() {
    string answers[3] = {"SHADOW PROTOCOL", "FIREWALL BYPASSED", "ROOT ACCESS"};
    string clues[3] = {
        "Clue: Mirror the alphabet (A=Z, B=Y) using Atbash.",
        "Clue: Caesar cipher shifted forward by 7.",
        "Clue: Vigenere cipher with keyword CPU."
    };

    while (true) {
        cout << "\n=== CRYPTO GAME ===\n";
        cout << "1. Play Game\n";
        cout << "2. High Scores\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        int menu;
        cin >> menu;
        cin.ignore();

        if (menu == 1) {
            string name;
            cout << "Enter your name: ";
            getline(cin, name);

            int score = 100;
            int lives = 3;

            for (int lvl = 0; lvl < 3 && lives > 0; lvl++) {
                string encrypted;
                if (lvl == 0) encrypted = atbash(answers[0]);
                if (lvl == 1) encrypted = caesar(answers[1], 7);
                if (lvl == 2) encrypted = vigenere(answers[2], "CPU", true);

                bool passed = false;
                while (!passed && lives > 0) {
                    cout << "\n--- LEVEL " << (lvl + 1) << " ---\n";
                    cout << "Score: " << score << " | Lives: " << lives << "\n";
                    cout << "Encrypted Message: " << encrypted << "\n";
                    cout << "1. Submit Decrypted Answer\n";
                    cout << "2. Open Decoder/Encoder Tool\n";
                    cout << "3. Get Clue (-20 pts)\n";
                    cout << "Choice: ";
                    int act;
                    cin >> act;
                    cin.ignore();

                    if (act == 1) {
                        string guess;
                        cout << "Enter decrypted text: ";
                        getline(cin, guess);

                        if (toUpper(guess) == answers[lvl]) {
                            cout << "Correct! +100 pts!\n";
                            score += 100;

                            cout << "Bonus (+50 pts): Encrypt 'HACK' with Caesar shift 3: ";
                            string bonus;
                            getline(cin, bonus);
                            if (toUpper(bonus) == caesar("HACK", 3)) {
                                cout << "Bonus Correct!\n";
                                score += 50;
                            } else {
                                cout << "Wrong bonus (Answer: KDFN).\n";
                            }
                            passed = true;
                        } else {
                            lives--;
                            score -= 20;
                            cout << "Wrong answer! Lives left: " << lives << "\n";
                        }
                    } else if (act == 2) {
                        decoderTool();
                    } else if (act == 3) {
                        score -= 20;
                        cout << clues[lvl] << "\n";
                    }
                }
            }

            if (lives > 0) {
                cout << "\nYOU WON! Final Score: " << score << "\n";
            } else {
                cout << "\nGAME OVER! Final Score: " << score << "\n";
            }
            saveScore(name, score);
        } else if (menu == 2) {
            showScores();
        } else {
            break;
        }
    }
    return 0;
}