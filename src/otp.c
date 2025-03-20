#include "otp.h"
#include "bbs.h"

static char *hex_to_string(const char *hex);
static void convert_hex_file_to_string(const char *input_file, const char *output_file);


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

static char **read_from_file(const char *input_file, int *num_righe) {
    FILE *file = fopen(input_file, "r");
    if (!file) {
        perror("Errore nell'apertura del file");
        return NULL;
    }

    char **righe = NULL;
    *num_righe = 0;
    size_t len = 0;
    char *line = NULL;

    while (getline(&line, &len, file) != -1) {
        righe = realloc(righe, (*num_righe + 1) * sizeof(char *));
        if (!righe) {
            perror("Errore di allocazione memoria");
            free(line);
            fclose(file);
            return NULL;
        }

        // Rimuove il newline finale, se presente
        size_t lunghezza = strlen(line);
        if (line[lunghezza - 1] == '\n') {
            line[lunghezza - 1] = '\0';
        }

        righe[*num_righe] = strdup(line);
        if (!righe[*num_righe]) {
            perror("Errore di allocazione memoria per una riga");
            free(line);
            fclose(file);

            // Libera le righe già allocate prima di uscire
            for (int i = 0; i < *num_righe; i++) {
                free(righe[i]);
            }
            free(righe);
            return NULL;
        }

        (*num_righe)++;
    }

    free(line);
    fclose(file);
    return righe;
}

void otp_encrypt_file(const char *input_file, const char *keys_file, const char *output_file) {
    int num_righe_input, num_righe_key;
    char **file_data = read_from_file(input_file, &num_righe_input);
    char **key_data = read_from_file(keys_file, &num_righe_key);

    if (!file_data || !key_data) {
        printf("Errore nella lettura dei file.\n");
        return;
    }

    if (num_righe_input != num_righe_key) {
        printf("Errore: il numero di righe nei file non coincide.\n");

        // Libera memoria allocata
        for (int i = 0; i < num_righe_input; i++) free(file_data[i]);
        for (int i = 0; i < num_righe_key; i++) free(key_data[i]);
        free(file_data);
        free(key_data);
        return;
    }

    FILE *out_file = fopen(output_file, "w");
    if (!out_file) {
        perror("Errore nella creazione del file crittografato");

        // Libera memoria allocata
        for (int i = 0; i < num_righe_input; i++) free(file_data[i]);
        for (int i = 0; i < num_righe_key; i++) free(key_data[i]);
        free(file_data);
        free(key_data);
        return;
    }

    printf("Contenuto crittografato del file:\n");
    for (int i = 0; i < num_righe_input; i++) {
        int length = strlen(file_data[i]);

        if (length == 0) {
            printf("Avviso: la riga %d non è stata crittografata (vuota).\n", i);
            continue;
        }

        uint8_t *encrypted = otp_encrypt((uint8_t *)file_data[i], (uint8_t *)key_data[i], length);

        if (encrypted) {
            for (int j = 0; j < length; j++) {
                fprintf(out_file, "%02X ", encrypted[j]);
            }
            fprintf(out_file, "\n");
            free(encrypted);
        }

        free(file_data[i]);
        free(key_data[i]);
    }

    free(file_data);
    free(key_data);

    convert_hex_file_to_string(output_file, output_file);

    fclose(out_file);
}

void otp_decrypt_file(const char *input_file, const char *keys_file, const char *output_file) {
    int num_righe_input, num_righe_key;
    char **file_data = read_from_file(input_file, &num_righe_input);
    char **key_data = read_from_file(keys_file, &num_righe_key);

    if (!file_data || !key_data) {
        printf("Errore nella lettura dei file.\n");
        return;
    }

    if (num_righe_input != num_righe_key) {
        printf("Errore: il numero di righe nei file non coincide.\n");

        // Libera memoria allocata
        for (int i = 0; i < num_righe_input; i++) free(file_data[i]);
        for (int i = 0; i < num_righe_key; i++) free(key_data[i]);
        free(file_data);
        free(key_data);
        return;
    }

    FILE *out_file = fopen(output_file, "w");
    if (!out_file) {
        perror("Errore nella creazione del file crittografato");

        // Libera memoria allocata
        for (int i = 0; i < num_righe_input; i++) free(file_data[i]);
        for (int i = 0; i < num_righe_key; i++) free(key_data[i]);
        free(file_data);
        free(key_data);
        return;
    }

    printf("Contenuto crittografato del file:\n");
    for (int i = 0; i < num_righe_input; i++) {
        int length = strlen(file_data[i]);

        if (length == 0) {
            printf("Avviso: la riga %d non è stata crittografata (vuota).\n", i);
            continue;
        }

        uint8_t *decrypted = otp_decrypt((uint8_t *)file_data[i], (uint8_t *)key_data[i], length);

        if (decrypted) {
            for (int j = 0; j < length; j++) {
                fprintf(out_file, "%02X ", decrypted[j]);
            }
            fprintf(out_file, "\n");
            free(decrypted);
        }

        free(file_data[i]);
        free(key_data[i]);
    }

    free(file_data);
    free(key_data);

    convert_hex_file_to_string(output_file, output_file);

    fclose(out_file);
}


void otp_encrypt_file_rand(const char *input_file, const char *keys_file, const char *output_file) {

    int num_righe;
    char **file_data = read_from_file(input_file, &num_righe);

    if (file_data == NULL) {
        printf("Errore nella lettura del file.\n");
        return;
    }

    FILE *out_file = fopen(output_file, "w");
    if (!out_file) {
        perror("Errore nella creazione del file crittografato");
        return;
    }

    FILE *key_file = fopen(keys_file, "w");
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


static char *hex_to_string(const char *hex) {
    if (!hex) return NULL;

    size_t len = strlen(hex);
    if (len % 2 != 0) {
        fprintf(stderr, "Errore: la stringa esadecimale deve avere una lunghezza pari.\n");
        return NULL;
    }

    size_t str_len = len / 2;
    char *str = malloc(str_len + 1);
    if (!str) {
        perror("Errore di allocazione memoria");
        return NULL;
    }

    for (size_t i = 0; i < str_len; i++) {
        sscanf(hex + (i * 2), "%2hhx", &str[i]);  // Converte ogni coppia di caratteri esadecimali in un byte
    }
    str[str_len] = '\0';

    return str;
}

// Funzione per convertire un file esadecimale in una stringa
static void convert_hex_file_to_string(const char *input_file, const char *output_file) {
    FILE *in_file = fopen(input_file, "r");
    if (!in_file) {
        perror("Errore nell'apertura del file di input");
        return;
    }

    FILE *out_file = fopen(output_file, "w");
    if (!out_file) {
        perror("Errore nella creazione del file di output");
        fclose(in_file);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, in_file)) != -1) {
        // Rimuove il newline finale, se presente
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        char *decoded = hex_to_string(line);
        if (decoded) {
            fprintf(out_file, "%s\n", decoded);
            printf("Decodificato: %s\n", decoded);  // Stampa a console per debugging
            free(decoded);
        }
    }

    free(line);
    fclose(in_file);
    fclose(out_file);
}