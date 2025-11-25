#include <iostream>
#include <vector>
using namespace std;

int modInverse(int a, int m) {
    a = a % m;
    for (int x = -m; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 0;
}

void getCofactor(vector<vector<int>> &a, vector<vector<int>> &temp, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = a[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(vector<vector<int>> &a, int n, int N) {
    int D = 0;
    if (n == 1) return a[0][0];

    vector<vector<int>> temp(N, vector<int>(N));
    int sign = 1;

    for (int f = 0; f < n; f++) {
        getCofactor(a, temp, 0, f, n);
        D += sign * a[0][f] * determinant(temp, n - 1, N);
        sign = -sign;
    }
    return D;
}

void adjoint(vector<vector<int>> &a, vector<vector<int>> &adj, int N) {
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }

    int sign;
    vector<vector<int>> temp(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            getCofactor(a, temp, i, j, N);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adj[j][i] = sign * determinant(temp, N - 1, N);
        }
    }
}

bool inverse(vector<vector<int>> &a, vector<vector<int>> &inv, int N) {
    int det = determinant(a, N, N);
    if (det == 0) {
        cout << "\nInverse does not exist!";
        return false;
    }

    int invDet = modInverse(det, 26);
    cout << "\nDeterminant: " << det % 26 << "  |  Inverse Determinant: " << invDet << endl;

    vector<vector<int>> adj(N, vector<int>(N));
    adjoint(a, adj, N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inv[i][j] = (adj[i][j] * invDet) % 26;

    return true;
}

int main() {
    int choice;
    cout << "\n===== HILL CIPHER =====\n";
    cout << "1. Encryption\n2. Decryption\nEnter choice: ";
    cin >> choice;

    int n, i, j, k;
    cout << "\nEnter size of key matrix: ";
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    cout << "Enter the key matrix:\n";
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            cin >> a[i][j];

    if (choice == 1) {
        // ------- ENCRYPTION -------
        cout << "\nEnter message to encrypt: ";
        string s, ans = "";
        cin >> s;

        int temp = (n - s.size() % n) % n;
        while (temp--) s += 'x';

        k = 0;
        while (k < s.size()) {
            for (i = 0; i < n; i++) {
                int sum = 0, pos = k;
                for (j = 0; j < n; j++)
                    sum += (a[i][j] * (s[pos++] - 'a')) % 26;
                ans += (sum % 26 + 'a');
            }
            k += n;
        }
        cout << "\nEncrypted Message: " << ans << endl;
    }

    else if (choice == 2) {
        // ------- DECRYPTION -------
        vector<vector<int>> inv(n, vector<int>(n));

        if (!inverse(a, inv, n)) return 0;

        cout << "\nEnter message to decrypt: ";
        string s, ans = "";
        cin >> s;

        k = 0;
        while (k < s.size()) {
            for (i = 0; i < n; i++) {
                int sum = 0, pos = k;
                for (j = 0; j < n; j++)
                    sum += ((inv[i][j] + 26) % 26 * (s[pos++] - 'a')) % 26;
                ans += (sum % 26 + 'a');
            }
            k += n;
        }

        // remove padding 'x'
        int f = ans.size() - 1;
        while (f >= 0 && ans[f] == 'x') f--;

        cout << "\nDecrypted Message: ";
        for (i = 0; i <= f; i++) cout << ans[i];
        cout << endl;
    }

    else {
        cout << "\nInvalid Choice!";
    }

    return 0;
}
