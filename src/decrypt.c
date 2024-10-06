#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include "decrypt.h"

void decrypt_file(const char *input_filename, const char *output_filename, const unsigned char *key) {
    AES_KEY dec_key;
    AES_set_decrypt_key(key, 256, &dec_key);

    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        perror("Error opening input file");
        return;
    }

    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Error opening output file");
        fclose(input_file);
        return;
    }

    unsigned char buffer[AES_BLOCK_SIZE];
    unsigned char out_buffer[AES_BLOCK_SIZE];

    // Читаем вектор инициализации (IV) из входного файла
    unsigned char iv[AES_BLOCK_SIZE];
    if (fread(iv, 1, AES_BLOCK_SIZE, input_file) != AES_BLOCK_SIZE) {
        perror("Error reading IV");
        fclose(input_file);
        fclose(output_file);
        return;
    }

    int bytes_read;
    while ((bytes_read = fread(buffer, 1, AES_BLOCK_SIZE, input_file)) > 0) {
        AES_cbc_encrypt(buffer, out_buffer, bytes_read, &dec_key, iv, AES_DECRYPT);
        fwrite(out_buffer, 1, bytes_read, output_file);
    }

    fclose(input_file);
    fclose(output_file);
    printf("File decrypted successfully to %s\n", output_filename);
}
