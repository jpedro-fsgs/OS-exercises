/* prog1.c – serial */
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#define CALLS 10
void CPU_bound(int id)
{
    int i;
    double result = 0.0;
    /* Consumo de CPU */
    for (i = 0; i < 10000; i++)
        result = result + sin(i) * tan(i) * sqrt(result);
    printf("%d: CPU intensiva terminada\n", id);
}
void IO_bound(int id)
{
    /* Simula operações de I/O, as quais levam a bloqueio */
    sleep(1);
    printf("%d: E/S intensiva terminada\n", id);
}
int main()
{
    int i;
    for (i = 0; i < CALLS; i++)
    {
        if (i % 2)
            CPU_bound(i);
        else
            IO_bound(i);
    }
    printf("\n*** Tarefas concluídas ***\n");
    return 0;
}

/* 1) Saída:
$ time ./a.out 
0: E/S intensiva terminada
1: CPU intensiva terminada
2: E/S intensiva terminada
3: CPU intensiva terminada
4: E/S intensiva terminada
5: CPU intensiva terminada
6: E/S intensiva terminada
7: CPU intensiva terminada
8: E/S intensiva terminada
9: CPU intensiva terminada

*** Tarefas concluídas ***

real    0m5.009s
user    0m0.004s
sys     0m0.004s
*/