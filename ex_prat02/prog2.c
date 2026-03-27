/* prog2.c – múltiplos processos */
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
// #define NPROCESS 10
#define NPROCESS 100
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
    int i, status;
    pid_t children[NPROCESS];
    for (i = 0; i < NPROCESS; i++)
    {
        if (i % 2)
        {
            children[i] = fork();
            if (children[i] == 0)
            {
                CPU_bound(i);
                exit(0);
            }
        }
        else
        {
            children[i] = fork();
            if (children[i] == 0)
            {
                IO_bound(i);
                exit(0);
            }
        }
    }
    for (i = 0; i < NPROCESS; i++)
        waitpid(children[i], &status, 0);
    printf("\n*** Tarefas concluídas ***\n");
    return 0;
}

/* Saída:
$ time ./a.out 
3: CPU intensiva terminada
1: CPU intensiva terminada
5: CPU intensiva terminada
7: CPU intensiva terminada
9: CPU intensiva terminada
0: E/S intensiva terminada
2: E/S intensiva terminada
4: E/S intensiva terminada
6: E/S intensiva terminada
8: E/S intensiva terminada

*** Tarefas concluídas ***

real    0m1.006s
user    0m0.008s
sys     0m0.006s
*/

/* 2) Saída:
$ time ./a.out 
1: CPU intensiva terminada
3: CPU intensiva terminada
5: CPU intensiva terminada
7: CPU intensiva terminada
9: CPU intensiva terminada
11: CPU intensiva terminada
13: CPU intensiva terminada
15: CPU intensiva terminada
17: CPU intensiva terminada
19: CPU intensiva terminada
21: CPU intensiva terminada
23: CPU intensiva terminada
27: CPU intensiva terminada
29: CPU intensiva terminada
31: CPU intensiva terminada
35: CPU intensiva terminada
25: CPU intensiva terminada
33: CPU intensiva terminada
37: CPU intensiva terminada
39: CPU intensiva terminada
41: CPU intensiva terminada
43: CPU intensiva terminada
45: CPU intensiva terminada
47: CPU intensiva terminada
49: CPU intensiva terminada
53: CPU intensiva terminada
51: CPU intensiva terminada
55: CPU intensiva terminada
57: CPU intensiva terminada
61: CPU intensiva terminada
59: CPU intensiva terminada
63: CPU intensiva terminada
65: CPU intensiva terminada
67: CPU intensiva terminada
71: CPU intensiva terminada
69: CPU intensiva terminada
73: CPU intensiva terminada
75: CPU intensiva terminada
77: CPU intensiva terminada
79: CPU intensiva terminada
81: CPU intensiva terminada
83: CPU intensiva terminada
85: CPU intensiva terminada
89: CPU intensiva terminada
87: CPU intensiva terminada
91: CPU intensiva terminada
93: CPU intensiva terminada
95: CPU intensiva terminada
99: CPU intensiva terminada
97: CPU intensiva terminada

0: E/S intensiva terminada
4: E/S intensiva terminada
2: E/S intensiva terminada
6: E/S intensiva terminada
8: E/S intensiva terminada
10: E/S intensiva terminada
14: E/S intensiva terminada
12: E/S intensiva terminada
16: E/S intensiva terminada
18: E/S intensiva terminada
22: E/S intensiva terminada
20: E/S intensiva terminada
24: E/S intensiva terminada
26: E/S intensiva terminada
28: E/S intensiva terminada
30: E/S intensiva terminada
32: E/S intensiva terminada
34: E/S intensiva terminada
36: E/S intensiva terminada
38: E/S intensiva terminada
40: E/S intensiva terminada
42: E/S intensiva terminada
44: E/S intensiva terminada
46: E/S intensiva terminada
48: E/S intensiva terminada
50: E/S intensiva terminada
52: E/S intensiva terminada
54: E/S intensiva terminada
56: E/S intensiva terminada
58: E/S intensiva terminada
60: E/S intensiva terminada
62: E/S intensiva terminada
64: E/S intensiva terminada
66: E/S intensiva terminada
68: E/S intensiva terminada
70: E/S intensiva terminada
72: E/S intensiva terminada
74: E/S intensiva terminada
76: E/S intensiva terminada
78: E/S intensiva terminada
80: E/S intensiva terminada
82: E/S intensiva terminada
84: E/S intensiva terminada
86: E/S intensiva terminada
88: E/S intensiva terminada
90: E/S intensiva terminada
92: E/S intensiva terminada
94: E/S intensiva terminada
96: E/S intensiva terminada
98: E/S intensiva terminada

*** Tarefas concluídas ***

real    0m1.016s
user    0m0.052s
sys     0m0.035s
*/