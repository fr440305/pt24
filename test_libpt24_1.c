#include <stdio.h>
#include <string.h>

#include "libpt24.h"

int main() {
	long test_cases[6][4] = {
		{1, 2, 3, 4},
		{2, 2, 3, 3},
		{7, 7, 8, 8},
		{4, 4, 10, 10},
		{2, 4, 8, 16},
		{2, 3, 4, 5}
	};
	char buf[512] = {0};
	int i;

	for (i = 0; i < 6; i++) {
		printf(
			"%ld %ld %ld %ld : ",
			test_cases[i][0], test_cases[i][1], test_cases[i][2], test_cases[i][3]
		);

		explicit_bzero((void *)(buf), 512);

		switch (libpt24_find_solution(test_cases[i], buf, 512, OFMT_PARENTHESIS)) {
		case 0: // No solution
			printf("No solution.\n");
			break;

		case 1: // Success
			printf("%s\n", buf);
			break;

		case -1: // Buffer overflow
			printf("Buffer overflow.\n");
			break;
		}
	}

	return 0;
}
