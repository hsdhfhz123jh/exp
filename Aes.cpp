#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

using namespace std;

// Convert bytes to hex
string bytesToHex(const unsigned char* data, int len) {
    stringstream ss;
    for (int i = 0; i < len; i++)
        ss << hex << setw(2) << setfill('0') << (int)data[i];
    return ss.str();
}

// Base64 encode function
string base64Encode(const unsigned char* buffer, size_t length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, buffer, length);
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    string encoded(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);
    return encoded;
}

int main() {
    cout << "AES Encryption/Decryption (128-bit)\n";

    string keyInput;
    cout << "Enter 16-character key: ";
    getline(cin, keyInput);

    if (keyInput.length() != 16) {
        cout << "Error: Key must be exactly 16 characters.\n";
        return 0;
    }

    unsigned char key[16];
    memcpy(key, keyInput.c_str(), 16);

    cout << "Enter plaintext: ";
    string plaintext;
    getline(cin, plaintext);

    unsigned char encrypted[128];
    unsigned char decrypted[128];
    int encryptedLen = 0, decryptedLen = 0;

    // --- AES Encryption using EVP ---
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 1);

    EVP_EncryptUpdate(ctx, encrypted, &encryptedLen, (unsigned char*)plaintext.c_str(), plaintext.length());
    int finalLen = 0;
    EVP_EncryptFinal_ex(ctx, encrypted + encryptedLen, &finalLen);
    encryptedLen += finalLen;

    EVP_CIPHER_CTX_free(ctx);

    // Output encrypted formats
    cout << "\nEncrypted (Hex): " << bytesToHex(encrypted, encryptedLen) << endl;
    cout << "Encrypted (Base64): " << base64Encode(encrypted, encryptedLen) << endl;

    // --- AES Decryption ---
    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);
    EVP_CIPHER_CTX_set_padding(ctx, 1);

    EVP_DecryptUpdate(ctx, decrypted, &decryptedLen, encrypted, encryptedLen);
    int finalDecLen = 0;
    EVP_DecryptFinal_ex(ctx, decrypted + decryptedLen, &finalDecLen);
    decryptedLen += finalDecLen;

    EVP_CIPHER_CTX_free(ctx);

    decrypted[decryptedLen] = '\0';
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
