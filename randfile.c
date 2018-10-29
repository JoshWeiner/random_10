#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int* num_gen() {
	int fd = open("/dev/random", O_RDONLY);
	if(fd == -1) {
		printf("Errno: %d\n", errno);
	}

	int * rand = malloc(sizeof(int));
	fd = read(fd, rand, sizeof(int));
	fd = close(fd);

	return rand;
}

int main() {
	int num_array[10];
	int *rand_num;
  int fd;
	printf("Generating random values:\n");
	for(int i = 0;i < 10; i++) {
		rand_num = num_gen();
		printf("Random number %d: %d\n", i, *rand_num);
    num_array[i] = *rand_num;
  }

  printf("Writing random numbers to file:\n");
	fd = open("./test.txt", O_WRONLY | O_CREAT, 0664);
	if(fd < 0) {
		printf("Errno: %d\n", errno);
	}
  else {
    write(fd, num_array, 10*sizeof(int));
    close(fd);
    printf("Success, no errors. \n");
  }

  printf("Reading random numbers from file:\n");
	int new_array[10];
	fd = open("./test.txt", O_RDONLY, 0664);
	if(fd < 0) {
		printf("Errno: %d\n", errno);
	}
  else {
	   read(fd, new_array, 10*sizeof(int));
	   close(fd);
     printf("Success, no errors. \n");
  }

	printf("Testing written values:\n");
	for(int i = 0; i < 10; i++) {
		printf("Position %d: %d\n", i, new_array[i]);
	}

	return 0;
}
