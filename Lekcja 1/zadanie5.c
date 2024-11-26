#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREADS 100

struct dwa {
    int liczba;
    int indeks;
};

pthread_t t[THREADS];
double numbers[THREADS];
struct dwa d[THREADS];

void *p(void *arg) {
    struct dwa *data = (struct dwa *)arg;
    int n = data->liczba;
    int sum = 0;
    int next = 1;

    while (sum < n) {
        sum += next;
        next++;
    }

    numbers[data->indeks] = (double)sum;
    return NULL;
}

int main() {
    int i = 0; // pobierana liczba
    int end = 0;

    // otwarcie pliku
    FILE *f = fopen("NazwaPliku.tht", "r");
    if (f == NULL) {
        perror("Błąd otwarcia pliku");
        return 1;
    }

    // wczytywanie liczb z pliku i tworzenie watkow
    while (fscanf(f, "%d", &i) != EOF && end < THREADS) {
        d[end].liczba = i;
        d[end].indeks = end;
        pthread_create(&t[end], NULL, p, &d[end]);
        end++;
    }

    // zamkniecie pliku
    fclose(f);

    // zamkniecie watkow
    for (int j = 0; j < end; j++) {
        pthread_join(t[j], NULL);
    }

    // wypisanie wynikow
    for (int j = 0; j < end; j++) {
        printf("Suma kolejnych liczb naturalnych dla liczby %d wynosi: %.2lf\n", d[j].liczba, numbers[j]);
    }

    return 0;
}
