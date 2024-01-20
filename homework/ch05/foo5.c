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
		printf("Child process PID : %d\n", (int) getpid());
		printf("Child wait for ret : %d\n", (int) wait(NULL));

	} else {
		printf("Parents wait for ret : %d\n", (int) wait(NULL));
		printf("Parents process\n");
		printf("Parents wait for ret : %d\n", (int) wait(NULL));
	}
	return 0;
}
