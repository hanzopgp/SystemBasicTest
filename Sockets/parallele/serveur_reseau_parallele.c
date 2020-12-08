// Le serveur reseau parallele

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h> // pour les signaux
#include <time.h>  //pour l'heure

int main() {

  //pour l'heure
  time_t timestamp;
  struct tm * t;
  int i=1; // compte les clients
  int sockfd_serveur, sockfd_client; // descripteurs pour les 2 sockets
  struct sockaddr_in adresse_serveur; // la structure pour le socket serveur
  struct sockaddr_in adresse_client; // la structure pour le socket client
  char ch;
  int longueur_serveur, longueur_client; // Taille en octets de la structure

  timestamp = time(NULL);
  t = localtime(&timestamp);

  // On cree le socket pour le client
  sockfd_serveur = socket(AF_INET, SOCK_STREAM, 0);

  // On nomme le socket
  adresse_serveur.sin_family = AF_INET;
  adresse_serveur.sin_addr.s_addr = inet_addr("127.0.0.1");
  adresse_serveur.sin_port=htons(50000);
  longueur_serveur = sizeof(adresse_serveur);

  // On attache la socket
  if(bind(sockfd_serveur, (struct sockaddr *)&adresse_serveur, longueur_serveur)==-1){
    perror("pb bind : Serveur");
      exit(1);
  }

  // On cree une file d'attente de connexion et on attend le client
  listen(sockfd_serveur, 3);

  // pour gerer les signaux du aux terminaisons des fils
  signal(SIGCHLD, SIG_IGN);
  // si on met la ligne suivante en commentaire on a des defunct !!!
  // 4556 pts/1    00:00:00 serveur_reseau_ <defunct>

  printf("Le serveur attend ");

  timestamp = time(NULL);
  t = localtime(&timestamp);
  printf("et il est %02uh %02umin %02usec.\n", t->tm_hour, t->tm_min, t->tm_sec);

  while(1){
    // Le serveur accepte la connexion
    longueur_client = sizeof(adresse_client);
    if((sockfd_client = accept(sockfd_serveur, (struct sockaddr *)&adresse_client, &longueur_client))==-1){
      perror("pb accept : Serveur");
      exit(1);
    }

    printf("A enfin un client %d ",i);
	i++;

    timestamp = time(NULL);
    t = localtime(&timestamp);
    printf("et il est %02uh %02umin %02usec.\n", t->tm_hour, t->tm_min, t->tm_sec);

    if(fork()==0) {//le fils travaille et le pere continue d'ecouter.
      // On peut maintenant lire et ecrire via sockfd_client
      // On ferme la socket d'ecoute
      printf("la socket service vaut : %d \n",sockfd_serveur);
      close(sockfd_serveur);
      read(sockfd_client, &ch, 1);
      sleep(3); //Chut je fais semblant de bosser ;-)
      ch++; 
      printf("je suis un fils, mon pid est %d et celui de papa est : %d, ma SOCKET est %d \n", \
	     getpid(), getppid(), sockfd_client);
      write(sockfd_client, &ch,1);
      exit(0);
    }
    else { //le pere
      //on ferme la socket de service
      close(sockfd_client);
      // ajoute en 2010 est-ce bien necessaire ?
      // waitpid();
    }  
  }
  return 0;
}


