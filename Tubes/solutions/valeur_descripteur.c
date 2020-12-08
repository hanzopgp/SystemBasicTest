#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
//#include 

int main(int argc, char *argv[]) {
  pid_t pid_fils1, pid_fils2;
  int tube1[2]; // Tube entre le pere et le fils1
  int tube2[2]; // Tube tube par le fils1 et le fils2

  if(pipe(tube1)==-1) // Creation du tube tube1
    error("pb pipe");
  if(pipe(tube2)==-1) // Creation du tube tube2
    error("pb pipe");


  //Creation du Fils1
  if((pid_fils1=fork())==-1)
    error("pb fork");
  
  //Creation du Fils2
  if((pid_fils2=fork())==-1)
    error("pb fork");

  if (pid_fils2==0){ // dans le fils2
    printf("fils 2 : valeur stdin : %d \n",STDIN_FILENO);
    printf("fils 2 : valeur stdout : %d \n",STDOUT_FILENO);
    printf("fils 2 : valeur tube1[0] : %d \n",tube1[0]);
    exit(1);
  }
  
  if (pid_fils1==0){ // dans le fils1
    printf("fils 1 : valeur stdin : %d \n",STDIN_FILENO);
    printf("fils 1 : valeur stdout : %d \n",STDOUT_FILENO);
    printf("fils 1 : valeur tube1[0] : %d \n",tube1[0]);
    
    exit(1);
  }
  
  
  return 0;
}

