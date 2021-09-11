#include <stdio.h>
#include <pthread.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define CLE 217 //cle de la SHM  

int main() { 

	char commande[20];
	int status;
	const int nbuff = 100;
	int rep;

	//VAR MEMOIRE PARTAGEE
	char* mem; //pointuer sur la SHM
	int shmid; // id de la SHM

	FILE *f;
	char pid_screen[8];
	
	int shell_to_noyau[2];
	int noyau_to_shell[2];
	pipe(shell_to_noyau);
	pipe(noyau_to_shell);

	//GET PID
	f = fopen("pid.txt", "r"); 		//r for Read
	if (f == NULL){
		printf("No such file !");
		return 0;
	}
	fscanf(f, "%s", pid_screen); 
	fclose(f);	
	
	//CREATE FORK
	int noyau;
	noyau = fork();
	if (noyau != 0){ //PERE = SHELL
		printf("BONJOUR, je suis votre super Shell !\n");
		ssize_t n;
		char res_received[nbuff];
		
		//CREATE SHM
		shmid = shmget((key_t)CLE, 1000, IPC_CREAT|0750);
		mem = shmat(shmid, NULL, 0);

		do {
			//ASK FOR COMMANDE			
			printf("Shell - Quelle est votre commande ? (\"stop\" pour fermer le terminal)\n");
			scanf("%s", &commande);	
			fflush(stdin);
			printf("Shell - Je suis le pere et j'envoie au noyau : %s\n", commande);

			if (strcmp(commande, "stop") != 0){
				//SEND COMMANDE TO NOYAU
				write(shell_to_noyau[1], &commande, strlen(commande));

				//GET RESULT BACK FROM NOYAU
				n = read(noyau_to_shell[0], res_received, nbuff-1);
				res_received[n] = '\0';
				printf("Command back with result : %s\n", res_received);

				//SEND TO SCREEN
				strcpy(mem, res_received);
							
				//SEND SIGNAL TO SCREEN
				rep = kill(atoi(pid_screen), SIGHUP);
				if (rep == -1){
					printf("Impossible de communiquer avec l'ecran");
					return (0);
				}

			} else {
				strcpy(mem, "stop");
				rep = kill(atoi(pid_screen), SIGHUP);
				rep = kill(atoi(pid_screen), SIGINT);
				if (rep == -1){
					printf("Impossible de communiquer avec l'ecran");
					return (0);
				}
				return (0);
			}

		} while (strcmp(commande, "stop") != 0);
		
		wait(&status);
		return (0);


	} else { //FILS = NOYAU
		while (strcmp(commande, "stop") != 0){

			char res_received[nbuff];
			//char* res_sgf[nbuff];
			ssize_t n;
			
			//READ IN PIPE
			n = read(shell_to_noyau[0], res_received, nbuff-1);
			sleep(1);
			res_received[n] = '\0';
			printf("Noyau - Je suis le noyau et je recois : %s\n", res_received);
			
			// SGF
			//respository managment
			if (strcmp(res_received, "ls") == 0){
					char* res_sgf = "J'ai reçu ls\n";
					printf("res : %s\n", res_sgf);
					sleep(1);
					write(noyau_to_shell[1], res_sgf, nbuff);
			} else if (strcmp(res_received, "ls -l") == 0){
					printf("J'ai reçu ls -l");
			} else if (strcmp(res_received, "mkdir") == 0){
					printf("J'ai reçu mkdir");
			} else if (strcmp(res_received, "rmdir") == 0){
					printf("J'ai reçu rmdir");
			} else if (strcmp(res_received, "cd") == 0){
					printf("J'ai reçu cd");
			
			//file management
			} else if (strcmp(res_received, "cp") == 0){
					printf("J'ai reçu cp");
			} else if (strcmp(res_received, "rm") == 0){
					printf("J'ai reçu rm");
			} else if (strcmp(res_received, "mv") == 0){
					printf("J'ai reçu mv");
			} else if (strcmp(res_received, "cat") == 0){
					printf("J'ai reçu cat");
			} else if (strcmp(res_received, "echo > file") == 0){
					printf("J'ai reçu echo");
			} else {
					printf("Cette commande n'existe pas");
			}


			//SEND RESULT IN PIPE


		} 
	}

	return (0);
}
