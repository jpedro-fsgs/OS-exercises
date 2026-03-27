#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *write_numbers(void *arg)
{
    FILE *file = fopen("file_numbers.txt", "w");

    for (int i = 1; i <= 10; i++)
    {
        fprintf(file, "%d\n", i);
    }
    fclose(file);
    return NULL;
}

void *write_letters(void *arg)
{
    FILE *file = fopen("file_letters.txt", "w");

    for (int i = 1; i <= 26; i++)
    {
        fprintf(file, "%c\n", i + 64);
    }
    fclose(file);
    return NULL;
}

int main()
{
    pthread_t numbers_thread, letters_thread;

    pthread_create(&numbers_thread, NULL, write_numbers, NULL);
    pthread_create(&letters_thread, NULL, write_letters, NULL);

    if (pthread_join(numbers_thread, NULL) == 0)
    {
        printf("Numbers file:\n");
        FILE *f1 = fopen("file_numbers.txt", "r");
        int c;
        while ((c = fgetc(f1)) != EOF)
            putchar(c);
        fclose(f1);
    }
    if (pthread_join(letters_thread, NULL) == 0)
    {
        printf("\nLetters file:\n");
        FILE *f2 = fopen("file_letters.txt", "r");
        int c;
        while ((c = fgetc(f2)) != EOF)
            putchar(c);
        fclose(f2);
    }
}

/* Saída:
$ time ./a.out 
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

real    0m0.005s
user    0m0.001s
sys     0m0.005s
*/