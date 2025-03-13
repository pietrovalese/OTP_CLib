#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "otp.h"

int main() {
    // Allocazione del messaggio
    const char *text = "HELLO";
    int length = strlen(text);

    uint8_t *message = (uint8_t *)malloc(length + 1);  // +1 per il terminatore
    if (!message) {
        printf("Errore di allocazione memoria!\n");
        return 1;
    }
    strncpy((char *)message, text, length + 1);

    // Generazione della chiave casuale
    uint8_t *key = otp_generate_random_key(length);
    if (!key) {
        printf("Errore: impossibile generare la chiave.\n");
        free(message);
        return 1;
    }

    printf("Generated Key: ");
    for (int i = 0; i < length; i++) {
        printf("%02x ", key[i]);
    }
    printf("\n");

    // Allocazione della memoria per il testo cifrato e decifrato
    uint8_t *ciphertext = otp_encrypt(message, key, length);
    if (!ciphertext) {
        printf("Errore nella cifratura.\n");
        free(message);
        free(key);
        return 1;
    }

    printf("Testo cifrato: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    uint8_t *decrypted = otp_decrypt(ciphertext, key, length);
    if (!decrypted) {
        printf("Errore nella decifratura.\n");
        free(message);
        free(key);
        free(ciphertext);
        return 1;
    }

    printf("Testo decifrato: %s\n", decrypted);

    // Libera la memoria allocata
    free(ciphertext);
    free(decrypted);
    free(key);
    free(message);

    return 0;
}
