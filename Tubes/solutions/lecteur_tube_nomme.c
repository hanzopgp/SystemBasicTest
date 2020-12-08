// Processus lecteur dans le tube nommé
/* lecteur_tube_nomme.c */

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(){
  int tube;
  char chaine[30];
  // Ouverture du tube
  tube = open("fichier_du_tube", O_RDONLY);
  // Ecritude dans le tube
  read(tube, chaine, 26);
  chaine[29]=0;
  printf("Processus Lecteur du tube ");
  printf("fichier_du_tube : %s \n", chaine);
  // Fermeture du tube
  close(tube);
  // détruit le fichier 
  // unlink("fichier_du_tube");
}

