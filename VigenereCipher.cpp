#include <iostream>
#include <vector>
#include <cctype>
using namespace std;

int main() {
    cout << "\n===== VIGENERE CIPHER =====\n";
    cout << "1. Encrypt\n2. Decrypt\nEnter choice: ";
    int choice;
    cin >> choice;

    vector<vector<char>> table(26, vector<char>(26));
    // Build the Vigenere table
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            table[i][j] = 'A' + (i + j) % 26;

    string message, key;
    cout << "\nEnter the message (A-Z): ";
    cin >> message;
    cout << "Enter the key: ";
    cin >> key;

    // Convert to uppercase
    for (auto &ch : message) ch = toupper(ch);
    for (auto &ch : key) ch = toupper(ch);

    // Expand key to match message length
    string fullKey = key;
    for (int i = key.size(); i < message.size(); i++)
        fullKey += key[i % key.size()];

    if (choice == 1) {
        // -------- Encryption --------
        string encrypted = "";
        for (int i = 0; i < message.size(); i++) {
            if (isalpha(message[i]))
                encrypted += table[message[i] - 'A'][fullKey[i] - 'A'];
            else
                encrypted += message[i];
        }
        cout << "\nEncrypted Message: " << encrypted << endl;
    }

    else if (choice == 2) {
        // -------- Decryption --------
        string decrypted = "";
        for (int i = 0; i < message.size(); i++) {
            if (isalpha(message[i])) {
                for (int r = 0; r < 26; r++) {
                    if (table[r][fullKey[i] - 'A'] == message[i]) {
                        decrypted += char('A' + r);
                        break;
                    }
                }
            } else
                decrypted += message[i];
        }
        cout << "\nDecrypted Message: " << decrypted << endl;
    }

    else {
        cout << "Invalid Choice!";
    }

    return 0;
}
