# Impostazioni del compilatore
CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror -fPIC
LDFLAGS = -shared
LIBNAME = libotp.so

# Percorsi
SRC_PATH = src/
BUILD_PATH = build/
TESTING_PATH = testing/

# Trova automaticamente tutti i file sorgenti nella cartella src/
SRCS = $(wildcard $(SRC_PATH)*.c)
OBJS = $(patsubst $(SRC_PATH)%.c, $(BUILD_PATH)%.o, $(SRCS))

# Assicura che la cartella di output esista
all: $(BUILD_PATH) lib example

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

# Creazione della libreria condivisa
lib: $(OBJS)
	$(CC) $(LDFLAGS) -o $(BUILD_PATH)$(LIBNAME) $(OBJS)

# Regola generica per compilare tutti i file .o da src/
$(BUILD_PATH)%.o: $(SRC_PATH)%.c | $(BUILD_PATH)
	$(CC) $(CFLAGS) -I$(SRC_PATH) -c $< -o $@

# Compilazione dell'eseguibile di test
example: $(BUILD_PATH)example.o lib
	$(CC) -o $(BUILD_PATH)example $(BUILD_PATH)example.o -L$(BUILD_PATH) -lotp

$(BUILD_PATH)example.o: $(TESTING_PATH)example.c $(SRC_PATH)otp.h $(SRC_PATH)bbs.h $(SRC_PATH)Miller_Rabin_PT.h | $(BUILD_PATH)
	$(CC) $(CFLAGS) -I$(SRC_PATH) -c $(TESTING_PATH)example.c -o $(BUILD_PATH)example.o

# Pulizia dei file generati
clean:
	rm -rf $(BUILD_PATH)

# Esegui l'eseguibile con la libreria
run: example
	LD_LIBRARY_PATH=$(BUILD_PATH) ./$(BUILD_PATH)example

# Debug con Valgrind
valgrind: example
	LD_LIBRARY_PATH=$(BUILD_PATH) valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(BUILD_PATH)example

# Installazione della libreria nel sistema
install:
	cp $(BUILD_PATH)$(LIBNAME) /usr/local/lib/
	cp $(SRC_PATH)otp.h /usr/local/include/
	cp $(SRC_PATH)bbs.h /usr/local/include/
	cp $(SRC_PATH)Miller_Rabin_PT.h /usr/local/include/

# Disinstallazione della libreria
uninstall:
	rm -f /usr/local/lib/$(LIBNAME)
	rm -f /usr/local/include/otp.h
	rm -f /usr/local/include/bbs.h
	rm -f /usr/local/include/Miller_Rabin_PT.h
