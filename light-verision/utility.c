#include "utility.h"

/**
 * @brief Esegue un calcolo specifico e ne restituisce il risultato.
 * @param a Primo operando del calcolo.
 * @param b Secondo operando del calcolo.
 * @param c Terzo operando del calcolo.
 * @param type Tipo di calcolo da eseguire. Se type è diverso da zero, esegue sottrazione, altrimenti esegue addizione.
 * @param print Flag che indica se stampare o meno l'espressione.
 * @return Risultato del calcolo.
 */
uintmax_t make_calc(uintmax_t a, uintmax_t b, uintmax_t c, uintmax_t type, bool print) {
    // Verifica il tipo di calcolo da eseguire
    if (type) {
        // Se il tipo è diverso da zero, esegue la sottrazione
        if (print) printf("%lu * %lu - %lu = %lu\n", a, b, c, (a*b)-c);
        return (a*b)-c;
    } else {
        // Se il tipo è zero, esegue l'addizione
        if (print) printf("%lu * %lu + %lu = %lu\n", a, b, c, (a*b)+c);
        return (a*b)+c;
    }
}


/**
 * @param argc Numero degli argomenti da riga di comando.
 * @param argv Array di stringhe degli argomenti da riga di comando.
 * @param cycle Puntatore a un intero per memorizzare il valore del ciclo.
 * @param stampa Puntatore a un booleano per memorizzare il flag di stampa.
 * @return Non vi è alcun valore restituito.
 */
void parseArgs(int argc, char *argv[], uintmax_t *cycle, bool *stampa) {
    *cycle = DEFAULT_CYCLE; // Imposta il valore predefinito del ciclo
    *stampa = PRINT_EX; // Imposta il flag di stampa predefinito
    int i;

    // Scansiona gli argomenti da riga di comando
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            int tempCycle = atoi(argv[i + 1]);
            if (tempCycle > 0) { // Controlla se è positivo
                *cycle = tempCycle;
            } else {
                printf("Il numero per l'opzione -c deve essere positivo. Usando il valore di default.\n");
            }
            i++; // Salta l'argomento successivo poiché è il valore per "-c"
        } else if (strcmp(argv[i], "-s") == 0) {
            *stampa = true; // Disabilita il flag di stampa se viene trovato il flag "-s"
        }
    }
}
