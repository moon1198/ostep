#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/time.h>

int main(int argc, char ** argv) {
	int n = 100;
	if (argc == 2) {
		n = atoi(argv[1]);
	}

	int fd = open("./syscall_time.c", O_RDONLY);
	char buf[1024];
	struct timeval t1, t2;
	if (gettimeofday(&t1, NULL) == -1) {
		perror("Faild to get current time");
		return 1;
	}
	

	for (int i = 0; i != n; ++ i) {
		read(fd, buf, 0);
	}
	//printf("Seconds since epoch: %ld\n", t1.tv_sec);
    //printf("Microseconds: %ld\n", t1.tv_usec);


	if (gettimeofday(&t2, NULL) == -1) {
		perror("Faild to get current time");
		return 1;
	}
	//printf("Seconds since epoch: %ld\n", t2.tv_sec);
    //printf("Microseconds: %ld\n", t2.tv_usec);
	long seq = (((t2.tv_sec - t1.tv_sec) << 6) + t2.tv_usec - t1.tv_usec);

	printf("Call %d times, one syscall use %lf usecs.\n", n, seq / (double) n);

	return 0;
}
