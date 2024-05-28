# Nome del compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra -Werror -std=c11

# Nome dell'eseguibile finale
TARGET = main

# Trova tutti i file .c e .h nella directory corrente
SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

# Crea un elenco degli oggetti corrispondenti ai file .c
OBJS = $(SRCS:.c=.o)

# Regola di default per costruire il target
all: $(TARGET)

# Regola per costruire l'eseguibile
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regola per compilare i file .c in oggetti .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regola per pulire i file di compilazione
clean:
	rm -f $(OBJS) $(TARGET)

# Regola per ricostruire tutto
rebuild: clean all

# Target per avviare l'applicazione con argomenti
start: $(TARGET)
	./$(TARGET) $(ARGS)

# Dichiarazione dei file non di destinazione
.PHONY: all clean rebuild start
