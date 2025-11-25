#include <bits/stdc++.h>
using namespace std;


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


pair<string,string> generateKeys(const string &key10) {
    vector<int> P10 = {3,5,2,7,4,10,1,9,8,6};
    string perm = permute(key10, P10);

    
    string L = perm.substr(0, 5);
    string R = perm.substr(5, 5);

   
    L = leftshift(L, 1);
    R = leftshift(R, 1);

    vector<int> P8 = {6,3,7,4,8,5,10,9};
    string K1 = permute(L + R, P8);   // Key 1


    L = leftshift(L, 2);
    R = leftshift(R, 2);

    string K2 = permute(L + R, P8);   // Key 2

    return {K1, K2};
}

int main() {
    string key10;
    cout << "Enter 10-bit key: ";
    cin >> key10;

    auto [K1, K2] = generateKeys(key10);

    cout << "Generated K1: " << K1 << endl;
    cout << "Generated K2: " << K2 << endl;
    return 0;
}
