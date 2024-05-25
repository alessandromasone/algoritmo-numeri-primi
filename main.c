#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "utility.h"
#include "primes.h"


int main(int argc, char *argv[]) {

    int CYCLE = get_cycle_value(argc, argv);

    clock_t start_time;
    
    system("clear");

    // Inizializzazione di un puntatore che conterrà i numeri primi
    long long *prime_numbers = init_array(0);
    inserisci_numero(&prime_numbers, 2);
    inserisci_numero(&prime_numbers, 3);

    // Puntatore ai numeri che si dovreanno sottrarre enll'espressione
    long long *numbers_to_subtract = init_array(0);

    start_time = start_timer();

    calcolo_livelli(0, CYCLE, 2, &prime_numbers, &numbers_to_subtract, get_value_index(prime_numbers, 0) * get_value_index(prime_numbers, 1));

    printf("Tempo di esecuzione totale per la generazione: %f secondi\n", stop_timer(start_time));

    printf("Inizio salvataggio su file\n");

    start_time = start_timer();

    // Salvataggio dei numeri in un file txt
    print_number_row_file(prime_numbers, "output.txt");

    printf("Tempo di esecuzione totale per il salvataggio su file: %f secondi\n", stop_timer(start_time));

    free(prime_numbers);
    free(numbers_to_subtract);

    return 0;

}