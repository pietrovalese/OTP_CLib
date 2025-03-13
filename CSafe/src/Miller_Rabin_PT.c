#include "Miller_Rabin_PT.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Decomposizione di N-1 in 2^w * z
static void Miller_Rabin_generate_Z_W(long long N, long long res[2]) {
    long long z = N - 1;
    long long w = 0;
    while (z % 2 == 0) {
        z /= 2;
        w++;
    }
    res[0] = z;
    res[1] = w;
}

// Algoritmo di esponenziazione modulare veloce
static long long square_and_multiply(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }

    return result;
}

// Test di Miller-Rabin per una singola base
static bool Miller_Rabin_verify(long long N, long long y, long long z, long long w) {
    long long x = square_and_multiply(y, z, N);
    if (x == 1 || x == N - 1) {
        return true;
    }
    for (long long i = 0; i < w - 1; i++) {
        x = (x * x) % N;
        if (x == N - 1) return true;
        if (x == 1) return false;
    }
    return false;
}

// Test di primalità Miller-Rabin con basi note
bool Test_Miller_Rabin(long long N) {
    if (N < 2) return false;
    if (N == 2 || N == 3) return true;
    if (N % 2 == 0) return false;

    // Basi note per garantire determinismo fino a 2^64
    long long bases[] = {2, 3, 5, 7, 11, 13, 17};
    int num_bases = sizeof(bases) / sizeof(bases[0]);

    long long Z_W[2];
    Miller_Rabin_generate_Z_W(N, Z_W);
    long long z = Z_W[0];
    long long w = Z_W[1];

    for (int i = 0; i < num_bases; i++) {
        if (bases[i] >= N) break;  // Se la base è >= N, possiamo fermarci
        if (!Miller_Rabin_verify(N, bases[i], z, w)) {
            return false;
        }
    }
    return true;
}
