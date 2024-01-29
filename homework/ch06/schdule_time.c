#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>
#include <sched.h>
//#define _GNU_SOURCE
//#include <sched.h>


int main(int argc, char ** argv) {
	int n = 100;
	if (argc == 2) {
		n = atoi(argv[1]);
	}

	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);

	int pipe1[2], pipe0[2];
	if (pipe(pipe1) == -1) {
		exit(-1);
	}else if (pipe(pipe0) == -1) {
		exit(-1);
	}

	struct timeval t1, t2;
	if (gettimeofday(&t1, NULL) == -1) {
		perror("Faild to get current time");
		return 1;
	}
	pid_t rc = fork();
	
	if (rc < 0) {
		perror("fork failed.");
	}else if (rc == 0) {
		sched_setaffinity(getpid(), sizeof(cpuset), &cpuset);
		//parents
		close(pipe0[1]);
		close(pipe1[0]);
		for (int i = 0; i < n; ++ i) {
			write(pipe0[1], NULL, 0);
			read(pipe1[0], NULL, 0);
		}
		if (gettimeofday(&t2, NULL) == -1) {
			perror("Faild to get current time");
			return 1;
		}
		//printf("Seconds since epoch: %ld\n", t2.tv_sec);
    	//printf("Microseconds: %ld\n", t2.tv_usec);
		long seq = (((t2.tv_sec - t1.tv_sec) << 6) + t2.tv_usec - t1.tv_usec);

		printf("Call %d times, one syscall use %lf usecs.\n", n, seq / (double) n);
	}else{
		//child
		sched_setaffinity(getpid(), sizeof(cpuset), &cpuset);
		close(pipe1[1]);
		close(pipe0[0]);
		for (int i = 0; i < n; ++ i) {
			write(pipe1[1], NULL, 0);
			read(pipe0[0], NULL, 0);
		}

	}


	return 0;
}
