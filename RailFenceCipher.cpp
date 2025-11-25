#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "\n===== RAIL FENCE CIPHER =====\n";
    cout << "1. Encrypt\n2. Decrypt\nEnter choice: ";
    int choice;
    cin >> choice;

    string text;
    int key;

    cout << "\nEnter the message: ";
    cin >> text;
    cout << "Enter key (number of rails): ";
    cin >> key;

    int len = text.size();
    vector<vector<char>> rail(key, vector<char>(len, '\n'));

    if (choice == 1) {
        // ---------------- ENCRYPTION ----------------
        int row = 0, dir = 1;
        for (int i = 0; i < len; i++) {
            rail[row][i] = text[i];

            if (row == 0) dir = 1;
            else if (row == key - 1) dir = -1;

            row += dir;
        }

        string encrypted = "";
        for (int i = 0; i < key; i++)
            for (int j = 0; j < len; j++)
                if (rail[i][j] != '\n')
                    encrypted += rail[i][j];

        cout << "\nEncrypted Message: " << encrypted << endl;
    }

    else if (choice == 2) {
        // ---------------- DECRYPTION ----------------
        int row = 0, dir = 1;

        // 1. Mark the zigzag
        for (int i = 0; i < len; i++) {
            rail[row][i] = '*';
            if (row == 0) dir = 1;
            else if (row == key - 1) dir = -1;
            row += dir;
        }

        // 2. Fill cipher text characters into positions
        int index = 0;
        for (int i = 0; i < key; i++)
            for (int j = 0; j < len; j++)
                if (rail[i][j] == '*' && index < len)
                    rail[i][j] = text[index++];

        // 3. Read using zigzag pattern
        string decrypted = "";
        row = 0, dir = 1;
        for (int i = 0; i < len; i++) {
            decrypted += rail[row][i];
            if (row == 0) dir = 1;
            else if (row == key - 1) dir = -1;
            row += dir;
        }

        cout << "\nDecrypted Message: " << decrypted << endl;
    }

    else {
        cout << "Invalid Choice!";
    }

    return 0;
}
