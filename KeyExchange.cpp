#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate (x^y) % P
long calculatePower(long x, long y, long P) {	
    long result = 1;
    x = x % P; // Ensure x is within modulo P
    while (y > 0) {
        // If y is odd, multiply x with the result
        if (y & 1)
            result = (result * x) % P;

        // y must be even now
        y = y >> 1; // y = y / 2
        x = (x * x) % P; // Change x to x^2
    }
    return result;
}

int main() {
    long P, G, x, a, y, b, ka, kb;

    cout << "Both users should agree upon the public keys G and P\n";

    // Input public keys G and P
    cout << "Enter value for public key G: ";
    cin >> G;
    cout << "Enter value for public key P: ";
    cin >> P;

    // Input private keys a and b
    cout << "Enter value for private key a selected by User1: ";
    cin >> a;
    cout << "Enter value for private key b selected by User2: ";
    cin >> b;

    // Calculate public keys for both users
    x = calculatePower(G, a, P); // User1's public key
    y = calculatePower(G, b, P); // User2's public key

    // Calculate secret keys
    ka = calculatePower(y, a, P); // Secret key for User1
    kb = calculatePower(x, b, P); // Secret key for User2

    // Display secret keys
    cout << "Secret key for User1 is: " << ka << endl;
    cout << "Secret key for User2 is: " << kb << endl;

    return 0;
}
