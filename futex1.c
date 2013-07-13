#include <linux/futex.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <common.h>

int main(int argc, char *argv[])
{
	char c;
  int result, errr;

	key_t key = KEYVAL;
	int *shm;
	int shmid;

	if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
		perror("shmget");
		exit(1);
	}
	if((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(1);
	}
	print_futex(shm);
	result = syscall(SYS_futex, shm, FUTEX_WAIT, 1, NULL, NULL, NULL);
	if (result) {
		errr = errno;
		printf("errno: %d\n", errr);
	}
	printf("%s\n", result ? "Failed": "Futex aquired, waiting for input: ");
	while(c!='Q') {
		c = getchar();
	}
	shmdt(shm);
	return 0;
}
