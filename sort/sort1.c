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

	syscall(SYS_futex, shm, FUTEX_WAIT, 1, NULL, NULL, 0);

	while(!bubble_iter(shm + 1, ARR_SIZE)) {
		*shm = 0;
		print_futex(shm);
		printf("Waking waiters...\n");
		syscall(SYS_futex, shm, FUTEX_WAKE, 1, NULL, NULL, 0);
		print_arr(shm + 1, ARR_SIZE);
		sleep(3);
		syscall(SYS_futex, shm, FUTEX_WAIT, 1, NULL, NULL, 0);
	}
	printf("Done.\n");
	shmdt(shm);
	return 0;
}
