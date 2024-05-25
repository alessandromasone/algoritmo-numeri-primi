
#include "primes.h"
#include "utility.h"

// Struttura per passare i dati ai thread
struct ThreadData {
    long long start;
    long long end;
    long long max_end;
    long long* index_not_primes;
    long long* expression_results;
};

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
long long make_calc(long long a, long long b, long long c, bool type, bool print) {
    if (type) {
        if (print) printf("%llu * %llu + %llu = %llu\n", a, b, c, (a*b)+c);
        return (a*b)+c;
    }
    if (print) printf("%llu * %llu - %llu = %llu\n", a, b, c, (a*b)-c);
    return (a*b)-c;
}

/**
 * @brief Calcola le espressioni con i numeri da sottrarre e restituisce un array con i risultati.
 * 
 * @param start Valore iniziale per i calcoli sarebbe 'm' a cui viene man mano moltiplicato il prossimo primo.
 * @param numbers_to_subtract Array di numeri da sottrarre.
 * @return Array con i risultati delle espressioni calcolate.
 */
long long* calcola_espressioni(long long start, long long *numbers_to_subtract) {
    printf("Ciclo con start %llu\n", start);
    long long *expression_results = init_array(0);
    long long k = 1;

    do {
        long long result = 0;

        aggiungi_spazi(&expression_results, get_size(numbers_to_subtract) + 2);

        for (long long i = get_size(numbers_to_subtract) - 1; i >= 0 ; i--) {
            result = make_calc(start, k, get_value_index(numbers_to_subtract, i), false, PRINT);
            inserisci_numero_senza_allocazione(expression_results, result);
        }
        result = make_calc(start, k, 1, false, PRINT);
        inserisci_numero_senza_allocazione(expression_results, result);
        result = make_calc(start, k, 1, true, PRINT);
        inserisci_numero_senza_allocazione(expression_results, result);
        
        k++;
    } while(start*(k) <= (start*get_value_index(expression_results, 0)));

    free(numbers_to_subtract);

    return expression_results;
}

/**
 * @brief Trova le posizioni degli elementi che appartengono alla famiglia del primo elemento e riduce la dimensione dell'array di conseguenza.
 *
 * @param expression_results Array dei risultati delle espressioni calcolate.
 * @param new_size Puntatore alla variabile che contiene la nuova dimensione dell'array.
 * @return Array con le posizioni degli elementi da eliminare.
 */
bool* posizioni_elimina_famiglia_successivo(long long *expression_results, long long *new_size) {

    bool* checker_array = (bool*)calloc(get_size(expression_results), sizeof(bool));

    for (long long i = 1; i < get_size(expression_results); i++) {
        if (get_value_index(expression_results, i) % get_value_index(expression_results, 0) == 0) {
            checker_array[i] = true;
            (*new_size)--;
        }
    }

    return checker_array;
}

/**
 * @brief Elimina gli elementi che appartengono alla famiglia del primo elemento nell'array passato.
 *
 * @param expression_results Puntatore all'array dei risultati delle espressioni calcolate.
 */
void elimina_famiglia_successivo(long long **expression_results) {
    printf("Elaborazione per il primo setaccio\n");

    eliminaElemento(expression_results, get_size(*expression_results) - 1);
    eliminaElemento(expression_results, get_size(*expression_results) - 1);

    long long new_size = get_size(*expression_results);

    bool* checker_array = posizioni_elimina_famiglia_successivo(*expression_results, &new_size);

    long long* filter_expression_results = init_array(new_size);

    set_size(filter_expression_results, new_size);

    inserisci_numero_at_index(filter_expression_results, 0, get_value_index(*expression_results, 0));

    long long j = 0;
    for (long long i = 0; i < get_size(*expression_results) - 1; i++) {
        if (checker_array[i] == 0) {
            inserisci_numero_at_index(filter_expression_results, j, get_value_index(*expression_results, i));
            j++;
        }
    }

    free(*expression_results);
    *expression_results = filter_expression_results;

}

/**
 * @brief Trova la posizione del numero massimo il cui quadrato è maggiore del prodotto di start e del primo successivo per 'm'.
 * 
 * @param expression_results Array di numeri.
 * @param start Valore di partenza per il calcolo.
 * @return Indice del numero trovato.
 */
long long trova_i(long long *expression_results, long long start) {
    printf("Ricerca numeri che possono creare le famiglie composte\n");
    long long i = 1;
    while (i < get_size(expression_results)) {
        if (get_value_index(expression_results, i) * get_value_index(expression_results, i) > (start * get_value_index(expression_results, 0))) {
            break;
        }
        i++;
    }
    return i;
}

/**
 * @brief Funzione eseguita dai thread per controllare i fattori primi.
 *
 * @param arg Puntatore ai dati del thread contenenti l'intervallo di controllo e gli array necessari.
 * @return Nessun valore di ritorno.
 */
void* check_prime_factors(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;

    for (long long h = data->start; h < data->end; h++) {
        for (long long j = 0; j < data->max_end; j++) {
            if (get_value_index(data->expression_results, h) % get_value_index(data->expression_results, j) == 0) {
                inserisci_numero_at_index(data->index_not_primes, h, true);
                break;
            }
        }
    }

    pthread_exit(NULL);
}

