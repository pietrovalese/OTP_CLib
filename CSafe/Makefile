# Impostazioni del compilatore e opzioni
CC = gcc
CFLAGS = -O2 -Wall -fPIC
LDFLAGS = -shared
LIBNAME = libotp.so

# Percorsi
SRC_PATH = src/
BUILD_PATH = build/
TESTING_PATH = testing/

# Assicura che la cartella di output esista
all: $(BUILD_PATH) lib example

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

# Creazione della libreria condivisa con BBS
lib: $(BUILD_PATH)otp.o $(BUILD_PATH)bbs.o
	$(CC) $(LDFLAGS) -o $(BUILD_PATH)$(LIBNAME) $(BUILD_PATH)otp.o $(BUILD_PATH)bbs.o

$(BUILD_PATH)otp.o: $(SRC_PATH)otp.c $(SRC_PATH)otp.h | $(BUILD_PATH)
	$(CC) $(CFLAGS) -c $(SRC_PATH)otp.c -o $(BUILD_PATH)otp.o

$(BUILD_PATH)bbs.o: $(SRC_PATH)bbs.c $(SRC_PATH)bbs.h | $(BUILD_PATH)
	$(CC) $(CFLAGS) -c $(SRC_PATH)bbs.c -o $(BUILD_PATH)bbs.o

# Compilazione dell'eseguibile di esempio
example: $(BUILD_PATH)example.o | $(BUILD_PATH)
	$(CC) -o $(BUILD_PATH)example $(BUILD_PATH)example.o -L$(BUILD_PATH) -lotp

$(BUILD_PATH)example.o: $(TESTING_PATH)example.c $(SRC_PATH)otp.h | $(BUILD_PATH)
	$(CC) $(CFLAGS) -I$(SRC_PATH) -c $(TESTING_PATH)example.c -o $(BUILD_PATH)example.o

# Pulizia dei file generati
clean:
	rm -rf $(BUILD_PATH)

# Esegui Valgrind per il debug della memoria
valgrind: example
	LD_LIBRARY_PATH=$(BUILD_PATH):$$LD_LIBRARY_PATH valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(BUILD_PATH)example
