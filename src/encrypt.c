#include <openssl/aes.h>
#include <openssl/rand.h>
#include <stdio.h>
#include "encrypt.h"

void encrypt_file(const char *input_filename, const char *output_filename, const unsigned char *key) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 256, &enc_key);

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
    
    // Инициализация вектора инициализации (IV)
    unsigned char iv[AES_BLOCK_SIZE];
    if (!RAND_bytes(iv, sizeof(iv))) {
        perror("Error generating IV");
        fclose(input_file);
        fclose(output_file);
        return;
    }

    fwrite(iv, sizeof(iv), 1, output_file); // Записываем IV в выходной файл

    int bytes_read;
    while ((bytes_read = fread(buffer, 1, AES_BLOCK_SIZE, input_file)) > 0) {
        AES_cbc_encrypt(buffer, out_buffer, bytes_read, &enc_key, iv, AES_ENCRYPT);
        fwrite(out_buffer, 1, bytes_read, output_file);
    }

    fclose(input_file);
    fclose(output_file);
    printf("File encrypted successfully to %s\n", output_filename);
}
