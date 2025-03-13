#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "Miller_Rabin_PT.h"
#include "bbs.h"


static const long long range_start = 1000000;
static const long long range_end = 100000000;


// Funzione per calcolare il Massimo Comun Divisore (MCD)
static long long mcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Funzione per generare due numeri primi congrui a 3 modulo 4
void gen_pq_BBS(long long *res) {
    srand(time(NULL));

    long long p, q;
    do {
        p = range_start + (rand() % (range_end - range_start + 1));
        if (p % 2 == 0) p++;  // Rendi p dispari
        while (!(p % 4 == 3 && Test_Miller_Rabin(p))) {
            p += 2;
        }

        q = range_start + (rand() % (range_end - range_start + 1));
        if (q % 2 == 0) q++;  // Rendi q dispari
        while (!(q % 4 == 3 && Test_Miller_Rabin(q))) {
            q += 2;
        }
    } while (p == q); // Assicura che p ≠ q

    res[0] = p;
    res[1] = q;
}

// Funzione per generare byte casuali con Blum Blum Shub
void bbs_generate_bytes(uint8_t *buffer, int length) {
    long long pq[2];
    gen_pq_BBS(pq);
    long long p = pq[0], q = pq[1];
    long long num = p * q;

    srand(time(NULL));
    long long y = range_start + (rand() % (range_end - range_start + 1));

    // Trova y tale che MCD(y, num) == 1
    while (mcd(y, num) != 1) {
        y++;
    }

    long long x = (y * y) % num;
    for (int i = 0; i < length; i++) {
        buffer[i] = (uint8_t)(x & 0xFF); // Prendi solo gli ultimi 8 bit
        x = (x * x) % num;
    }
}

