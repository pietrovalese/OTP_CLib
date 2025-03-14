# Libreria OTP con generatore BBS

Questo progetto implementa una libreria **OTP (One-Time Pad)** utilizzando il generatore **BBS (Blum Blum Shub)** per la generazione di numeri casuali crittograficamente sicuri il test di Miller Rabin per garantire la primalità fino a interi minori di 2^64.

## Struttura del progetto
**include** -> otp.h
               bbs.h
               Miller_Rabin_PT.h
               APR_CL.h
**src** ->     otp.c
               bbs.c
               Miller_Rabin_PT.c
               APR_CL.c
**testing** -> example.c
**Makefile**

## Funzionamento della libreria

La libreria fornisce un'implementazione di **One-Time Pad (OTP)** sfruttando un generatore di numeri casuali basato su **Blum Blum Shub (BBS)**.  
Di seguito una panoramica delle componenti principali:

- **BBS (Blum Blum Shub)**
  - Funzione `gen_pq_BBS(long res[2])`: Genera due numeri primi `p` e `q` per il generatore.
  - Funzione `bbs_generate(int bits)`: Restituisce un numero casuale sicuro di una lunghezza specificata.

- **OTP (One-Time Pad)**
  - Funzione `otp_encrypt(const char *msg, char *key, char *cipher)`: Cifra un messaggio usando una chiave OTP.
  - Funzione `otp_decrypt(const char *cipher, char *key, char *msg)`: Decifra un messaggio OTP.

## Compilazione e utilizzo

### Prerequisiti

- **GCC** deve essere installato nel sistema.

### Compilazione

Per compilare la libreria e l'eseguibile di test, eseguire:

```bash
make
```

Per installare e disinstallare la libreria:

```bash
make install
make uninstall
```






