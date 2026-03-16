#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    int first_process = 1;
    for (int i = 0; i < 5; i++)
    {
        if (pid == 0)
        {
            first_process = 0;
            pid = fork();
        }
    }
    wait(NULL);

    if (!first_process)
    {
        printf("PID: %d PPID: %d\n", getpid(), getppid());
    }
}

/* Saída:
$ gcc 3.c 
$ ./a.out 
PID: 91298 PPID: 91297
PID: 91297 PPID: 91296
PID: 91296 PPID: 91295
PID: 91295 PPID: 91294
PID: 91294 PPID: 91293
PID: 91293 PPID: 91292
*/