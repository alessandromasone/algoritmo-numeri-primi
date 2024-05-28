#ifndef utility_h
#define utility_h

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_CYCLE 5
#define PRINT_EX false

/**
 * @brief Esegue un calcolo specifico e ne restituisce il risultato.
 * @param a Primo operando del calcolo.
 * @param b Secondo operando del calcolo.
 * @param c Terzo operando del calcolo.
 * @param type Tipo di calcolo da eseguire. Se type è diverso da zero, esegue sottrazione, altrimenti esegue addizione.
 * @param print Flag che indica se stampare o meno l'espressione.
 * @return Risultato del calcolo.
 */
uintmax_t make_calc(uintmax_t a, uintmax_t b, uintmax_t c, uintmax_t type, bool print);

/**
 * @param argc Numero degli argomenti da riga di comando.
 * @param argv Array di stringhe degli argomenti da riga di comando.
 * @param cycle Puntatore a un uintmax_t per memorizzare il valore del ciclo.
 * @param stampa Puntatore a un booleano per memorizzare il flag di stampa.
 * @return Non vi è alcun valore restituito.
 */
void parseArgs(int argc, char *argv[], uintmax_t *cycle, bool *stampa);

#endif