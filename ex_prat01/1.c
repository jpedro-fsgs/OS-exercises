#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* Ocorrências Previstas:
A: 2
B: 2
C: 2
D: 1
E: 2
*/
int main()
{
    pid_t pid;
    pid = fork();
    printf("A\n");
    if (pid == 0)
    {
        printf("B\n");
    }
    printf("C\n");
    if (pid > 0)
    {
        printf("D\n");
    }
    printf("E\n");
    return 0;
}

/* Compilação e Execução:
$ gcc 1.c 
$ ./a.out 
A
C
D
E
A
B
C
E

Ocorrências Observadas:
A: 2
B: 1
C: 2
D: 1
E: 2
*/