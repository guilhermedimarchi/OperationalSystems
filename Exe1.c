#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h>
#include <math.h>   //pow
#include <unistd.h> // fork
#include <fcntl.h>

void Pai(pid_t pid, int *status);
void Filho(pid_t pid, int *status);

int main (int argc, char *argv[])
{
	int status;
	pid_t pid;
	printf("Duplicando o processo\n");
	mknod("com", S_IFIFO|0666, 0);//Create a pipe
	
	pid = fork();
	
	if(pid<0)
	{
		printf("Processo filho nao pode ser criado");
		perror(argv[0]);
	}
	else if(pid>0)
		{
			Pai(pid,&status);
			wait(&status);
				
		}
	else
	{
			Filho(pid,&status);
			
	}
		//
	exit(EXIT_SUCCESS);
}
// Se Processo pai
void Pai(pid_t	pid, int *status)
{
		
		char str2[100];
		double result;
		int fd;
			fd = open("com", O_RDONLY);
		if (fd < 0)
		{
			//perror(argv[0]);
			exit (EXIT_FAILURE);
		}
		
		wait(status);
		
		read(fd,str2, 100);
		close(fd);
		
		result = atol(str2);
		
		printf("PAI: Valor calculado: %lf",result);
		
		unlink("com");
	
		printf("PAI encerrando Processo");
}



//Executa um calculo de potenciacao
void Filho(pid_t pid, int *status)
{
	float base;
	float expoente;
	float resultado;
	int fd;
	char str[100];
	printf("Digite o valor 1:");
	scanf("%f", &base);
	fflush(stdin);
	
	printf("Digite o valor 2:");
	scanf("%f", &expoente);
	fflush(stdin);
	resultado=pow(base,expoente);
	
	sprintf(str,"%lf",resultado);
	if((fd=open("com",O_WRONLY | O_NDELAY))<0)
	{
				//perror(argv[0]);
				exit(EXIT_FAILURE);
	}
	write(fd,str,sizeof(str));
	close(fd);
		
	printf("FILHO: Finalizando processo \n");
}

