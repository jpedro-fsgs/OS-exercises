#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_B, sem_C;

void print_A(){
    printf("A");

    sem_post(&sem_B);
    pthread_exit(NULL);
}

void print_B(){
    sem_wait(&sem_B);

    printf("B");
    
    sem_post(&sem_C);
    pthread_exit(NULL);
}

void print_C(){
    sem_wait(&sem_C);

    printf("C");
    pthread_exit(NULL);
}


int main(){

    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);

    pthread_t thread1, thread2, thread3;
    pthread_create(&thread1, NULL, (void *)print_A, NULL);
    pthread_create(&thread2, NULL, (void *)print_B, NULL);
    pthread_create(&thread3, NULL, (void *)print_C, NULL);

    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread1, NULL);

    sem_destroy(&sem_B);
    sem_destroy(&sem_C);

    return 0;
}

/* 3 Saída:
$ time ./a.out 
ABC
real    0m0.004s
user    0m0.000s
sys     0m0.004s
*/