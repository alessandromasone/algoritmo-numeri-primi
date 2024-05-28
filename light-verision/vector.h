#ifndef vector_h
#define vector_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


enum INFO_POINT {
    size_array = 0,
    remove_size_array = 1,
};

/**
 * @brief Sposta tutti gli elementi del vettore a destra di una posizione e inserisce 'numero' all'inizio.
 * @param vettore Puntatore al vettore.
 * @param numero Valore da inserire all'inizio del vettore.
 */
void shift_first(uintmax_t *vettore, uintmax_t numero);

/**
 * @brief Annulla il memory mapping del vettore e elimina il file.
 * @param filename Nome del file associato al vettore.
 * @param vector Puntatore al vettore.
 */
void destroy_vector(const char *filename, uintmax_t *vector);

/**
 * @brief Scambia i puntatori di due vettori e rinomina il file associato.
 * @param old_filename Nome attuale del file.
 * @param new_filename Nuovo nome del file.
 * @param var1 Puntatore al primo puntatore del vettore.
 * @param var2 Puntatore al secondo puntatore del vettore.
 */
void swap_and_rename(const char *old_filename, const char *new_filename, uintmax_t **var1, uintmax_t **var2);

/**
 * @brief Inizializza un vettore con un numero specificato di elementi, creando e memory-mapping un file.
 * @param filename Nome del file da creare e memory-mappare.
 * @param num_elements Numero di elementi nel vettore.
 * @return Puntatore al vettore inizializzato.
 */
uintmax_t* init_vector(const char *filename, uintmax_t num_elements);

/**
 * @brief Estende la dimensione di un vettore memory-mapped aggiungendo spazio aggiuntivo.
 * @param vector Puntatore al puntatore del vettore.
 * @param filename Nome del file associato al vettore.
 * @param spazi_da_aggiungere Numero di elementi da aggiungere al vettore.
 */
void extend_vector(uintmax_t **vector, const char *filename, off_t spazi_da_aggiungere);

/**
 * @brief Elimina un file dal sistema operativo.
 * @param filename Il percorso del file da eliminare.
 * @return Non vi è alcun valore restituito.
 */
void delete_vector_file(const char* filename);

/**
 * @brief Salva un vettore su un file.
 * @param array Puntatore al vettore contenente i dati da salvare.
 * @param nomeFile Nome del file su cui salvare i dati.
 * @return Non vi è alcun valore restituito.
 */
void save_vector_on_file(uintmax_t *array, const char *nomeFile);

#endif