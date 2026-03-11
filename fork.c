#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
   int pid;
   
   pid = fork () ;
   printf("pid %d\n", pid) ;
   
   if ( pid < 0 )
   {
      perror ("Erro: ") ;
      exit (1) ; 
   }
   else if ( pid > 0 )
   {
      wait (0) ;
   }
   else
   {
      sleep (5) ;
   }
   printf ("Tchau !\n") ;
}

