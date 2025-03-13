#ifndef BBS_H
#define BBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/**
 * Inizializza il generatore di numeri casuali.
 * Da chiamare prima di usare altre funzioni di BBS.
 */
void bbs_init(void);

/**
 * Genera due numeri primi p e q congrui a 3 modulo 4.
 * I valori vengono memorizzati in res[0] e res[1].
 *
 * @param res Array di almeno due elementi per memorizzare p e q.
 */
void gen_pq_BBS(long long *res);

/**
 * Genera una sequenza di byte casuali usando l'algoritmo Blum Blum Shub (BBS).
 *
 * @param buffer Array in cui verranno memorizzati i byte casuali.
 * @param length Numero di byte da generare.
 */
void bbs_generate_bytes(uint8_t *buffer, int length);

#ifdef __cplusplus
}
#endif

#endif // BBS_H
