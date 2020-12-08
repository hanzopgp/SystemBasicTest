// Processus ecrivain dans le tube nommé
/* ecrivain_tube_nomme.c */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(){
  mode_t mode;
  int tube;
  char chaine[]="Bonjour passe dans le tube";
  mode = S_IRUSR | S_IWUSR;
  // Création du tube nommé
  mkfifo("fichier_du_tube", mode);
  // Ouverture du tube
  tube = open("fichier_du_tube", O_WRONLY);
  // Ecritude dans le tube
  write(tube, chaine, strlen(chaine));
  // Fermeture du tube
  close(tube);
}

