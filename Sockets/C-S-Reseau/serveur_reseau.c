//Le serveur reseau

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

  int sockfd_serveur, sockfd_client; // descripteurs pour les 2 sockets
  struct sockaddr_in adresse_serveur; // la structure pour le socket serveur
  struct sockaddr_in adresse_client; // la structure pour le socket client
  char ch;
  int longueur_serveur, longueur_client; // Taille en octets de la structure

  // On cree le socket pour le client
  sockfd_serveur = socket(AF_INET, SOCK_STREAM, 0);

  // On nomme le socket
  adresse_serveur.sin_family = AF_INET;
  adresse_serveur.sin_addr.s_addr = inet_addr("127.0.0.1");
  adresse_serveur.sin_port=htons(50000);
  longueur_serveur = sizeof(adresse_serveur);
  
  
  // On attache le socket
  if(bind(sockfd_serveur, (struct sockaddr *)&adresse_serveur, longueur_serveur)==-1){
    perror("pb bind : Serveur");
      exit(1);
  }

  // On cree une file d'attente de connexion et on attend le client
  listen(sockfd_serveur, 5);
  while(1){
    printf("Le serveur attend \n");
    //system("ps");
  
    // Le serveur accepte la connexion
    longueur_client = sizeof(adresse_client);
    if((sockfd_client = accept(sockfd_serveur, (struct sockaddr *)&adresse_client, &longueur_client))==-1){
      perror("pb accept : Serveur");
      exit(1);
    }

    // On peut maintenant lire et ecrire via sockfd
    read(sockfd_client, &ch, 1);
    ch++; 
    //sleep(10);
    write(sockfd_client, &ch,1);
    
    //on ferme le socket avec le client
    close(sockfd_client);
  }
  return 0;
}

