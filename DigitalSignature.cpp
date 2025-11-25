#include <iostream>
#include <string>
#include <openssl/evp.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

using namespace std;

// Base64 Encoding Function
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
    OpenSSL_add_all_algorithms();

    cout << "Enter message to sign: ";
    string message;
    getline(cin, message);

    // ===== Generate DSA Key Pair =====
    DSA* dsa = DSA_new();
    DSA_generate_parameters_ex(dsa, 2048, NULL, 0, NULL, NULL, NULL);
    DSA_generate_key(dsa);

    EVP_PKEY* pkey = EVP_PKEY_new();
    EVP_PKEY_assign_DSA(pkey, dsa);

    // ===== Sign the message =====
    EVP_MD_CTX* signCtx = EVP_MD_CTX_new();
    EVP_DigestSignInit(signCtx, NULL, EVP_sha256(), NULL, pkey);
    EVP_DigestSignUpdate(signCtx, message.c_str(), message.length());

    size_t sigLen = 0;
    EVP_DigestSignFinal(signCtx, NULL, &sigLen);

    unsigned char* signature = new unsigned char[sigLen];
    EVP_DigestSignFinal(signCtx, signature, &sigLen);
    EVP_MD_CTX_free(signCtx);

    // Base64 signature output
    string encodedSig = base64Encode(signature, sigLen);
    cout << "\nDigital Signature (Base64): " << encodedSig << endl;

    // ===== Verify the signature =====
    EVP_MD_CTX* verifyCtx = EVP_MD_CTX_new();
    EVP_DigestVerifyInit(verifyCtx, NULL, EVP_sha256(), NULL, pkey);
    EVP_DigestVerifyUpdate(verifyCtx, message.c_str(), message.length());

    int verified = EVP_DigestVerifyFinal(verifyCtx, signature, sigLen);
    EVP_MD_CTX_free(verifyCtx);

    cout << "\nVerification: " << (verified == 1 ? "SUCCESS ✓" : "FAILED ✗") << endl;

    delete[] signature;
    EVP_PKEY_free(pkey);

    return 0;
}
