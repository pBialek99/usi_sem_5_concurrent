/*
Dana jest tablica zawierająca liczby losowe z zakresu 1..1000 Napisać program wielowątkowy obliczający najmniejszą wartość.
*/
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define SIZE 100
#define THREADS 5

int tab[SIZE];
pthread_t t[THREADS];
int min_num = 1000;
int range[THREADS];
int min_tab[THREADS];

void *p(void *range) {
    
    // zakres tablicy
    int max = *((int *) range);
    int min = max - (SIZE / THREADS);
    
    // indeks dla tablicy liczb minimalnych
    int min_index = (max / (SIZE / THREADS)) - 1;
    // jako minimalna ustalmy wartosc maks dla liczb generowanycg
    int min_local = 1000;
    
    for (int i = min; i < max; i++) {
        if (tab[i] < min_local) {
            min_local = tab[i];
        }
    }
    
    // przypisanie minimalnej liczby z pewnej czesci tablicy
    min_tab[min_index] = min_local;
    
    return NULL;
}

int main() {
    
    // generacja losowych liczb
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand() % 1000 + 1;
    }
    
    // zakresy tablic
    int range[THREADS];
    for (int r = 0; r < THREADS; r++) {
        range[r] = (r + 1) * (SIZE / THREADS);
    }
    
    // tworzenie watkow
    for (int j = 0; j < THREADS; j++) {
        pthread_create(&t[j], NULL, &p, &range[j]);
    }
    
    // zamykanie watkow
    for (int k = 0; k < THREADS; k++) {
        pthread_join(t[k], NULL);
    }
    
    // znalezienie minimalnej wartosci z tego co przetworzyly watki
    int m = 1000;
    for (int l = 0; l < THREADS; l++) {
        if (min_tab[l] < m) {
            m = min_tab[l];
        }
    }
    
    // wyswietlenie minimalnej liczby tablicy
    printf("Najmniejsza liczba w tablicy to: %d", m);
    
    return 0;
}




