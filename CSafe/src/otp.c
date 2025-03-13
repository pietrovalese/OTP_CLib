#include "otp.h"
#include "bbs.h"

uint8_t *otp_encrypt(uint8_t *message, uint8_t *key, int length) {
    if (!message || !key) {
        printf("Errore: messaggio o chiave null!\n");
        return NULL;
    }

    uint8_t *encrypted_message = (uint8_t *)malloc(length);
    if (!encrypted_message) {
        printf("Errore di allocazione memoria per il messaggio cifrato (riga %d, file %s)\n", __LINE__, __FILE__);
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        encrypted_message[i] = message[i] ^ key[i];
    }

    return encrypted_message;
}

uint8_t *otp_decrypt(uint8_t *encrypted_message, uint8_t *key, int length) {
    if (!encrypted_message || !key) {
        printf("Errore: messaggio cifrato o chiave null!\n");
        return NULL;
    }

    uint8_t *decrypted_message = (uint8_t *)malloc(length);
    if (!decrypted_message) {
        printf("Errore di allocazione memoria per il messaggio decifrato (riga %d, file %s)\n", __LINE__, __FILE__);
        exit(1);
    }

    for (int i = 0; i < length; i++) {
        decrypted_message[i] = encrypted_message[i] ^ key[i];
    }

    return decrypted_message;
}

static void file_analyzer(const char *nome_file, int *num_righe, int *max_lunghezza) {
    FILE *file = fopen(nome_file, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return;
    }

    char buffer[1024];
    *num_righe = 0;
    *max_lunghezza = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        (*num_righe)++;
        int lunghezza = strlen(buffer);
        if (lunghezza > *max_lunghezza) {
            *max_lunghezza = lunghezza;
        }
    }

    fclose(file);
}

static char **read_from_file(const char *nome_file, int *num_righe) {
    int MAX_LUNGHEZZA, MAX_RIGHE;
    file_analyzer(nome_file, &MAX_RIGHE, &MAX_LUNGHEZZA);

    FILE *file = fopen(nome_file, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        return NULL;
    }

    char **righe = malloc(MAX_RIGHE * sizeof(char *));
    if (righe == NULL) {
        perror("Errore di allocazione memoria");
        fclose(file);
        return NULL;
    }

    char *buffer = malloc((MAX_LUNGHEZZA + 1) * sizeof(char));
    if (buffer == NULL) {
        perror("Errore di allocazione buffer");
        free(righe);
        fclose(file);
        return NULL;
    }

    *num_righe = 0;

    while (fgets(buffer, MAX_LUNGHEZZA + 1, file) != NULL && *num_righe < MAX_RIGHE) {
        righe[*num_righe] = malloc(strlen(buffer) + 1);
        if (righe[*num_righe] == NULL) {
            perror("Errore di allocazione memoria per una riga");
            break;
        }
        strcpy(righe[*num_righe], buffer);
        (*num_righe)++;
    }

    free(buffer);
    fclose(file);
    return righe;
}


void file_to_otp(const char *nome_file, const char *output_file) {
    int num_righe;
    char **file_data = read_from_file(nome_file, &num_righe);

    if (file_data == NULL) {
        printf("Errore nella lettura del file.\n");
        return;
    }

    FILE *out_file = fopen(output_file, "a");
    if (!out_file) {
        perror("Errore nella creazione del file crittografato");
        return;
    }

    FILE *key_file = fopen("src/key.txt", "a");
    if (!key_file) {
        perror("Errore nella creazione del file delle chiavi");
        fclose(out_file);
        return;
    }

    printf("Contenuto crittografato del file:\n");
    for (int i = 0; i < num_righe; i++) {
        int length = strlen(file_data[i]);  // File_data è una stringa, quindi strlen va bene qui

        if (length == 0) {
            printf("Avviso: la riga %d non è stata crittografata (vuota).\n", i);
            continue;
        }

        uint8_t *key = otp_generate_random_key(length);
        uint8_t *encrypted = otp_encrypt((uint8_t *)file_data[i], key, length);

        if (encrypted) {
            // Scrive i dati crittografati in formato esadecimale
            for (int j = 0; j < length; j++) {
                fprintf(out_file, "%02X ", encrypted[j]);
                fprintf(key_file, "%02X ", key[j]);
            }
            fprintf(out_file, "\n");
            fprintf(key_file, "\n");

            free(encrypted);
        }

        free(key);
        free(file_data[i]);
    }

    free(file_data);
    fclose(key_file);
    fclose(out_file);
}


uint8_t *otp_generate_random_key(int length){
    uint8_t *key = (uint8_t *)malloc(sizeof(uint8_t) * length);
    if (!key) {
        printf("Errore di allocazione della chiave!\n");
        exit(1);
    }
    bbs_generate_bytes(key, length);  // Scrive direttamente sulla chiave
    return key;
}

