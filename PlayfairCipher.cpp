#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void createMatrix(string key, vector<vector<char>> &a) {
    map<char, int> mp;
    int k = 0, i, j;
    int n = 5;

    // Fill using key characters
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            while (k < key.size() && mp[key[k]] > 0)
                k++;

            if (k < key.size()) {
                a[i][j] = key[k];
                mp[key[k]]++;
            } else break;
        }
        if (k == key.size()) break;
    }

    k = 0;
    // Fill remaining letters
    for (; i < n; i++) {
        for (; j < n; j++) {
            while (k < 26 && mp[char(k + 'a')] > 0)
                k++;

            if (char(k + 'a') == 'j') { j--; k++; continue; }
            if (k < 26) {
                a[i][j] = char(k + 'a');
                mp[char(k + 'a')]++;
            }
        }
        j = 0;
    }
}

string encrypt(string s, vector<vector<char>> &a) {
    string ans = "";
    map<char, pair<int,int>> mp2;

    // Map each character to its coordinates
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mp2[a[i][j]] = make_pair(i, j);

    // Prepare string
    if (s.size() % 2 == 1) s += "z";
    for (int i = 0; i < s.size() - 1; i++)
        if (s[i] == s[i+1]) s[i+1] = 'x';

    // Encrypt process
    for (int i = 0; i < s.size() - 1; i += 2) {
        int y1 = mp2[s[i]].first,  x1 = mp2[s[i]].second;
        int y2 = mp2[s[i + 1]].first,  x2 = mp2[s[i + 1]].second;

        if (y1 == y2) {
            ans += a[y1][(x1 + 1) % 5];
            ans += a[y1][(x2 + 1) % 5];
        } else if (x1 == x2) {
            ans += a[(y1 + 1) % 5][x1];
            ans += a[(y2 + 1) % 5][x2];
        } else {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }
    return ans;
}

string decrypt(string s, vector<vector<char>> &a) {
    string ans = "";
    map<char, pair<int,int>> mp2;

    // Map each character to matrix positions
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            mp2[a[i][j]] = make_pair(i, j);

    // Decrypt process
    for (int i = 0; i < s.size() - 1; i += 2) {
        int y1 = mp2[s[i]].first,  x1 = mp2[s[i]].second;
        int y2 = mp2[s[i + 1]].first,  x2 = mp2[s[i + 1]].second;

        if (y1 == y2) {
            ans += a[y1][(x1 + 4) % 5];
            ans += a[y1][(x2 + 4) % 5];
        } else if (x1 == x2) {
            ans += a[(y1 + 4) % 5][x1];
            ans += a[(y2 + 4) % 5][x2];
        } else {
            ans += a[y1][x2];
            ans += a[y2][x1];
        }
    }
    return ans;
}

int main() {
    int choice;
    cout << "\n===== PLAYFAIR CIPHER =====\n";
    cout << "1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    string text, key, s;
    cout << "\nEnter text: ";
    getline(cin, text);

    cout << "Enter key: ";
    cin >> key;

    // Remove spaces
    for (char c : text)
        if (c != ' ') s += c;

    vector<vector<char>> a(5, vector<char>(5, ' '));
    createMatrix(key, a);

    if (choice == 1) {
        string enc = encrypt(s, a);
        cout << "\nEncrypted Message: " << enc << endl;
    } else if (choice == 2) {
        string dec = decrypt(s, a);
        cout << "\nDecrypted Message: " << dec << endl;
    } else {
        cout << "\nInvalid Choice!";
    }

    return 0;
}
