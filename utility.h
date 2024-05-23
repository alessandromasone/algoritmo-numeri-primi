#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Codici di errore per gestire situazioni specifiche:
// - exit 1: Errori nell'allocazione di memoria durante l'inizializzazione o la riallocazione dell'array.
// - exit 2: Indice non presente nell'array, causando accesso fuori limite o operazioni non valide.
// - exit 3: Errori relativi alla gestione dei file, come problemi durante l'apertura, la lettura o la scrittura.

/*
 * Enumerazione per indicare l'indice della dimensione dell'array
 */
#ifndef INFO_POINT
#define INFO_POINT

enum INFO_POINT {
    size_array = 0,
};

#endif // INFO_POINT

/*
 * @brief Restituisce il tempo di sistema corrente come valore clock_t.
 *
 * @return Il tempo di sistema corrente.
 */
clock_t start_timer();

/*
 * @brief Calcola il tempo trascorso in secondi dato un tempo di inizio.
 *
 * @param start_time Il tempo di inizio ottenuto da start_timer().
 * @return Il tempo trascorso in secondi.
 */
double stop_timer(clock_t start_time);

/*
 * @brief Inizializza un array dinamico di numeri interi con la dimensione specificata.
 *
 * @param initial_size La dimensione iniziale dell'array.
 * @return Puntatore all'array inizializzato.
 */
long long* init_array(long long initial_size);

/*
 * @brief Inserisce un numero intero nell'array dinamico e aggiorna la dimensione.
 *
 * @param array Puntatore all'array in cui inserire il numero.
 * @param numero Il numero da inserire nell'array.
 */
void inserisci_numero(long long **array, long long numero);

/*
 * @brief Restituisce il valore dell'elemento dell'array all'indice specificato.
 *
 * @param array Puntatore all'array.
 * @param index Indice dell'elemento da recuperare.
 * @return Il valore dell'elemento all'indice specificato.
 */
long long get_value_index(long long *array, long long index);

/*
 * @brief Aggiunge spazi di memoria aggiuntiva all'array dinamico.
 *
 * @param array Puntatore all'array a cui aggiungere spazio.
 * @param spazi_da_aggiungere Numero di spazi da aggiungere.
 */
void aggiungi_spazi(long long **array, long long spazi_da_aggiungere);

/*
 * @brief Inserisce un numero intero nell'array senza riallocare la memoria.
 *
 * @param array Puntatore all'array in cui inserire il numero.
 * @param numero Il numero da inserire nell'array.
 */
void inserisci_numero_senza_allocazione(long long *array, long long numero);

/*
 * @brief Elimina un elemento dall'array in una posizione specifica e rialloca la memoria.
 *
 * @param array Puntatore all'array da cui eliminare l'elemento.
 * @param posizione Posizione dell'elemento da eliminare.
 */
void eliminaElemento(long long **array, long long posizione);

/*
 * @brief Inserisce un numero intero nell'array in una posizione specifica senza riallocare la memoria.
 *
 * @param array Puntatore all'array in cui inserire il numero.
 * @param posizione Posizione in cui inserire il numero.
 * @param numero Il numero da inserire nell'array.
 */
void inserisci_numero_at_index(long long *array, long long posizione, long long numero);

/*
 * @brief Stampa gli elementi dell'array su righe separate in un file specificato.
 *
 * @param array L'array da stampare.
 * @param nomeFile Il nome del file in cui stampare gli elementi.
 */
void print_number_row_file(long long array[], const char *nomeFile);

/*
 * @brief Crea un clone dell'array passato come parametro.
 *
 * @param source L'array da clonare.
 * @return Il clone dell'array.
 */
long long* clone_array(long long* source);

/*
 * @brief Restituisce la dimensione di un array passato.
 *
 * @param array L'array di cui sapere la dimensione.
 * @return dimensione dell'array.
 */
long long get_size(long long* array);

/*
 * @brief Imposta la dimensione di un array, soltanto nominale.
 *
 * @param array L'array di cui modificare la dimensione.
 */
void set_size(long long* array, long long size);



#endif /* UTILITY_H */