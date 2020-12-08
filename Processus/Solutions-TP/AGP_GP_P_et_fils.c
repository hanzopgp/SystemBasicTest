#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  int pid_GP, pid_P, pid_F; // pour le GP, le P et le fils...
  system("clear"); // on efface l'écran
  
  pid_GP=fork(); //l'AGP cré le GP
  if (pid_GP != 0){ /* dans l'AGP */
    printf("\narrière grand père : je suis le processus %d \n", getpid());
    printf("arrière grand père : j'attends la fin de %d \n", pid_GP);
    waitpid(pid_GP, NULL, 0); // l'AGP attend le GP 
    sleep(5);
    printf("arrière grand père : je termine enfin \n");
  }
  else{ pid_P=fork(); // dans le GP qui cré le P
    if (pid_P!=0){ //le GP cré le P
      printf("\ngrand père : je suis le processus %d \n", getpid());
      printf("grand père : j'attends la fin de %d \n", pid_P);
      waitpid(pid_P, NULL, 0); // Le GP attend le P
      sleep(5); 
      printf("grand père : je termine enfin \n");
    }
    else{ pid_F=fork(); // dans le P qui cré le fils
      if (pid_F!=0){ 
	printf("\npère : je suis le processus %d \n", getpid());
	printf("père : j'attends la fin de %d \n", pid_F);
	waitpid(pid_F, NULL, 0); // Le P attend le F
	sleep(5);
	printf("père : je termine enfin \n");
      }
      else{ // dans le F
	printf("\nfils : je suis le processus %d \n", getpid());
	printf("fils : moi je dors 5 secondes pendant que les autres attendent...\n");
	sleep(5);
	printf("fils  j'ai fini de dormir enfin \n");
      }
    }
  }
  return 0;
}
