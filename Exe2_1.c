#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <wait.h>



//Filho
void opbasica(float *v1, float *v2, float *resultado, int *op);

int main(int argc, char *argv[])
{
	int fd;
	float v1=0,v2=0, resultado=0;
	int op;
	char str2[100];

	printf("\nCriando processo Filho PID: %i",getpid());
		
		
		if((fd = open("com", O_RDONLY))<0){
			perror(argv[0]);
			exit(EXIT_FAILURE);
		} 
		else
		{
					read(fd,str2, 100);
					v1 = atol(str2);
					read(fd,str2, 100);
					v2 = atol(str2);
					read(fd,str2, 100);
					op = atol(str2);
		printf("\nFILHO: Recebendo Valores, V1: %lf, V2: %lf, Operacao: %i\n", v1,v2,op);
		}
		close(fd);

		
		
		mknod("com1", S_IFIFO|0666, 0);
		unlink("com");
		printf("\nFILHO: Abrir para escrita\n");
		sleep(5);
		if((fd=open("com1", O_WRONLY | O_NDELAY))<0){
				printf("\nFILHO: Falha na escrita\n");
				perror(argv[0]);
				exit(EXIT_FAILURE);
		}
			else
			{
			opbasica(&v1, &v2, &resultado,&op);
			printf("\nFILHO: Escrevendo resultado...\n");
			sprintf(str2,"%lf",resultado); 
			write(fd,str2,sizeof(str2));
			close (fd);
			}
	exit(EXIT_SUCCESS);
}

void opbasica(float *v1, float *v2, float *resultado, int *op){
		switch(*op){
			case 1:
				*resultado= *v1+*v2;
				break;
			case 2:
				*resultado= *v1-*v2;
				break;
			case 4:
				if(*v2 != 0)
				{
					*resultado= *v1+*v2;
					break;
				}
			case 3:
				*resultado= *v1**v2;
				break;
		}
		
}

	
