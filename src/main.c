#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "encrypt.h"
#include "decrypt.h"
#include "keygen.h"

void print_usage() {
    printf("Usage: file_encryptor -e|-d -f <filename> -p <password>\n");
    printf("  -e            Encrypt the file\n");
    printf("  -d            Decrypt the file\n");
    printf("  -f <file>     File to encrypt/decrypt\n");
    printf("  -p <password> Password for encryption/decryption\n");
}

int main(int argc, char *argv[]) {
    int encrypt = 0, decrypt = 0;
    char *filename = NULL;
    char *password = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "edf:p:")) != -1) {
        switch (opt) {
            case 'e':
                encrypt = 1;
                break;
            case 'd':
                decrypt = 1;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    if ((encrypt && decrypt) || (!encrypt && !decrypt) || filename == NULL || password == NULL) {
        print_usage();
        exit(EXIT_FAILURE);
    }

    unsigned char key[32]; // 256-битный ключ
    generate_key(password, key);

    if (encrypt) {
        encrypt_file(filename, "output.enc", key);
    } else if (decrypt) {
        decrypt_file(filename, "output.dec", key);
    }

    return 0;
}
