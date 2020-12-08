#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
void *activite1(void *p){
	while(1){
		printf("thread1\n");
		sleep(2);
	}
	return 0;
}
void *activite2(void *p){
	while(1){
		printf("thread2\n");
		sleep(2);
	}
	return 0;
}
void *activite3(void *p){
	while(1){
		printf("thread3\n");
		sleep(2);
	}
	return 0;
}
void handler(int signo, siginfo_t *info, void *extra) {
	int i;
	for(i=0;i<3;i++){
		puts("signal");
		sleep(2);
	}
}
void set_sig_handler(void){
        struct sigaction action;
        action.sa_flags = SA_SIGINFO; 
        action.sa_sigaction = handler;
        if (sigaction(SIGUSR1, &action, NULL) == -1) {
	    perror("sigusr: sigaction");
            exit(1);
        }
}
int main(){
	printf("mon PID est : %d \n", getpid());
	printf("Lancez la commande kill -10 %d \n", getpid());
	pthread_t t1, t2, t3;
	set_sig_handler();
	pthread_create(&t1,NULL,activite1,NULL);
	pthread_create(&t1,NULL,activite2,NULL);
	pthread_create(&t1,NULL,activite3,NULL);
	pthread_exit(NULL);
	return 0;
}
