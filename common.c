#include <common.h>
#include <stdio.h>

void print_futex(int *futex_ptr) {
	    printf("%s\n", (*futex_ptr) ? "Locked": "Unlocked");
}