/**
 * @brief Identifica le posizioni dei candidati non primi nell'array passato.
 *
 * @param expression_results Array dei risultati delle espressioni calcolate.
 * @param max_position Indice fino al quale controllare per i numeri che possono creare dei composti.
 * @return Array con le posizioni dei candidati non primi.
 */
long long *posizioni_cadidati_non_primi(long long *expression_results, long long max_position) {
    printf("Eliminazioni composti\n");
    long long *index_not_primes = init_array(get_size(expression_results));
    set_size(index_not_primes, get_size(expression_results));

    // Inizializzazione thread
    pthread_t threads[NUM_THREADS];
    struct ThreadData thread_data[NUM_THREADS];

    // Calcola il numero di iterazioni per ogni thread
    long long iterations_per_thread = (get_size(expression_results)-max_position) / NUM_THREADS;
    long long current_start = max_position;

    // Creazione e esecuzione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].index_not_primes = index_not_primes;
        thread_data[i].expression_results = expression_results;

        // Imposta il range di iterazioni per il thread corrente
        thread_data[i].start = current_start;
        thread_data[i].end = (i == NUM_THREADS - 1) ? get_size(expression_results) : current_start + iterations_per_thread;
        thread_data[i].max_end = max_position;
        current_start = thread_data[i].end;

        pthread_create(&threads[i], NULL, check_prime_factors, (void*)&thread_data[i]);
    }

    // Attende la fine dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return index_not_primes;
}

/**
 * @brief Salva i numeri primi nell'array prime_numbers.
 * 
 * @param index_not_primes Array con le posizioni dei candidati non primi.
 * @param expression_results Array dei risultati
 * @param prime_numbers Puntatore all'array dei numeri primi.
 */
void salva_numeri_primi(long long *index_not_primes, long long *expression_results, long long **prime_numbers) {
    printf("Salvataggio dei numeri primi\n");

    for (long long x = 0; x < get_size(index_not_primes); x++) {
        if (get_value_index(index_not_primes, x) == 0 && get_value_index(expression_results, x) > get_value_index(*prime_numbers, get_size(*prime_numbers) - 1)) {
            inserisci_numero(prime_numbers, get_value_index(expression_results, x));
        }
    }

    free(index_not_primes);
    free(expression_results);
}

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
void calcolo_livelli(long long cycle, long long max_cycle, long long position_prime, long long **prime_numbers, long long **numbers_to_subtract, long long start) {
    if (cycle >= max_cycle) {
        return;  // Condizione di base: termina la ricorsione quando raggiungiamo il limite di ciclo
    }

    clock_t start_time = start_timer();

    // Risultati delle moltiplicazioni con sottrazione senza la scarnitura (la scarnitura sarà risultante dentro a numbers_to_subtract)
    long long *expression_results = init_array(0);

    // Calcolo delle espressioni
    expression_results = calcola_espressioni(start, (*numbers_to_subtract));

    // Cerco i composti della famiglia del primo che moltiplicherò per lo start successivo
    elimina_famiglia_successivo(&expression_results);

    // Cerco i numeri primi che possono creare dei composti nel prossimo ciclo
    long long last_to_check = trova_i(expression_results, start);

    // Clona array expression_results in to_analyze
    long long* to_analyze = clone_array(expression_results);

    // Eliminazione primo che utilizzerò nel prossimo ciclo per la moltiplicazione a 'start'
    eliminaElemento(&expression_results, 0);

    // Eliminazione famiglie dei numeri composti trovati fino a 'last_to_check' presenti dentro a quelli prodotti, utilizzo dei bool per velocità
    long long *clean_primes = posizioni_cadidati_non_primi(to_analyze, last_to_check);

    // Salvataggio all'interno dei numeri primi
    salva_numeri_primi(clean_primes, to_analyze, prime_numbers);

    printf("Ricalibrazioni variabili\n");

    *numbers_to_subtract = expression_results;
    expression_results = NULL;

    printf("Tempo di esecuzione con livello %llu: %f secondi (%lld)\n", cycle, stop_timer(start_time), get_size(*prime_numbers));

    // Chiamata ricorsiva con l'incremento del ciclo e modifica dei parametri successivi
    calcolo_livelli(cycle + 1, max_cycle, position_prime+1, prime_numbers, numbers_to_subtract, start * get_value_index((*prime_numbers), position_prime));

    free(expression_results);
}


/**
 * @brief Ottiene il valore di CYCLE dai parametri della linea di comando.
 *
 * @param argc Il numero di argomenti passati alla linea di comando.
 * @param argv L'array di stringhe contenente gli argomenti della linea di comando.
 * @return Il valore di CYCLE da utilizzare.
 */
int get_cycle_value(int argc, char *argv[]) {
    int cycle = DEFAULT_CYCLE;

    if (argc > 1) {
        cycle = atoi(argv[1]);
        if (cycle <= 0) {
            fprintf(stderr, "Il valore di CYCLE deve essere un intero positivo. Utilizzo del valore di default %d.\n", DEFAULT_CYCLE);
            cycle = DEFAULT_CYCLE;
        }
    }

    return cycle;
}