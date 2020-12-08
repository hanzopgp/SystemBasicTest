// Voir la page 520 : Le serveur local

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {

  int sockfd_serveur, sockfd_client; // descripteurs pour les 2 sockets
  struct sockaddr_un adresse_serveur; // la structure pour le socket serveur
  struct sockaddr_un adresse_client; // la structure pour le socket client
  char ch;
  int long_client;

  // On supprime un éventuel socket déjà existant...
  unlink("socket_serveur");

  // On crée le socket pour le client
  sockfd_serveur = socket(AF_UNIX, SOCK_DGRAM, 0);

  // On nomme le socket
  adresse_serveur.sun_family = AF_UNIX;
  strcpy(adresse_serveur.sun_path, "socket_serveur");
  
  // On attache le socket
  if(bind(sockfd_serveur, (struct sockaddr *)&adresse_serveur, sizeof(adresse_serveur))==-1){
    perror("pb bind : Serveur");
      exit(1);
  }

  // On crée une file d'attente de connexion et on attend le client
  //listen(sockfd_serveur, 5);
  //while(1){
    printf("Le serveur attend \n");
  
    // Le serveur accepte la connexion
    long_client = sizeof(adresse_client);
    /*if((sockfd_client = accept(sockfd_serveur, (struct sockaddr *)&adresse_client, &long_client))==-1){
      perror("pb accept : Serveur");
      exit(1);
      }*/

    // On peut maintenant lire et écrire via sockfd
    recvfrom(sockfd_client, &ch, 1,0,(struct sockaddr *)&adresse_client, &long_client);
    printf("Le serveur a lu : %c\n", ch);
    ch++; 
    printf("Le serveur écrit : %c\n", ch);
    sendto(sockfd_client, &ch, 1, 0, (struct sockaddr *)&adresse_client, long_client);
    
    //on ferme le socket avec le client
    close(sockfd_client);
    //}

  return 0;
}


