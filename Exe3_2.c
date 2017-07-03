#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
	
	
int main (int argc, char *argv[])
{
		char str2[100];

		int resultado = 14;
		pid_t	pid;
		int status;
		int fd;
		pid=fork();
		if(pid<0)
		{
			printf("Erro na criação de processo filho");
			perror(argv[0]);
			exit(errno);
		}
		else if(pid>0) //Processo Pai
		{
			if((fd = open("com", O_RDONLY))<0){
					printf("PAI: Falha na leitura!");
					perror(argv[0]);
					exit(EXIT_FAILURE);
			}
				else
			{	
				wait(&status);
				read(fd,str2,100);
				resultado = resultado- atoi(str2);
				
				close(fd);
				wait(&status);
					
					if((fd=open("com", O_WRONLY | O_NDELAY))<0){
					printf("P2: Erro COM");
					perror(argv[0]);
					exit(EXIT_FAILURE);
					
					}
					else
					{
					sprintf(str2,"%i",resultado); 
					write(fd,str2,sizeof(str2));
					close(fd);
					}
				
			
			}
			exit(EXIT_SUCCESS);
		}
		else if(pid==0)
			execl("Exe3_3","Exe3_3",NULL);
	
}
