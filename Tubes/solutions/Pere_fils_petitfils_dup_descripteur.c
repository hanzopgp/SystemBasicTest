#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// Pere | Fils1 | Fils2
// cat fichier | tee | compte les lignes 
// Usage : nom_bin fichier.txt /dev/pts/x

static void usage(char *s) {
  fprintf(stderr, "Usage : %s fichier /dev/pts/numero_console \n",s);
  exit (EXIT_FAILURE);
}

void error(char *msg){
  perror(msg);
  exit(-1);
}

int main(int argc, char *argv[]) {
  pid_t pid_fils1, pid_fils2;
  int tube1[2]; // Tube entre le pere et le fils1
  int tube2[2]; // Tube tube par le fils1 et le fils2
  if(argc != 3)
    usage(argv[0]); 
  
  if(pipe(tube1)==-1) // Creation du tube 1
    error("pb pipe");
  if(pipe(tube2)==-1) // Creation du tube 2
    error("pb pipe");
  
  // Creation du Fils1 qui herite des 2 tubes !
  if((pid_fils1=fork())==-1){
    error("pb fork");
  }
  
  //Creation du Fils2 qui herite aussi des 2 tubes !
  if(pid_fils1 != 0){    // mais creation que par le pere !!!
    if((pid_fils2=fork())==-1)
      error("pb fork");
  }  
  
  if (pid_fils1==0){ // dans le fils 1
    //sleep(10);
    close (0);       // Il ferme STDIN
    close (1);       // Il ferme STDOUT
    dup(tube1[0]);   // Redirection de STDIN sur la sortie de tube 1
    dup(tube2[1]);   // Redirection de STDOUT vers l'entree du tube 2

    close(tube1[0]); // Fermeture des descripteurs devenu inutiles
    close(tube2[1]); 

    close(tube1[1]); // Le fils 1 n'ecrit pas dans le tube 1
    close(tube2[0]); // Le fils 1 ne lit pas dans le tube 2

    execl("/usr/bin/tee", "tee", argv[2], NULL);
    
    exit(1);// fin du fils 1
  }
  
  
  if (pid_fils2==0){ // dans le fils 2
    //sleep(10);
    close (0);       // Il ferme STDIN
    dup(tube2[0]);   // Redirection de STDIN sur la sortie de tube 2

    close(tube2[0]); // Fermeture du descripteur devenu inutile
    
    close(tube1[0]); // Le fils 2 ne lit pas dans tube 1
    close(tube1[1]); // Le fils 2 n'ecrit pas dans le tube 1

    close(tube2[1]); // Le fils 2 n'ecrit pas dans le tube 2

    execlp("wc", "wc", "-clw", NULL); // "-lmc"

    exit(1); // fin du fils 2
  }
  else {
    
  //dans le Pere !
  //sleep(10);
  close(1);        // Il ferme STDOUT
  dup(tube1[1]);   // Redirection de STDOUT sur l'entree de tube 1
  
  close(tube1[1]); // Fermeture du descripteur devenu inutile

  close(tube1[0]); // Le pere ne lit pas dans le tube 1

  close(tube2[1]); // Le pere n'ecrit pas dans le tube 2
  close(tube2[0]); // Le pere ne lit pas dans le tube 2

  printf("\n");
  execl("/bin/cat", "cat", argv[1],NULL);
  return 0;
  }
}

