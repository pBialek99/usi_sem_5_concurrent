#include <pthread.h>
#include <iostream>

#define C 20
#define P 10

class MonitorCP {
private:
    pthread_mutex_t monitor;
    pthread_cond_t mozna_czytac;
    pthread_cond_t mozna_pisac;
    int czyta = 0;
    int pisze = 0;
    int chce_czytac = 0;
    int chce_pisac = 0;

public:
    MonitorCP() {
        pthread_mutex_init(&monitor, nullptr);
        pthread_cond_init(&mozna_czytac, nullptr);
        pthread_cond_init(&mozna_pisac, nullptr);
    }

    ~MonitorCP() {
        pthread_mutex_destroy(&monitor);
        pthread_cond_destroy(&mozna_czytac);
        pthread_cond_destroy(&mozna_pisac);
    }

    void poczatek_czytania() {
        pthread_mutex_lock(&monitor);
        if (pisze == 1 || chce_pisac > 0) {
            chce_czytac++;
            pthread_cond_wait(&mozna_czytac, &monitor);
            chce_czytac--;
        }
        czyta++;
        pthread_cond_signal(&mozna_czytac);
        pthread_mutex_unlock(&monitor);
    }

    void koniec_czytania() {
        pthread_mutex_lock(&monitor);
        czyta--;
        if (czyta == 0) {
            pthread_cond_signal(&mozna_pisac);
        }
        pthread_mutex_unlock(&monitor);
    }

    void poczatek_pisania() {
        pthread_mutex_lock(&monitor);
        if (czyta > 0 || pisze == 1) {
            chce_pisac++;
            pthread_cond_wait(&mozna_pisac, &monitor);
            chce_pisac--;
        }
        pisze = 1;
        pthread_mutex_unlock(&monitor);
    }

    void koniec_pisania() {
        pthread_mutex_lock(&monitor);
        pisze = 0;
        if (chce_czytac > 0) {
            pthread_cond_signal(&mozna_czytac);
        } else {
            pthread_cond_signal(&mozna_pisac);
        }
        pthread_mutex_unlock(&monitor);
    }
};

void* czytelnik(void* arg) {
    MonitorCP* monitor = static_cast<MonitorCP*>(arg);
    monitor->poczatek_czytania();
    std::cout << "Czytam..." << std::endl;
    monitor->koniec_czytania();
    return nullptr;
}

void* pisarz(void* arg) {
    MonitorCP* monitor = static_cast<MonitorCP*>(arg);
    monitor->poczatek_pisania();
    std::cout << "Pisze..." << std::endl;
    monitor->koniec_pisania();
    return nullptr;
}

int main() {
    MonitorCP monitor;
    pthread_t czytelnicy[C], pisarze[P];

    for (int i = 0; i < C; i++) {
        pthread_create(&czytelnicy[i], nullptr, czytelnik, &monitor);
    }

    for (int i = 0; i < P; i++) {
        pthread_create(&pisarze[i], nullptr, pisarz, &monitor);
    }

    for (int i = 0; i < C; i++) {
        pthread_join(czytelnicy[i], nullptr);
    }
    for (int i = 0; i < P; i++) {
        pthread_join(pisarze[i], nullptr);
    }

    return 0;
}
