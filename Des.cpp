#include <bits/stdc++.h>
using namespace std;

// ==================== Original SDES Helpers ====================

string permute(const string &in, const vector<int> &p) {
    string out = "";
    out.reserve(p.size());
    for (int i : p) out.push_back(in[i - 1]);
    return out;
}

string leftshift(const string &s, int n) {
    string r = s;
    rotate(r.begin(), r.begin() + n, r.end());
    return r;
}

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

string xorbits(const string &a, const string &b) {
    string r = "";
    for (int i = 0; i < a.size(); i++) 
        r += (a[i] == b[i]) ? '0' : '1';
    return r;
}

string toBinary2(int x) {
    return string("") 
        + ((x & 2) ? '1' : '0')
        + ((x & 1) ? '1' : '0');
}

string fk(const string &bits, const string &key) {
    string L = bits.substr(0, 4);
    string R = bits.substr(4, 4);

    vector<int> EP = {4,1,2,3,2,3,4,1};
    string R_EP = permute(R, EP);
    string temp = xorbits(R_EP, key);

    string left4  = temp.substr(0, 4);
    string right4 = temp.substr(4, 4);

    int row0 = (left4[0] - '0') * 2 + (left4[3] - '0');
    int col0 = (left4[1] - '0') * 2 + (left4[2] - '0');
    int out0 = S0[row0][col0];

    int row1 = (right4[0] - '0') * 2 + (right4[3] - '0');
    int col1 = (right4[1] - '0') * 2 + (right4[2] - '0');
    int out1 = S1[row1][col1];

    string S_output = toBinary2(out0) + toBinary2(out1);

    vector<int> P4 = {2,4,3,1};
    string P4out = permute(S_output, P4);

    string L_new = xorbits(L, P4out);
    return L_new + R;
}

pair<string,string> generateKeys(const string &key10) {
    vector<int> P10 = {3,5,2,7,4,10,1,9,8,6};
    string perm = permute(key10, P10);

    string L = perm.substr(0, 5);
    string R = perm.substr(5, 5);

    L = leftshift(L, 1);
    R = leftshift(R, 1);

    vector<int> P8 = {6,3,7,4,8,5,10,9};
    string K1 = permute(L + R, P8);

    L = leftshift(L, 2);
    R = leftshift(R, 2);

    string K2 = permute(L + R, P8);
    return {K1, K2};
}

string encryptBlock(const string &pt8, const string &K1, const string &K2) {
    vector<int> IP     = {2,6,3,1,4,8,5,7};
    vector<int> IPinv  = {4,1,3,5,7,2,8,6};

    string x = permute(pt8, IP);

    x = fk(x, K1);

    x = x.substr(4,4) + x.substr(0,4);

    x = fk(x, K2);

    return permute(x, IPinv);
}

string decryptBlock(const string &ct8, const string &K1, const string &K2) {
    return encryptBlock(ct8, K2, K1);
}

// ==================== Binary <-> Text + HEX Helpers ====================

string charToBin(unsigned char c) {
    string b = "";
    for (int i = 7; i >= 0; i--)
        b += ((c >> i) & 1) ? '1' : '0';
    return b;
}

unsigned char binToChar(const string &b) {
    unsigned char v = 0;
    for (char c : b)
        v = (v << 1) | (c - '0');
    return v;
}

string binToHex(const string &bin) {
    string hex = "";
    for (int i = 0; i < bin.size(); i += 4) {
        int val = stoi(bin.substr(i, 4), nullptr, 2);
        hex += "0123456789ABCDEF"[val];
    }
    return hex;
}

string hexToBin(const string &hex) {
    string bin = "";
    for (char c : hex) {
        int x = (c >= '0' && c <= '9') ? c - '0'
              : toupper(c) - 'A' + 10;
        for (int i = 3; i >= 0; i--)
            bin += ((x >> i) & 1) ? '1' : '0';
    }
    return bin;
}

// ==================== MAIN ====================

int main() {
    string key10;
    cout << "Enter 10-bit key: ";
    cin >> key10;

    auto [K1, K2] = generateKeys(key10);

    cin.ignore();
    cout << "Enter plaintext text: ";
    string text;
    getline(cin, text);

    string ciphertext_hex = "";

    for (char c : text) {
        string pt8 = charToBin(c);
        string ct8 = encryptBlock(pt8, K1, K2);
        ciphertext_hex += binToHex(ct8);
    }

    cout << "Ciphertext (hex): " << ciphertext_hex << "\n";

    // Decrypt back
    string decrypted = "";
    for (int i = 0; i < ciphertext_hex.size(); i += 2) {
        string ct8 = hexToBin(ciphertext_hex.substr(i, 2));
        string pt8 = decryptBlock(ct8, K1, K2);
        decrypted += binToChar(pt8);
    }

    cout << "Decrypted text: " << decrypted << "\n";

    return 0;
}