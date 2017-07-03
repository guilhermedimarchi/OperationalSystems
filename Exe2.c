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

int main(int argc, char *argv[])
{
	int  fd;
	double v1=0,v2=0, resultado=0;
	int op;
	char str2[100];
	pid_t pid;
	
	pid = fork();
	if(pid < 0)
	{
		printf("Erro na criação de processo filho!!!\n");
			perror(argv[0]);
			exit(errno);
	}
	else if (pid>0)
		{
			printf("Criando processo Pai PID: %i\n\n",getpid());
			mknod("com", S_IFIFO|0666, 0);

			printf("Digite o Valor 1:");
			scanf("%lf",&v1);
			fflush(stdin);
			
			printf("Digite o valor 2:");
			scanf("%lf",&v2);
			fflush(stdin);
			
			printf("Escolha:\n 1. Soma\n 2. Subtracao\n 3. Multiplicacao\n 4. Divisao \n\nQual a operação desejada:");
			scanf("%i",&op);
			fflush(stdin);
			
			if((fd=open("com", O_WRONLY | O_NDELAY))<0){
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
			sprintf(str2,"%lf",v1); 
			write(fd,str2,sizeof(str2));
			
			
			sprintf(str2,"%lf",v2); 
			write(fd,str2,sizeof(str2));
		
			
			sprintf(str2,"%i",op); 
			write(fd,str2,sizeof(str2));
			
			
			close(fd);
			printf("PAI: Esperando Filho\n");
		
		
			
			if((fd = open("com1", O_RDONLY))<0){
				printf("PAI: Falha na leitura!");
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
			else
			{
					printf("PAI: Aguardando Resultado\n");
					read(fd,str2, 100);
					resultado = atol(str2);
					close(fd);
					printf("\nPAI: Resultado %lf",resultado);
						unlink("com");
							unlink("com1");
			} 
		}
	else if (pid==0)
		{
			
			execl("Exe2_1","Exe2_1", NULL);
					
		}
	
		exit(EXIT_SUCCESS);
}
	
	
