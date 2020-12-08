#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
pthread_t tid[2]; 
int compteur; 
void* travail(void *arg) { // le travail des 2 threads
	int i = 0, j; 
	compteur += 1; 
	printf("\n thread %d a commencé\n", compteur); 
	for(i; i<5;i++){
	    printf("Valeur de i : %d \n", i);
		//for (j=0; j<0xFFFFFFF; j++); // un peu de travail
	}
	printf("\n thread %d est terminé\n", compteur); 
	return 0; 
} 
int main(void) { 
	int i = 0; 
	int erreur; 
	while(i < 2) { 
		erreur = pthread_create(&(tid[i]), NULL, &travail, NULL); 
		if (erreur != 0) 
			printf("\nThread ne peut être créé : [%s]", strerror(erreur)); 
		i++; 
	} 
	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 
	return 0; 
} 
