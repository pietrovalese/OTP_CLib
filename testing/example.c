#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "otp.h"

int main() {
    // Messaggio da cifrare
    const char *text = "HELLObehwfoigeihpjxnxbchsjelxnvareig0275vvrmcoayegdewofbeubewu3rbfr3ubfr39g2e9736432@#qswqgd@";
    int length = strlen(text);

    // Calcolare la quantità di uint64_t necessari per memorizzare il messaggio
    int num_blocks = (length + sizeof(uint64_t) - 1) / sizeof(uint64_t); // numero di blocchi di 8 byte

    // Allocazione del messaggio come array di uint64_t
    uint64_t *message = (uint64_t *)malloc(num_blocks * sizeof(uint64_t));
    if (!message) {
        printf("Errore di allocazione memoria per il messaggio!\n");
        return 1;
    }

    // Copiare il messaggio nel buffer message come uint64_t
    for (int i = 0; i < num_blocks; i++) {
        message[i] = 0; // inizializza con zero
        for (uint64_t j = 0; j < sizeof(uint64_t); j++) {
            int idx = i * sizeof(uint64_t) + j;
            if (idx < length) {
                message[i] |= (uint64_t)text[idx] << (8 * j); // Combina i caratteri in un uint64_t
            }
        }
    }

    // Generazione della chiave casuale
    uint64_t *key = otp_generate_random_key(num_blocks * sizeof(uint64_t)); // Genera una chiave lunga quanto il messaggio
    if (!key) {
        printf("Errore: impossibile generare la chiave.\n");
        free(message);
        return 1;
    }

    printf("Generated Key: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02lx ", key[i]);
    }
    printf("\n");

    // Allocazione della memoria per il testo cifrato e decifrato
    uint64_t *ciphertext = otp_encrypt(message, key, num_blocks);
    if (!ciphertext) {
        printf("Errore nella cifratura.\n");
        free(message);
        free(key);
        return 1;
    }

    printf("Testo cifrato: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02lX ", ciphertext[i]);
    }
    printf("\n");

    uint64_t *decrypted = otp_decrypt(ciphertext, key, num_blocks);
    if (!decrypted) {
        printf("Errore nella decifratura.\n");
        free(message);
        free(key);
        free(ciphertext);
        return 1;
    }

    printf("Testo decifrato: ");
    for (int i = 0; i < num_blocks; i++) {
        uint64_t block = decrypted[i];
        for (uint64_t j = 0; j < sizeof(uint64_t); j++) {
            unsigned char byte = (unsigned char)(block >> (8 * j)) & 0xFF;
            if (byte != 0) {
                printf("%c", byte); // stampa ogni byte come carattere
            }
        }
    }
    printf("\n");

    // Libera la memoria allocata
    free(ciphertext);
    free(decrypted);
    free(key);
    free(message);

    otp_encrypt_file("testing/input.txt", "testing/key_file.txt", "testing/output.txt");
    //otp_decrypt_file("testing/output.txt", "testing/key_file.txt", "testing/input.txt");

    return 0;
}
