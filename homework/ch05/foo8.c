#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



int main() {
	int pipefd[2];
	char buf;
	
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(-1);
	}

	int rc1 = fork();
	if (rc1 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc1 == 0){
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		printf("hello world\n");

	} else {
		int rc2 = fork();
		if (rc2 < 0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc2 == 0){

			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			char buf[15];
			read(STDIN_FILENO, buf, 12);
			printf("%s", buf);

		}

	}
	return 0;
}
