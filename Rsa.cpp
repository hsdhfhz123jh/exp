#include <bits/stdc++.h>
using namespace std;

// Function to calculate the greatest common divisor (gcd)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular inverse using the extended Euclidean algorithm
double modInverse(double e, double phi) {
    double t = 0, newT = 1;
    double r = phi, newR = e;
    
    while (newR != 0) {
        double quotient = floor(r / newR);
        t = t - quotient * newT;
        r = r - quotient * newR;

        // Swap
        double tmpT = t, tmpR = r;
        t = newT, r = newR;
        newT = tmpT, newR = tmpR;
    }

    if (t < 0)
        t += phi;

    return t;
}

// Function for modular exponentiation
double modExpo(double base, double exp, double mod) {
    double result = 1;
    base = fmod(base, mod);

    while (exp > 0) {
        if (fmod(exp, 2) == 1) {
            result = fmod(result * base, mod);
        }
        exp = floor(exp / 2);
        base = fmod(base * base, mod);
    }

    return result;
}

int main()
{
    
    cout << "Implementation of RSA Algorithm \n";
    
    // Input two prime numbers
    cout << "\nEnter two prime numbers: ";
    double num1, num2;
    cin >> num1 >> num2;

    // Calculate n and phi
    double n = num1 * num2;
    double phi = (num1 - 1) * (num2 - 1);

    // Choose an encryption key 'e'
    double e = 7;
    while (e < phi) {
        if (gcd((int)e, (int)phi) == 1)
            break;
        else
            e++;
    }

    // Calculate the private key 'd' (modular inverse of e modulo phi)
    double d = modInverse(e, phi);

    // Input the message
    double message;
    cout << "\nEnter message: ";
    cin >> message;

    // Encrypt the message
    double c = modExpo(message, e, n);

    // Decrypt the message
    double m = modExpo(c, d, n);

    // Output the results
    cout << "\nOriginal Message = " << message;
    cout << "\n" << "p = " << num1;
    cout << "\n" << "q = " << num2;
    cout << "\n" << "n = pq = " << n;
    cout << "\n" << "phi = " << phi;
    cout << "\n" << "e = " << e;
    cout << "\n" << "d = " << d;
    cout << "\n" << "\nEncrypted message : " << c;
    cout << "\n" << "Decrypted message : " << m;

    return 0;
}
