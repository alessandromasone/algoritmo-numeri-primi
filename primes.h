#ifndef PRIMES_H
#define PRIMES_H

#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define PRINT false

#define DEFAULT_CYCLE 5

#define NUM_THREADS 2

/**
 * @brief Effettua un calcolo basato sul tipo specificato.
 * 
 * @param a Primo numero intero lungo.
 * @param b Secondo numero intero lungo.
 * @param c Terzo numero intero lungo.
 * @param type Tipo di calcolo ("add=true" o "sub=false").
 * @param print Se vero, stampa il risultato del calcolo.
 * @return Il risultato del calcolo.
 */
long long make_calc(long long a, long long b, long long c, bool type, bool print);

/**
 * @brief Calcola le espressioni con i numeri da sottrarre e restituisce un array con i risultati.
 * 
 * @param start Valore iniziale per i calcoli sarebbe 'm' a cui viene man mano moltiplicato il prossimo primo.
 * @param numbers_to_subtract Array di numeri da sottrarre.
 * @return Array con i risultati delle espressioni calcolate.
 */
long long* calcola_espressioni(long long start, long long *numbers_to_subtract);

/**
 * @brief Trova le posizioni degli elementi che appartengono alla famiglia del primo elemento e riduce la dimensione dell'array di conseguenza.
 *
 * @param expression_results Array dei risultati delle espressioni calcolate.
 * @param new_size Puntatore alla variabile che contiene la nuova dimensione dell'array.
 * @return Array con le posizioni degli elementi da eliminare.
 */
bool* posizioni_elimina_famiglia_successivo(long long *expression_results, long long *new_size);

/**
 * @brief Elimina gli elementi che appartengono alla famiglia del primo elemento nell'array passato.
 *
 * @param expression_results Puntatore all'array dei risultati delle espressioni calcolate.
 */
void elimina_famiglia_successivo(long long **expression_results);

/**
 * @brief Trova la posizione del numero massimo il cui quadrato è maggiore del prodotto di start e del primo successivo per 'm'.
 * 
 * @param expression_results Array di numeri.
 * @param start Valore di partenza per il calcolo.
 * @return Indice del numero trovato.
 */
long long trova_i(long long *expression_results, long long start);

/**
 * @brief Funzione eseguita dai thread per controllare i fattori primi.
 *
 * @param arg Puntatore ai dati del thread contenenti l'intervallo di controllo e gli array necessari.
 * @return Nessun valore di ritorno.
 */
void* check_prime_factors(void* arg);

/**
 * @brief Identifica le posizioni dei candidati non primi nell'array passato.
 *
 * @param expression_results Array dei risultati delle espressioni calcolate.
 * @param max_position Indice fino al quale controllare per i numeri che possono creare dei composti.
 * @return Array con le posizioni dei candidati non primi.
 */
long long *posizioni_cadidati_non_primi(long long *expression_results, long long max_position);

/**
 * @brief Salva i numeri primi nell'array prime_numbers.
 * 
 * @param index_not_primes Array con le posizioni dei candidati non primi.
 * @param expression_results Array dei risultati
 * @param prime_numbers Puntatore all'array dei numeri primi.
 */
void salva_numeri_primi(long long *index_not_primes, long long *expression_results, long long **prime_numbers);

/**
 * @brief Esegue un ciclo ricorsivo per trovare numeri primi.
 * 
 * @param cycle Ciclo corrente.
 * @param max_cycle Numero totale di cicli.
 * @param position_prime Posizione corrente nell'array dei numeri primi.
 * @param prime_numbers Puntatore all'array dei numeri primi.
 * @param numbers_to_subtract Puntatore all'array dei numeri da sottrarre.
 * @param start Valore iniziale per i calcoli.
 */
void calcolo_livelli(long long cycle, long long max_cycle, long long position_prime, long long **prime_numbers, long long **numbers_to_subtract, long long start);


/**
 * @brief Ottiene il valore di CYCLE dai parametri della linea di comando.
 *
 * @param argc Il numero di argomenti passati alla linea di comando.
 * @param argv L'array di stringhe contenente gli argomenti della linea di comando.
 * @return Il valore di CYCLE da utilizzare.
 */
int get_cycle_value(int argc, char *argv[]);

#endif /* PRIMES_H */