//Le client reseau parallele
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pour sleep

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

  int sockfd; // le descripteur pour la socket
  struct sockaddr_in adresse; // la structure pour le socket
  char ch = 'A';
  //int longueur;

  // On cree la socket pour le client
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // On nomme le socket en "osmose" avec le serveur
  adresse.sin_family = AF_INET;
  adresse.sin_addr.s_addr = inet_addr("127.0.0.1");
  adresse.sin_port=htons(50000);
    
  // On connecte la socket au serveur
  if((connect(sockfd, (struct sockaddr *)&adresse, sizeof(adresse))==-1)){
      perror("pb connect : Client");
      exit(1);
  }

  // On peut maintenant ecrire et lire via sockfd
  printf("j'envoie un %c à mon serveur \n", ch);
  write(sockfd, &ch, 1);
  read(sockfd, &ch, 1);
  printf(" A moi client : %d, le serveur me donne : %c\n",getpid(), ch);

  //on ferme la socket
  close(sockfd);
  return 0;
}
