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
		int resultado = -((20/2)+10);
		int fd;
		char str2[100];
		if((fd=open("com", O_WRONLY | O_NDELAY))<0){
				printf("P4: Erro COM");
				perror(argv[0]);
				exit(EXIT_FAILURE);
		}
		else
		{
			sprintf(str2,"%i",resultado); 
			write(fd,str2,sizeof(str2));
			close(fd);
		}
	exit(EXIT_SUCCESS);
}
