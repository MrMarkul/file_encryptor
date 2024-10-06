#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include "keygen.h"

void generate_key(const char *password, unsigned char *key) {
    // Используем PBKDF2 (Password-Based Key Derivation Function 2) для генерации ключа
    const unsigned char salt[] = "some_salt";  // В реальной программе лучше использовать случайный соль
    int iterations = 10000;                    // Количество итераций для усиления защиты
    if (!PKCS5_PBKDF2_HMAC(password, strlen(password), salt, sizeof(salt), iterations, EVP_sha256(), 32, key)) {
        perror("Error generating key");
    }
}
