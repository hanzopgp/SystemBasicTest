/* tube_uni_père_fils.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
  int pip[2];
  pid_t pid;
  char chaine[]="Avant..";
  int taille_chaine;
  pipe(pip); //on crée un tube 

  if((pid=fork())==0) {//dans le fils
	// on fait patienter le père pendant 2s
    // montre que la lecture est blocante...
    sleep(2); 	
    char chaine_fils[]="Pour toi papa :)";
    close(pip[0]); // le fils ne lit pas
    write(pip[1], &chaine_fils, strlen(chaine_fils));
    sleep(10);
    // le fils ferme l'entrée avant de quitter
    close(pip[1]); 
    exit(0);
  }
  else { //dans le père
    char chaine_papa[]="Je vais etre effacée";
    taille_chaine = strlen(chaine_papa);
    printf("taille : %d\n", taille_chaine);
    memset(chaine_papa,'\0',taille_chaine);
	//Que des caractères NULL
	printf("Chaine avant: %s\n",chaine_papa);
    close(pip[1]); // le père n'écrit pas
    sleep(30);
    read(pip[0], chaine_papa, taille_chaine);
	// le père ferme la sortie avant de quitter
	close(pip[0]); 
	printf("Chaine après: %s\n",chaine_papa);
  }
  return 0;
}

