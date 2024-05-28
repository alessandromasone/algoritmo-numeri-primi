#include "clock.h"

/**
 * @brief Avvia il timer restituendo il tempo di sistema corrente.
 * @return Il tempo di sistema corrente in tick di clock.
 */
clock_t start_timer() {
    return clock();
}

/**
 * @brief Ferma il timer e calcola la durata in secondi trascorsa dall'inizio.
 * @param start_time Il tempo di sistema al momento dell'avvio del timer.
 * @return La durata in secondi trascorsa dall'avvio del timer.
 */
double stop_timer(clock_t start_time) {
    // Calcola la differenza tra il tempo attuale e il tempo di avvio, quindi la converte in secondi
    return (double)(clock() - start_time) / CLOCKS_PER_SEC;
}
