#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 100
#define THREADS 5

int p3, p5, p7 = 0;
int tab[N];

void *thread(void *range) {
    
    int max = *((int*)range);
    int min = max - 19;
    
    for (int i = min; i < max; i++) {
        // podzielne przez 3
        if (tab[i] % 3 == 0) {
            p3++;
        }
        // podzielne przez 5
        if (tab[i] % 5 == 0) {
            p5++;
        }
        // podzielne przez 7
        if (tab[i] % 7 == 0) {
            p7++;
        }
    }
    
    return NULL;   
}    

int main()
{
    
    // tablica watkow
    pthread_t t[THREADS];
    
    // generacja liczb losowych z zakresu 1-1000
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        tab[i] = rand() % (1000) + 1;
    }
    
    // tworzenie watkow
    for (int i = 0; i < THREADS; i++) {
        int range = ( (N/THREADS) * (i+1) );
        pthread_create(&t[i], NULL, thread, &range);
    }
    
    // domykanie watkow
    for (int j = 0; j < THREADS; j++) {
        pthread_join(t[j], NULL);
    }
    
    // wypisanie zliczonych liczb
    printf("Liczb podzielnych przez 3 jest: %d\n", p3);
    printf("Liczb podzielnych przez 5 jest: %d\n", p5);
    printf("Liczb podzielnych przez 7 jest: %d\n", p7);
    
    return 0;
}



