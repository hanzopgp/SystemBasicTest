#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


void sortietubeferme(int sig){
  printf("\n\t\tOUILLE!-Signal reçu %d\n",sig);
  if (sig==13){
	  printf("Voilà ce qui arrive quand on écrit \
	  dans un tube où la sortie est fermée\n");
  }
  //On réarme le signal par défaut
  (void) signal(SIGPIPE, SIG_DFL);
}


int main(int argc, char *argv[]) {
  pid_t pid_fils1, pid_fils2;
  int tube[2]; // les 2 descripteurs du Tube
  char chaine[]="Chaine envoyée dans le tube fermé...";
  
  //On arme le signal pour le SIGPIPE
  (void) signal(SIGPIPE, sortietubeferme);
  
  pipe(tube);// Creation du tube 1

  // Si à la ligne suivante on fait : close(tube[1]); 
  // donc fermer l'entrée du tube pas de SIGPIPE !!!
  close(tube[0]); // on ferme la sortie du tube !
  write(tube[1], &chaine, strlen(chaine)); // On écrit dans le tube
  
  sleep(5); // On attend 5s pour comprendre
  // Quand on aime on ne compte pas :)
  // et on recommence !!!
  printf("Allez j'essaie à nouveau d'écrire dans le tube fermé en sortie \n");
   write(tube[1], &chaine, strlen(chaine)); // On écrit dans le tube
  
  printf("Je ne serai pas exécuté moi :( \n");
  return 0;
}

  
  
  