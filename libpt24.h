#ifndef _libpt24_h_
#define _libpt24_h_

#define OFMT_DEFAULT 0
//#define OFMT_DEFAULT 2

#define OFMT_PARENTHESIS 1
#define OFMT_PREFIX 2
#define OFMT_POSTFIX 3
#define OFMT_SEXPRESSION 4

#define LIBPT24_VERSION "0.0.1"

/* if no solution, return 0. if buffer overflows, return -1. if success, return 1. */
int libpt24_find_solution(
	long a[4],
	char *buf,
	int capacity,
	int ofmt
);

#endif
