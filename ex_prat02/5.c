#include <stdio.h>
#include <stdlib.h> // Necessário para malloc e free
#include <pthread.h>

#define N 5

// Adicionamos o id para a thread saber sua posição na cadeia
typedef struct
{
    int id;
    pthread_t parent_thread;
} DadosThread;

void *create_thread(void *args)
{
    // 1. Extrai os dados recebidos
    DadosThread *meus_dados = (DadosThread *)args;
    int meu_id = meus_dados->id;
    pthread_t pai = meus_dados->parent_thread;

    // 2. Critério de Parada: Só cria a próxima se não chegou no limite N
    if (meu_id < N)
    {
        pthread_t proxima_thread; // Variável simples, sem o '*'

        // Prepara os dados para a PRÓXIMA thread
        DadosThread *dados_proxima = (DadosThread *)malloc(sizeof(DadosThread));
        dados_proxima->id = meu_id + 1;
        dados_proxima->parent_thread = pthread_self();

        // Cria a próxima thread e passa o pacote NOVO (dados_proxima)
        pthread_create(&proxima_thread, NULL, create_thread, (void *)dados_proxima);

        // Substituído pthread_wait por pthread_join
        pthread_join(proxima_thread, NULL);
    }

    // 3. Imprime os dados após o join (garante a ordem reversa)
    // Usamos %lu e fazemos cast para (unsigned long) para evitar alertas do compilador
    printf("Thread %d (ID Real: %lu) | Criada pela Thread ID: %lu\n",
           meu_id, (unsigned long)pthread_self(), (unsigned long)pai);

    // Limpa a memória que foi alocada para esta thread
    free(meus_dados);

    pthread_exit(NULL);
}

int main()
{
    pthread_t primeira_thread;

    printf("Iniciando. O ID da Main eh: %lu\n\n", (unsigned long)pthread_self());

    // A Main prepara o pacote de dados para a 1ª thread da cadeia
    DadosThread *dados_primeira = (DadosThread *)malloc(sizeof(DadosThread));
    dados_primeira->id = 1;
    dados_primeira->parent_thread = pthread_self();

    // A Main dá o pontapé inicial criando a 1ª thread
    pthread_create(&primeira_thread, NULL, create_thread, (void *)dados_primeira);

    // A Main aguarda a 1ª thread terminar (o que significa aguardar toda a cadeia)
    pthread_join(primeira_thread, NULL);

    return 0;
}

/* Saída:
$ time ./a.out 
Iniciando. O ID da Main eh: 140493911185216

Thread 5 (ID Real: 140493673457344) | Criada pela Thread ID: 140493681850048
Thread 4 (ID Real: 140493681850048) | Criada pela Thread ID: 140493894395584
Thread 3 (ID Real: 140493894395584) | Criada pela Thread ID: 140493902788288
Thread 2 (ID Real: 140493902788288) | Criada pela Thread ID: 140493911180992
Thread 1 (ID Real: 140493911180992) | Criada pela Thread ID: 140493911185216

real    0m0.006s
user    0m0.003s
sys     0m0.004s
*/