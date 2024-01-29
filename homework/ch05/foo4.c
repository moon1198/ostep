#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0){
		printf("Child process\n");
		//v --> argument are store in vector
		//e --> bring up env
		//l --> argument are store in list

		char *argv[] = {"ls", "-l", NULL};
		char *envp[] = {NULL};
		//execve("/bin/ls", argv, envp);
		//execv("/bin/ls", argv);
		execvp("ls", argv);

		//execl("/bin/ls", "ls", "-l", NULL);
		
		//execle("/bin/ls", "ls", "-l", NULL, envp);
		
		//execlp("ls", "ls", "-l", NULL);


	} else {
		printf("Parents process\n");
	}
	return 0;
}
