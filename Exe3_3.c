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
		mknod("com", S_IFIFO|0666, 0);
		int resultado=(25*4)+40 ;
		char str2[100];
		pid_t	pid;
		int fd;
		int status;
		pid=fork();
		if(pid<0)
		{
			printf("Erro na criação de processo filho");
			perror(argv[0]);
			exit(errno);
		}
		else if(pid>0) //Processo Pai
		{
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
					read(fd,str2, 100);
					resultado+= atoi(str2);
					//printf("%i", resultado);
					
					sleep(2);	
					read(fd,str2, 100);
					resultado+= atoi(str2);
					//printf("%i", resultado);
					
					close(fd);
					wait(&status);
					
					if((fd=open("com", O_WRONLY | O_NDELAY))<0){
					printf("P3: Erro COM");
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
				
			}
			else // Filho 1
			{
			sleep(2);
			execl("Exe3_5","Exe3_5",NULL);
			}
		}
		else // Filho 2
		{
			
				execl("Exe3_4","Exe3_4",NULL);
		}

}

