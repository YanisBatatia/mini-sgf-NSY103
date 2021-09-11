#include <stdio.h>
#include <pthread.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdbool.h>

#define CLE 217 //cle de la SHM 

char* mem; //pointeur sur la SHM

void action_signal(int signal){
	if(signal == SIGHUP){
		int shmid = shmget((key_t)CLE, 0, 0); //récup id de la SHM
		mem = shmat(shmid, NULL, 0); // attachement à la SHM
		if (mem != "stop"){
			printf("%s\n", mem); // lecture de la SHM
		} else {
			exit(EXIT_FAILURE);
		}
	}
}

int main() {
	FILE * f;
	pid_t pid = getpid();
	f = fopen("pid.txt", "r+");
	fprintf(f, "%d", getpid());
	fclose(f);
	int rep;
	int rep2;
	
	printf("VOICI LE PLUS BEL ECRAN DU MONDE\n");
	sleep(1);

	int err;
	struct sigaction action;
	action.sa_handler = action_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(SIGHUP, &action, NULL)==-1){
		printf("Impossible d'appeler signaction\n");
		exit(EXIT_FAILURE);
	}
	while(1){
		//printf(".\n");
		sleep(1);
	}

		

	return (0);
}
