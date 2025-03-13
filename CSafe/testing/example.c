#include <stdio.h>
#include <string.h>
#include "otp.h"

int main() {
    uint8_t *message = (uint8_t *)malloc(6);  // +1 per il terminatore \0
    if (!message) {
        printf("Errore di allocazione memoria!\n");
        exit(1);
    }
    strcpy((char *)message, "HELLO");
    int length = strlen((char *)message);

    uint8_t *key;
    printf("Sei arrivato a %d, %s",__LINE__,__FILE__);
    do {
        key = otp_generate_random_key(length);
        if (!key) {
            printf("Errore: impossibile generare la chiave.\n");
            exit(1);
        }
    } while (key[length - 1] == '\0');  // Assicura che l'ultimo byte non sia '\0'
    
    printf("Generated Key: ");
    for (int i = 0; i < length; i++) {
        printf("%02x ", key[i]);  // Stampa ogni byte in esadecimale
    }
    printf("\n");

    uint8_t *ciphertext=(uint8_t *)malloc(sizeof(uint8_t)*length);
    uint8_t *decrypted=(uint8_t *)malloc(sizeof(uint8_t)*length);

    ciphertext=otp_encrypt(message, key, length);
    printf("Testo cifrato: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", (uint8_t)ciphertext[i]);  // Stampa in esadecimale
    }
    printf("\n");

    decrypted=otp_decrypt(ciphertext, key,length);

    printf("Testo decifrato: %s\n", decrypted);

    free(ciphertext);
    free(decrypted);
    free(key);
    free(message);

    return 0;
}
