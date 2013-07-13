#ifndef _COMMON_H_
#define _COMMON_H_

int bubble_iter(int *, int);
void print_arr(int *, int);

#define SWAP(ARR,A,B) {\
	printf("Swapping arr[%d]=%d and arr[%d]=%d\n", A, ARR[A], B, ARR[B]);\
	ARR[A]^=ARR[B];ARR[B]^=ARR[A];ARR[A]^=ARR[B];\
}

#define ARR_SIZE (10)
#define SHMSZ (sizeof(int) * (1 + ARR_SIZE))
#define KEYVAL (56789)

void print_futex(int *);

#endif /* _COMMON_H_ */
