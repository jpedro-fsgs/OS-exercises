#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    char *input = malloc(100 * sizeof(char));
    char *args[10];

    while (1)
    {
        printf("$ ");
        if (fgets(input, 100, stdin) == NULL)
            break;

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0)
            break;
        if (strlen(input) == 0)
            continue;

        pid_t pid = fork();

        if (pid == 0)
        {
            int i = 0;
            args[i] = strtok(input, " ");
            while (args[i] != NULL)
            {
                args[++i] = strtok(NULL, " ");
            }
            execvp(args[0], args);
        }
        else
            wait(NULL);
    }
}

/* Saída:
$ gcc 5.c 
$ ./a.out 
$ ls
1.c  2.c  3.c  4.c  5.c  a.out  file_letters.txt  file_numbers.txt
$ pwd
/home/myoui/T/C/so-exercises/ex_prat01
$ echo "Teste"
"Teste"
$ exit
*/