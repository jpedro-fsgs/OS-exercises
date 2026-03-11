#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int vector[] = {10, 3, 9, 5, 7, 8, 4, 2};
    int pid;

    for (int i = 0; i < 8; i++)
    {
        pid = fork();
        if(pid == 0)
        {
            sleep(vector[i]);
            printf("%d ", vector[i]);
            exit(0);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        wait(NULL);
    }
}
