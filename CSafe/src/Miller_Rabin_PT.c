#include "Miller_Rabin_PT.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

static long long MCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Correzione: Passiamo un array come argomento per evitare di restituire un array locale
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

// Correzione: x deve essere aggiornato correttamente nel ciclo
static bool Miller_Rabin_verify(long long N, long long y, long long z, long long w) {
    long long x = square_and_multiply(y, z, N);
    if (x == 1 || x == N - 1) {
        return true;
    }
    for (int i = 0; i < w - 1; i++) {
        x = (x * x) % N;  // ✅ Aggiorniamo x correttamente
        if (x == N - 1) return true;
        if (x == 1) return false;
    }
    return false;
}

bool Test_Miller_Rabin(long long N, int k) {
    if (N < 2) return false;
    if (N == 3) return true;
    if (N % 2 == 0) return false;

    long long Z_W[2];
    Miller_Rabin_generate_Z_W(N, Z_W);
    long long z = Z_W[0];
    long long w = Z_W[1];

    srand(time(NULL));  // ✅ Spostato fuori dal ciclo

    for (int i = 0; i < k; i++) {
        long long y = 2 + (rand() % (N - 3));
        if (MCD(N, y) != 1 || !Miller_Rabin_verify(N, y, z, w)) {
            return false;
        }
    }
    return true;  // ✅ Deve essere fuori dal ciclo
}
