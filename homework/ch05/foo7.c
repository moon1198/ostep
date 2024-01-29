#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



int main() {
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0){
		close(STDOUT_FILENO);
		printf("Child process PID : %d\n", (int) getpid());

	} else {
		printf("Parents wait for ret : %d\n", (int) waitpid(rc, NULL, 0));
		printf("Parents process\n");
	}
	return 0;
}
