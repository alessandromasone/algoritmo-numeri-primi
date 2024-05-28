#include "vector.h"

/**
 * @brief Sposta tutti gli elementi del vettore a destra di una posizione e inserisce 'numero' all'inizio.
 * @param vettore Puntatore al vettore.
 * @param numero Valore da inserire all'inizio del vettore.
 * @return Non vi è alcun valore restituito.
 */
void shift_first(uintmax_t *vettore, uintmax_t numero) {
    // Itera sul vettore dall'ultimo elemento al primo
    for (uintmax_t i = vettore[size_array] - 1; i > 0; i--) {
        // Sposta ogni elemento a destra di una posizione
        vettore[i+remove_size_array] = vettore[i+remove_size_array - 1];
    }
    // Inserisce il nuovo numero all'inizio del vettore
    vettore[remove_size_array] = numero;
}


/**
 * @brief Annulla il memory mapping del vettore e elimina il file.
 * @param filename Nome del file associato al vettore.
 * @param vector Puntatore al vettore.
 * @return Non vi è alcun valore restituito.
 */
void destroy_vector(const char *filename, uintmax_t *vector) {
    // Calcola la dimensione della regione memory-mapped
    off_t size = vector[size_array] + 1 * sizeof(uintmax_t);

    // Annulla il memory mapping
    if (munmap(vector, size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    // Elimina il file
    if (unlink(filename) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Scambia i puntatori di due vettori e rinomina il file associato.
 * @param old_filename Nome attuale del file.
 * @param new_filename Nuovo nome del file.
 * @param var1 Puntatore al primo puntatore del vettore.
 * @param var2 Puntatore al secondo puntatore del vettore.
 * @return Non vi è alcun valore restituito.
 */
void swap_and_rename(const char *old_filename, const char *new_filename, uintmax_t **var1, uintmax_t **var2) {
    // Scambia i puntatori dei due vettori
    uintmax_t *temp = *var1;
    *var1 = *var2;
    *var2 = temp;

    // Rinomina il file
    if (rename(old_filename, new_filename) == -1) {
        perror("rename");
        exit(EXIT_FAILURE);
    }
}


/**
 * @brief Inizializza un vettore con un numero specificato di elementi, creando e memory-mapping un file.
 * @param filename Nome del file da creare e memory-mappare.
 * @param num_elements Numero di elementi nel vettore.
 * @return Puntatore al vettore inizializzato.
 */
uintmax_t* init_vector(const char *filename, uintmax_t num_elements) {
    uintmax_t *vector;
    // Calcola la dimensione della regione memory-mapped
    off_t size = (num_elements + 1) * sizeof(uintmax_t);

    // Apre il file
    int fd = open(filename, O_CREAT | O_RDWR, (mode_t)0600);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Imposta la dimensione del file
    if (ftruncate(fd, size) == -1) {
        close(fd);
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Memory-mappa il file
    vector = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (vector == MAP_FAILED) {
        close(fd);
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Inizializza la dimensione del vettore
    vector[size_array] = num_elements;
    close(fd);
    return vector;
}

/**
 * @brief Estende la dimensione di un vettore memory-mapped aggiungendo spazio aggiuntivo.
 * @param vector Puntatore al puntatore del vettore.
 * @param filename Nome del file associato al vettore.
 * @param spazi_da_aggiungere Numero di elementi da aggiungere al vettore.
 * @return Non vi è alcun valore restituito.
 */
void extend_vector(uintmax_t **vector, const char *filename, off_t spazi_da_aggiungere) {
    // Apre il file
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Ottiene la dimensione attuale del file
    off_t current_size = lseek(fd, 0, SEEK_END);
    if (current_size == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Calcola la nuova dimensione del file
    off_t new_size = current_size + spazi_da_aggiungere * sizeof(uintmax_t);

    // Estende la dimensione del file
    if (ftruncate(fd, new_size) == -1) {
        perror("ftruncate");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Salva il vecchio puntatore del vettore
    uintmax_t *old_vector = *vector;

    // Memory-mappa il file esteso
    *vector = mmap(0, new_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (*vector == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Copia i vecchi dati nella nuova regione memory-mapped
    memcpy(*vector, old_vector, current_size);

    // Annulla il memory mapping della vecchia regione memory-mapped
    munmap(old_vector, current_size);

    close(fd);
}

/**
 * @brief Elimina un file dal sistema operativo.
 * @param filename Il percorso del file da eliminare.
 * @return Non vi è alcun valore restituito.
 */
void delete_vector_file(const char* filename) {
    // Prova ad eliminare il file
    if (remove(filename) != 0) {
        // Se si verifica un errore, stampa un messaggio di errore con perror()
        perror("Error deleting file");
    }
}

/**
 * @brief Salva un vettore su un file.
 * @param array Puntatore al vettore contenente i dati da salvare.
 * @param nomeFile Nome del file su cui salvare i dati.
 * @return Non vi è alcun valore restituito.
 */
void save_vector_on_file(uintmax_t *array, const char *nomeFile) {
    // Apre il file in modalità scrittura
    FILE *file = fopen(nomeFile, "w");
    // Verifica se l'apertura del file è avvenuta correttamente
    if (file == NULL) {
        perror("Errore durante l'apertura del file");
        return;
    }
    // Itera attraverso il vettore e scrive ciascun elemento nel file
    for (uintmax_t i = 0; i < array[size_array]; i++) {
        fprintf(file, "%lu\n", array[i+remove_size_array]);
    }
    // Chiude il file
    fclose(file);
}
