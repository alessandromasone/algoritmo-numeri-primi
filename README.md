# Algoritmo Numeri Primi

## Descrizione

Il progetto **Algoritmo Numeri Primi** implementa un algoritmo per calcolare numeri primi utilizzando un approccio basato su cicli e sottrazioni. Il programma è scritto in C e include diverse funzionalità per l'inizializzazione e la manipolazione di array dinamici, nonché per l'esecuzione di calcoli e la gestione di numeri primi.

## Struttura del Progetto

Il progetto è composto dai seguenti file:

- `main.c`: Il file principale che contiene la funzione `main` e avvia l'esecuzione del programma.
- `primes.h` e `primes.c`: Contengono le funzioni per il calcolo dei numeri primi e la gestione degli array coinvolti.
- `utility.h` e `utility.c`: Contengono funzioni di utilità generali, come la gestione dei timer, l'inizializzazione degli array e altre operazioni comuni.
- `Makefile`: File di configurazione per la compilazione del progetto.

## Funzionamento

Il programma esegue i seguenti passaggi:

1. Inizializza un array di numeri primi con i primi due numeri primi (2 e 3).
2. Calcola una serie di espressioni basate su cicli e sottrazioni per identificare numeri non primi.
3. Elimina i numeri composti dall'array dei risultati delle espressioni.
4. Salva i numeri primi trovati in un array dedicato.
5. Ripete il processo per un numero specificato di cicli, aggiungendo nuovi numeri primi all'array.

## Utilizzo

### Compilazione

Per compilare il progetto, eseguire il comando:

```sh
make
```

### Esecuzione

#### Esecuzione senza argomenti

Per eseguire il programma senza argomenti, utilizzare il target `start`:

```sh
make start
```

#### Esecuzione con argomenti

Per eseguire il programma con un numero specificato di cicli, utilizzare il target `start` con l'argomento `-` seguito dal numero di cicli desiderato:

```sh
make start-<CYCLE>
```

Ad esempio, per eseguire il programma con 10 cicli:

```sh
make start-10
```

### Pulizia

Per pulire i file compilati, utilizzare il target `clean`:

```sh
make clean
```

## File di Output

Il programma salva i numeri primi trovati in un file di testo chiamato `output.txt`.

## Dipendenze

Il progetto utilizza la libreria standard C e non richiede dipendenze esterne.

## Contributi

Se desideri contribuire al progetto, sentiti libero di forkare il repository, apportare le modifiche necessarie e aprire una pull request. Sono benvenuti suggerimenti, correzioni di bug e miglioramenti delle funzionalità.

<br><br><br><br><br><br><br><br><br><br>

# Light Version

Questo progetto è un generatore di numeri primi implementato in C, che utilizza una serie di algoritmi per generare e salvare numeri primi in un file di output.

## Requisiti

- Compilatore GCC
- Sistema operativo Unix-like (Linux, macOS, etc.)

## Come compilare ed eseguire

1. Assicurati di avere il compilatore GCC installato sul tuo sistema.
2. Clona questo repository sul tuo computer.
3. Naviga nella directory del progetto.
4. Esegui il comando `make` per compilare il programma.
5. Una volta compilato, esegui il programma con `./main` seguito da eventuali opzioni desiderate.
   Ad esempio: `./main -c 10 -s` per generare i primi 10 cicli di numeri primi e abilitare la stampa delle espressioni.

## Opzioni da riga di comando

- `-c NUM`: Specifica il numero di cicli da eseguire per generare i numeri primi (default: 5).
- `-s`: Disabilita la stampa delle espressioni durante la generazione dei numeri primi.

## Struttura del codice

Il progetto è organizzato nei seguenti file:

- `main.c`: Il punto di ingresso del programma che gestisce la logica principale.
- `clock.h` e `clock.c`: Contengono le funzioni per avviare e fermare un timer.
- `utility.h` e `utility.c`: Contengono funzioni di utilità, come il parsing degli argomenti da riga di comando.
- `vector.h` e `vector.c`: Definiscono e implementano un'astrazione per la gestione di vettori.
