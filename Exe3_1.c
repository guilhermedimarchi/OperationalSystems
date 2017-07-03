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
		mknod("com", S_IFIFO|0666, 0);
		
		int resultado = 25;
		int status;
		int fd;
		
		pid_t	pid;
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
				
				resultado =  atoi(str2)+resultado;
				printf("%i", resultado);
			
			}
			exit(EXIT_SUCCESS);
			unlink("com");
		}
		else if(pid==0)
			execl("Exe3_2","Exe3_2",NULL);
	
}
