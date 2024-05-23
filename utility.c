
#include "utility.h"

/*
 * @brief Restituisce il tempo di sistema corrente come valore clock_t.
 *
 * @return Il tempo di sistema corrente.
 */
clock_t start_timer() {
    return clock();
}

/*
 * @brief Calcola il tempo trascorso in secondi dato un tempo di inizio.
 *
 * @param start_time Il tempo di inizio ottenuto da start_timer().
 * @return Il tempo trascorso in secondi.
 */
double stop_timer(clock_t start_time) {
    return (double)(clock() - start_time) / CLOCKS_PER_SEC;
}

/*
 * @brief Inizializza un array dinamico di numeri interi con la dimensione specificata.
 *
 * @param initial_size La dimensione iniziale dell'array.
 * @return Puntatore all'array inizializzato.
 */
long long* init_array(long long initial_size) {
    long long* array = (long long*)malloc((initial_size + 1) * sizeof(long long));
    if (array == NULL) {
        printf("Errore durante l'allocazione iniziale di memoria.\n");
        exit(1);
    }
    array[size_array] = 0;
    return array;
}

/*
 * @brief Inserisce un numero intero nell'array dinamico e aggiorna la dimensione.
 *
 * @param array Puntatore all'array in cui inserire il numero.
 * @param numero Il numero da inserire nell'array.
 */
void inserisci_numero(long long **array, long long numero) {
    (*array)[size_array]++;
    *array = realloc(*array, ((*array)[size_array] + 1) * sizeof(long long));
    if (*array == NULL) {
        printf("Errore durante la riallocazione di memoria.");
        exit(1);
    }
    (*array)[(*array)[size_array]] = numero;
}

/*
 * @brief Restituisce il valore dell'elemento dell'array all'indice specificato.
 *
 * @param array Puntatore all'array.
 * @param index Indice dell'elemento da recuperare.
 * @return Il valore dell'elemento all'indice specificato.
 */
long long get_value_index(long long *array, long long index) {
    if (index < 0 || index > array[size_array]) {
        printf("Posizione non valida.\n");
        exit(2);
    }
    return array[index + 1];
}

/*
 * @brief Aggiunge spazi di memoria aggiuntiva all'array dinamico.
 *
 * @param array Puntatore all'array a cui aggiungere spazio.
 * @param spazi_da_aggiungere Numero di spazi da aggiungere.
 */
void aggiungi_spazi(long long **array, long long spazi_da_aggiungere) {
    long long dimensione_attuale = (*array)[size_array];
    *array = realloc(*array, (dimensione_attuale + spazi_da_aggiungere + 1) * sizeof(long long));
    if (*array == NULL) {
        printf("Errore durante l'aggiunta di spazio di memoria.\n");
        exit(1);
    }
}

/*
 * @brief Inserisce un numero intero nell'array senza riallocare la memoria.
 *
 * @param array Puntatore all'array in cui inserire il numero.
 * @param numero Il numero da inserire nell'array.
 */
void inserisci_numero_senza_allocazione(long long *array, long long numero) {
    array[size_array]++;
    array[array[size_array]] = numero;
}

/*
 * @brief Elimina un elemento dall'array in una posizione specifica e rialloca la memoria.
 *
 * @param array Puntatore all'array da cui eliminare l'elemento.
 * @param posizione Posizione dell'elemento da eliminare.
 */
void eliminaElemento(long long **array, long long posizione) {
    long long size = (*array)[size_array];
    if (posizione < 0 || posizione >= size) {
        printf("Posizione non valida.\n");
        exit(2);
    }
    for (long long i = posizione + 1; i < size; i++) {
        (*array)[i] = (*array)[i+1];
    }
    (*array)[size_array]--;
    *array = realloc(*array, ((*array)[size_array] + 1) * sizeof(long long));
    if (*array == NULL && (*array)[size_array] > 0) {
        printf("Errore durante la riallocazione di memoria.\n");
        exit(1);
    }
}

/*
 * @brief Inserisce un numero intero nell'array in una posizione specifica senza riallocare la memoria.
 *
 * @param array Puntatore all'array in cui inserire il numero.
 * @param posizione Posizione in cui inserire il numero.
 * @param numero Il numero da inserire nell'array.
 */
void inserisci_numero_at_index(long long *array, long long posizione, long long numero) {
    long long size = array[size_array];
    if (posizione < 0 || posizione >= size) {
        printf("Posizione non valida.\n");
        exit(2);
    }
    array[posizione + 1] = numero;
}

/*
 * @brief Stampa gli elementi dell'array su righe separate in un file specificato.
 *
 * @param array L'array da stampare.
 * @param nomeFile Il nome del file in cui stampare gli elementi.
 */
void print_number_row_file(long long array[], const char *nomeFile) {
    FILE *file = fopen(nomeFile, "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file.");
        exit(3);
    }
    for (long long i = 1; i <= array[size_array]; i++) {
        fprintf(file, "%lld\n", array[i]);
    }
    fclose(file);
}

/*
 * @brief Crea un clone dell'array passato come parametro.
 *
 * @param source L'array da clonare.
 * @return Il clone dell'array.
 */
long long* clone_array(long long* source) {
    long long* clone = init_array(source[size_array]);
    for (long long i = 0; i < source[size_array]; i++) {
        inserisci_numero_senza_allocazione(clone, source[i+1]);
    }
    return clone;
}

/*
 * @brief Restituisce la dimensione di un array passato.
 *
 * @param array L'array di cui sapere la dimensione.
 * @return dimensione dell'array.
 */
long long get_size(long long* array) {
    return array[size_array];
}

/*
 * @brief Imposta la dimensione di un array, soltanto nominale.
 *
 * @param array L'array di cui modificare la dimensione.
 */
void set_size(long long* array, long long size) {
    array[size_array] = size;
}
