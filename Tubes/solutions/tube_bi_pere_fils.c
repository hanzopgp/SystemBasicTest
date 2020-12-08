/* tube_bi_père_fils.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
int main(){
  int pip1[2];
  int pip2[2];
  pid_t pid;
  char chaine[12]="Chaine vide.";
  pipe(pip1); //on cré un tube 
  pipe(pip2); //puis un second
  if((pid=fork())==0) {// le fils
    printf("le fils : %s \n",chaine);
	//ne lit pas dans pip1
    close(pip1[0]); 
	//n'écrit pas dans pip2
    close(pip2[1]); 
    write(pip1[1], "Bonjour Papa", 12);
    close(pip1[1]);
    read(pip2[0],chaine, 12);
    close(pip2[0]);
    printf("Fils reçoit : %s \n",chaine);
    exit(0);
  }
  else { // le père
    printf("le père : %s\n",chaine);
	//n'écrit pas dans pip1
    close(pip1[1]);
	//ne lit pas dans pip2 
    close(pip2[0]); 
    read(pip1[0], chaine, 12);
    close(pip1[0]);
    write(pip2[1],"Bonjour Fils",12);
    close(pip2[1]);
    printf("Père reçoit : %s\n",chaine);
    waitpid(pid, NULL, 0);
    }
  return EXIT_SUCCESS;
}

