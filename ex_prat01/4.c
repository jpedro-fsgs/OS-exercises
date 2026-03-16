#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid, pid2;
    pid = fork();
    if (pid > 0)
    {
        pid2 = fork();
    }

    if (pid == 0)
    {
        FILE *file = fopen("file_numbers.txt", "w");

        for (int i = 1; i <= 10; i++)
        {
            fprintf(file, "%d\n", i);
        }
        fclose(file);
        exit(0);
    }

    if (pid2 == 0)
    {
        FILE *file = fopen("file_letters.txt", "w");

        for (int i = 1; i <= 26; i++)
        {
            fprintf(file, "%c\n", i + 64);
        }
        fclose(file);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Numbers file:\n");
    FILE *f1 = fopen("file_numbers.txt", "r");
    int c;
    while ((c = fgetc(f1)) != EOF)
        putchar(c);
    fclose(f1);

    printf("\nLetters file:\n");
    FILE *f2 = fopen("file_letters.txt", "r");
    while ((c = fgetc(f2)) != EOF)
        putchar(c);
    fclose(f2);
}

/* Saída:
$ gcc 4.c 
$ ./a.out 
Numbers file:
1
2
3
4
5
6
7
8
9
10

Letters file:
A
B
C
D
E
F
G
H
I
J
K
L
M
N
O
P
Q
R
S
T
U
V
W
X
Y
Z
*/