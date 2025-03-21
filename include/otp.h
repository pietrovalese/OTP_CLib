#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

uint64_t *otp_encrypt(uint64_t *message, uint64_t *key, int length);
uint64_t *otp_decrypt(uint64_t *encrypted_message, uint64_t *key, int length);
void otp_encrypt_file(const char *input_file, const char *keys_file, const char *output_file);
void otp_decrypt_file(const char *input_file, const char *keys_file, const char *output_file);
void otp_encrypt_file_rand(const char *input_file, const char *key_file, const char *output_file);
uint64_t *otp_generate_random_key(int length);
