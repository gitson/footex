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
  print_futex(shm);
	(*shm) = 1;
  print_futex(shm);
	
	do {
		c = getchar();
		if ('\n' == c) {
			continue;
		}
		print_futex(shm);
	} while(c!='X');
	printf("Unlocking futex\n");
	*shm = 0;
	printf("Waking waiters...\n");
	syscall(SYS_futex, shm, FUTEX_WAKE, 1, NULL, NULL, 0);
	if(result) {
		errr = errno;
		printf("errno: %d\n", errr);
	}
	printf("Done.\n");
	c = 0;
	do {
		c = getchar();
	} while(c!='X');
	shmdt(shm);
	return 0;
}
