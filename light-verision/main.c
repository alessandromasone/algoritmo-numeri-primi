#include "vector.h"
#include "clock.h"
#include "utility.h"

int main(int argc, char *argv[]) {
    uintmax_t CYCLE;
    bool PRINT;

    parseArgs(argc, argv, &CYCLE, &PRINT);
    
    clock_t start_time;

    uintmax_t* prime_numbers = init_vector("prime_numbers", 3);
    prime_numbers[0 + remove_size_array] = 2;
    prime_numbers[1 + remove_size_array] = 3;
    prime_numbers[2 + remove_size_array] = 5;

    uintmax_t* numbers_to_subtract = init_vector("numbers_to_subtract", 2);
    numbers_to_subtract[0 + remove_size_array] = 1;
    numbers_to_subtract[1 + remove_size_array] = 1;

    uintmax_t position_prime = 0;
    uintmax_t start = prime_numbers[position_prime + remove_size_array];
    position_prime++;

    for (uintmax_t cycle = 0; cycle < CYCLE; cycle++) {
        uintmax_t k = 1;
        start = start * prime_numbers[position_prime + 1];
        uintmax_t next_start = start * prime_numbers[position_prime + remove_size_array + 1];

        start_time = start_timer();
        printf("Ciclo con start %lu\n", start);

        uintmax_t* expression_results = init_vector("expression_results", 0);
        uintmax_t position_prime_to_start_check = position_prime;
        uintmax_t position_prime_to_start_check_end = prime_numbers[size_array];

        for (uintmax_t h = position_prime + 1; h < prime_numbers[size_array]; h++) {
            uintmax_t current_prime = prime_numbers[h + 1];
            if (current_prime * current_prime > next_start) {
                position_prime_to_start_check_end = h;
                break;
            }
        }

        do {
            double progress = (double)(k * start) / next_start;
            int progress_percentage = (int)(progress * 100.0);
            printf("%d %%\r", progress_percentage);
            fflush(stdout);

            extend_vector(&prime_numbers, "prime_numbers", numbers_to_subtract[size_array]);
            extend_vector(&expression_results, "expression_results", numbers_to_subtract[size_array]);

            intmax_t prime_pos = prime_numbers[size_array] - 1 + 1;
            intmax_t position_prime_plus_two = position_prime + 2;

            for (intmax_t i = numbers_to_subtract[size_array] - 1; i >= 0; --i) {
                intmax_t index = i + remove_size_array;
                uintmax_t result = make_calc(start, k, numbers_to_subtract[index], i, PRINT);

                if (result % prime_numbers[position_prime_plus_two] == 0) {
                    continue;
                }

                bool insert = true;

                for (uintmax_t h = position_prime_to_start_check + 1; h < position_prime_to_start_check_end; ++h) {
                    if (result % prime_numbers[h + 1] == 0) {
                        insert = false;
                        break;
                    }
                }

                if (insert && prime_numbers[prime_pos] < result) {
                    prime_numbers[++prime_numbers[size_array]] = result;
                }
                expression_results[++expression_results[size_array]] = result;
            }

            k++;
        } while (start * k <= next_start);


        shift_first(expression_results, 1);
        shift_first(expression_results, 1);
        swap_and_rename("expression_results", "numbers_to_subtract", &numbers_to_subtract, &expression_results);
        position_prime++;

        printf("Tempo di esecuzione totale per la generazione %lu: %f secondi\n", start, stop_timer(start_time));
        position_prime_to_start_check = position_prime_to_start_check_end;
    }

    save_vector_on_file(prime_numbers, "output.txt");

    delete_vector_file("prime_numbers");
    delete_vector_file("numbers_to_subtract");

    return 0;
}
