#include <linux/futex.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <common.h>

int main(int argc, char *argv[])
{
	char c;
	unsigned long i;
	int result;
	int errr;
	int shmid;
  key_t key = KEYVAL;
  int *shm;
  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
    perror("shmget");
    exit(1);
  }
  if((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
    perror("shmat");
    exit(1);
  }
	*shm = 0;
	print_futex(shm);
	*shm = 1;
	print_futex(shm);

	for(i = 0; i < ARR_SIZE; i++) {
		shm[i + 1] = ((10 + i) * (10 + i)) % 5;
	}
	print_arr(shm + 1, ARR_SIZE);

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
