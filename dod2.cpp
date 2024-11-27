#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>

class MonitorPK {
private:
    std::queue<int> bufor;           
    const size_t maxRozmiar = 10;    
    pthread_mutex_t mutex;           
    pthread_cond_t niepusty;         
    pthread_cond_t niepelny;         

public:
    MonitorPK() {
        pthread_mutex_init(&mutex, nullptr);
        pthread_cond_init(&niepusty, nullptr);
        pthread_cond_init(&niepelny, nullptr);
    }

    ~MonitorPK() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&niepusty);
        pthread_cond_destroy(&niepelny);
    }

    void wstaw(int dane) {
        pthread_mutex_lock(&mutex);

        while (bufor.size() == maxRozmiar) {
            pthread_cond_wait(&niepelny, &mutex);
        }

        bufor.push(dane);
        std::cout << "Producent: Wstawiono " << dane << std::endl;

        pthread_cond_signal(&niepusty);
        pthread_mutex_unlock(&mutex);
    }

    int pobierz() {
        pthread_mutex_lock(&mutex);

        while (bufor.empty()) {
            pthread_cond_wait(&niepusty, &mutex);
        }

        int dane = bufor.front();
        bufor.pop();
        std::cout << "Konsument: Pobieram " << dane << std::endl;

        pthread_cond_signal(&niepelny);
        pthread_mutex_unlock(&mutex);

        return dane;
    }
};

MonitorPK Bufor;

void* producent(void* arg) {
    int dane = 1;
    while (true) {
        Bufor.wstaw(dane);
        dane++;
        sleep(1);
    }
    return nullptr;
}

void* konsument(void* arg) {
    while (true) {
        int dane = Bufor.pobierz();
        
        std::cout << "Konsument: Przetwarzam " << dane << std::endl;
        sleep(2);
    }
    return nullptr;
}

int main() {
    pthread_t thProducent, thKonsument;

    pthread_create(&thProducent, nullptr, producent, nullptr);
    pthread_create(&thKonsument, nullptr, konsument, nullptr);

    pthread_join(thProducent, nullptr);
    pthread_join(thKonsument, nullptr);

    return 0;
}
