#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("N: ");
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if(pid == 0){
            break;
        }
    }

    printf("PID: %d PPID: %d\n", getpid(), getppid());
}

/* Saída:
$ gcc 2.c 
$ ./a.out 
N: 6
PID: 11711 PPID: 11698
PID: 11712 PPID: 11698
PID: 11713 PPID: 11698
PID: 11714 PPID: 11698
PID: 11698 PPID: 8543
PID: 11715 PPID: 11698
PID: 11716 PPID: 11698
*/