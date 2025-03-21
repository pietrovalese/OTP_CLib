#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "otp.h"

int main() {
    // Allocazione del messaggio
    const char *text = "HELLO";
    int length = strlen(text);

    uint64_t *message = (uint64_t *)malloc(length + 1);  // +1 per il terminatore
    if (!message) {
        printf("Errore di allocazione memoria!\n");
        return 1;
    }
    strncpy((char *)message, text, length + 1);

    // Generazione della chiave casuale
    uint64_t *key = otp_generate_random_key(length);
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
    uint64_t *ciphertext = otp_encrypt(message, key, length);
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

    uint64_t *decrypted = otp_decrypt(ciphertext, key, length);
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

    otp_encrypt_file("testing/input.txt", "testing/key_file.txt", "testing/output.txt");
    //otp_decrypt_file("testing/output.txt", "testing/key_file.txt", "testing/input.txt");

    return 0;
}
