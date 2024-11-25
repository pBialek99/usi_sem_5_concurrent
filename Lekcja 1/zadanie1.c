#include <stdio.h>
#include <pthread.h>

int main()
{
    int tab1[] = {1, 5, 6, 8, 11};
    int tab2[] = {2, 4, 7, 11, 15};
    int tab3[] = {3, 9, 10, 11, 12};
    
    int liczba = -1;
    int i1, i2, i3 = 0;
    
    // szukamy wspólnej liczby
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // jeśli taka sama liczba zostanie znaleziona
            if (tab1[i] == tab2[j]) {
                liczba = tab1[i];
            }
        }
    }
    
    for (int i = 0; i < 5; i++) {
        if (tab1[i] == liczba) {
            i1 = i;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (tab2[i] == liczba) {
            i2 = i;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        if (tab3[i] == liczba) {
            i3 = i;
            break;
        }
    }
    
    if (liczba == -1) {
        printf("Tablice nie maja wspolnej liczby!\n");
    }
    else {
        printf("Wspolna liczba - %d - znajduje sie w tablicach:\nTab 1 - na indeksie: %d\nTab 2 - na indeksie: %d\nTab 3 - na indeksie: %d\n", liczba, i1, i2, i3);
    }
    
    return 0;
}