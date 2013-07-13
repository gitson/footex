#include <common.h>
#include <stdio.h>


void print_arr(int *arr, int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int bubble_iter(int *arr, int n) {
	int i;

	for(i = 0; i < n - 1; i++) {
		if(arr[i] > arr[i + 1]) {
			SWAP(arr, i, i + 1);
			return 0;
		}
	}
	return 1;
}

void print_futex(int *futex_ptr) {
	    printf("%s\n", (*futex_ptr) ? "Locked": "Unlocked");
}

