#ifndef BBS_H
#define BBS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Genera due numeri primi p e q congrui a 3 modulo 4 e li memorizza in res[0] e res[1]
void gen_pq_BBS(long long *res);

// Genera una sequenza di byte casuali usando l'algoritmo Blum Blum Shub (BBS)
void bbs_generate_bytes(uint8_t *buffer, int length);

#endif // BBS_H
