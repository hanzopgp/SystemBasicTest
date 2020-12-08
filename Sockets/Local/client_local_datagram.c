// Voir la page 519 : Le client local

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {

  int sockfd; // le descripteur pour le socket
  struct sockaddr_un adresse; // la structure pour le socket
  char ch = 'A';
  int long_adresse;
  // On crée la socket pour le client
  sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);

  // On nomme le socket en "osmose" avec le serveur
  adresse.sun_family = AF_UNIX;
  strcpy(adresse.sun_path, "socket_serveur");
  
  // On connect le socket au serveur
  if((connect(sockfd, (struct sockaddr *)&adresse, sizeof(adresse))==-1)){
      perror("pb connect : Client");
      exit(1);
  }

  long_adresse=sizeof(adresse);
  // On peut maintenant écrire et lire via sockfd
  printf("Le client a écrit : %c \n",ch);
  //write(sockfd, &ch, 1); // le client écrit
  sendto(sockfd, &ch,1, 0, (struct sockaddr *)&adresse, long_adresse);
  //read(sockfd, &ch, 1); // le client lit 
  recvfrom(sockfd, &ch, 1, 0, (struct sockaddr *)&adresse, &long_adresse);
  printf("Le serveur a renvoyé : %c\n", ch);

  //on ferme le socket qui n'est plus utile
  close(sockfd);
  return 0;
}
