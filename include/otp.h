#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

uint8_t *otp_encrypt(uint8_t *message, uint8_t *key, int length);
uint8_t *otp_decrypt(uint8_t *encrypted_message, uint8_t *key, int length);
void file_to_otp(const char *input_file, const char *output_file);
uint8_t *otp_generate_random_key(int length);
