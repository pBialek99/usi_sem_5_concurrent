/* Online C Compiler and Editor */
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define SIZE 100
#define THREADS 5

int count = 0;
int tab[SIZE];
pthread_t t[THREADS];

void *p(void *range) {
    
    int max = *((int *) range);
    int min = max - (SIZE / THREADS) - 1;
    int local_count = 0;
    
    for (int i = min; i < max; i++) {
        local_count += tab[i];
    }
    
    count += local_count;
    
    return NULL;
}

int main()
{
    // przydzielanie losowych liczb
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        tab[i] = rand() % 1000 + 1;
    }
    
    // tworzenie watkow
    int range[THREADS];
    for (int r = 0; r < THREADS; r++) {
        range[r] = (r + 1) * (SIZE / THREADS);
    }
    for (int j = 0; j < THREADS; j++) {
        
        pthread_create(&t[j], NULL, &p, &range[j]);
    }

    // domykanie watkow
    for (int k = 0; k < THREADS; k++) {
        pthread_join(t[k], NULL);
    }
    
    // wypis wyniku
    printf("Laczna wartosc liczb w tablicy 'tab' wynosi: %d", count);
    
    return 0;
}




