#include "bbs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

const long long range_start = 10000000000000ULL; // 10^20
const long long range_end = 100000000000000000ULL; // 10^40

// Funzione per generare due numeri primi congrui a 3 modulo 4
void gen_pq_BBS(long *res) {
    srand(time(NULL));

    long p, q;
    do {
        p = range_start + (rand() % (range_end - range_start + 1));
        if (p % 2 == 0) p++;  // Rendi p dispari
        while (!(p % 4 == 3 && is_prime(p))) {
            p += 2;
        }

        q = range_start + (rand() % (range_end - range_start + 1));
        if (q % 2 == 0) q++;  // Rendi q dispari
        while (!(q % 4 == 3 && is_prime(q))) {
            q += 2;
        }
    } while (p == q); // Assicura che p ≠ q

    res[0] = p;
    res[1] = q;
}

// Funzione per generare byte casuali con Blum Blum Shub
void bbs_generate_bytes(uint8_t *buffer, int length) {
    long pq[2];
    gen_pq_BBS(pq);
    long p = pq[0], q = pq[1];
    long num = p * q;

    srand(time(NULL));
    long y = range_start + (rand() % (range_end - range_start + 1));

    // Trova y tale che MCD(y, num) == 1
    while (mcd(y, num) != 1) {
        y++;
    }

    long x = (y * y) % num;
    for (int i = 0; i < length; i++) {
        buffer[i] = (uint8_t)(x & 0xFF); // Prendi solo gli ultimi 8 bit
        x = (x * x) % num;
    }
}

// Funzione per verificare se un numero è primo
bool is_prime(long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Funzione per calcolare il Massimo Comun Divisore (MCD)
long mcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
