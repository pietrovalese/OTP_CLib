# Libreria OTP con Generatore BBS

Questo progetto implementa una libreria **OTP (One-Time Pad)** utilizzando il generatore **BBS (Blum Blum Shub)** per la generazione di numeri casuali crittograficamente sicuri e il **Test di Miller-Rabin** per garantire la primalità fino a interi minori di \(2^{64}\).

---

## 📂 Struttura del Progetto

```
include/  -> otp.h
            bbs.h
            Miller_Rabin_PT.h
            APR_CL.h

src/      -> otp.c
            bbs.c
            Miller_Rabin_PT.c
            APR_CL.c

testing/  -> example.c

Makefile
```

---

## 🔧 Funzionamento della Libreria

La libreria fornisce un'implementazione di **One-Time Pad (OTP)** sfruttando un generatore di numeri casuali basato su **Blum Blum Shub (BBS)**.\
Ecco una panoramica delle componenti principali:

### ✨ BBS (Blum Blum Shub)

- `gen_pq_BBS(long *res)`: Genera due numeri primi `p` e `q` per il generatore.
- `bbs_generate_bytes(uint8_t *buffer, int length)`: Restituisce un numero casuale sicuro di una lunghezza specificata.

### 🔑 OTP (One-Time Pad)

- `otp_encrypt(uint8_t *message, uint8_t *key, int length)`: Cifra un messaggio usando il cifrario OTP.
- `otp_decrypt(uint8_t *encrypted_message, uint8_t *key, int length)`: Decifra un messaggio cifrato con OTP.
- `file_to_otp(const char *input_file, const char *output_file)`: Cifra o decifra un file cifrato con OTP.
- `otp_generate_random_key(int length)`: Genera una chiave randomica di lunghezza specificata.

### 🔢 Test di Miller-Rabin

- `Test_Miller_Rabin(long long N)`: Controlla la primalità del valore fornito in \(O(7log^2(n))\).

---

## 🚀 Compilazione e Utilizzo

### 📌 Prerequisiti

- **GCC** deve essere installato nel sistema.

### 📄 Compilazione

Per compilare la libreria e l'eseguibile di test, eseguire:

```bash
make
```

Per installare e disinstallare la libreria:

```bash
make install
make uninstall
```

Per testare il codice utilizzare:

```bash
make run 
```

---

## 📜 Licenza

Questo progetto è distribuito sotto la licenza MIT.

---

## 📝 Autore

Sviluppato da Valese Pietro

