#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
char flag;

void* count(void* p){

    size_t contador_max = (size_t)p;

    size_t contador = 0;

    for(size_t i = 0; i < contador_max; i++){
        #ifdef ATOMIC
            __atomic_fetch_add(&contador, 1,__ATOMIC_SEQ_CST);
        #endif

        #ifdef MUTEX
            pthread_mutex_lock(&mutex);
            contador++;
            pthread_mutex_unlock(&mutex);
        #endif

        #ifdef WHILE
            while((__sync_lock_test_and_set(&flag, 1)));
            contador++;
            flag = 0;
        #endif
    }

    return (void*)contador;
}

int main(int argc, char *argv[])
{
    if(argc < 3){
        printf("./path/to/bin 'num of threads' 'num of counter'\n");
        return 1;
    }

    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);

    int num_threads = atoi(argv[1]);

    size_t contador_max = atoi(argv[2]);

    pthread_t threads[num_threads];
    flag = 0;

    for(int i = 0; i < num_threads; i++){

        pthread_create(&threads[i], NULL, count, (void*) contador_max);
    }

    size_t contagem = 0;

    for(int i = 0; i < num_threads; i++){

        size_t r_value;
        pthread_join(threads[i], (void*)&r_value);
        contagem += r_value;
    }

    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double tempo_corrido = seconds + nanoseconds*1e-9;

    printf("%zu %lf\n", contagem, tempo_corrido);

    return 0;
}
