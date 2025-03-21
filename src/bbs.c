#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/random.h>  
#include "Miller_Rabin_PT.h" 
#include "bbs.h"

#define RANGE_START 1000000
#define RANGE_END 100000000

// Funzione per calcolare il Massimo Comun Divisore (MCD)
static long long mcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint64_t get_secure_random() {
    uint64_t r;
    if (getrandom(&r, sizeof(r), 0) != sizeof(r)) {
        perror("Errore in getrandom()");
        exit(EXIT_FAILURE);
    }
    return r;
}

// Genera un numero primo congruo a 3 modulo 4
long long generate_prime_mod4_3(long long start, long long end) {
    long long p;
    do {
        p = start + (get_secure_random() % (end - start + 1));
        if (p % 2 == 0) p++;  // Rendi p dispari
        while (!(p % 4 == 3 && Test_Miller_Rabin(p))) {
            p += 2;
        }
    } while (p < start || p > end);
    return p;
}

// Genera due numeri primi p e q congrui a 3 modulo 4
void gen_pq_BBS(long long *res) {
    long long p = generate_prime_mod4_3(RANGE_START, RANGE_END);
    long long q;
    do {
        q = generate_prime_mod4_3(RANGE_START, RANGE_END);
    } while (p == q);  // Assicura che p ≠ q

    res[0] = p;
    res[1] = q;
}

// Genera un valore iniziale y tale che MCD(y, num) == 1
long long generate_secure_y(long long num) {
    long long y = get_secure_random() % (RANGE_END - RANGE_START) + RANGE_START;
    while (mcd(y, num) != 1) {
        y++;
    }
    return y;
}

// Genera una sequenza di byte casuali con Blum Blum Shub
void bbs_generate_bytes(uint64_t *buffer, int length) {
    long long pq[2];
    gen_pq_BBS(pq);
    long long p = pq[0], q = pq[1];
    long long num = p * q;

    long long y = generate_secure_y(num);
    long long x = (y * y) % num;

    for (int i = 0; i < length; i++) {
        buffer[i] = (uint64_t)(x & 0xFF);  // Prendi gli ultimi 8 bit
        x = (x * x) % num;
    }
}
