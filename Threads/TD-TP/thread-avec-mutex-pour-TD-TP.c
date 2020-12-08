#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 

pthread_t tid[2]; 
int compteur; 
pthread_mutex_t lock; 

void* travail(void *arg) { 
	pthread_mutex_lock(&lock); 
	int i = 0, j; 
	compteur += 1; 
	printf("\n thread %d a commencé\n", compteur); 
	for(i; i<5;i++){
	    printf("Valeur de i : %d \n", i);
		for (j=0; j<0xFFFFFFF; j++); // un peu de travail
	}
	printf("\n thread %d est terminé\n", compteur);  
	pthread_mutex_unlock(&lock); 
	return NULL; 
} 
int main(void) { 
	int i = 0; 
	int erreur; 
	if (pthread_mutex_init(&lock, NULL) != 0) { 
		printf("\n mutex init a raté\n"); 
		return 1; 
	} 
	while(i < 2) { 
		erreur = pthread_create(&(tid[i]), NULL, &travail, NULL); 
		if (erreur != 0) 
			printf("\nThread ne peut être créé : [%s]", strerror(erreur)); 
		i++; 
	} 
	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 
	pthread_mutex_destroy(&lock); 
	return 0; 
} 
