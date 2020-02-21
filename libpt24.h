#ifndef _LIBPT24_H_
#define _LIBPT24_H_

#define OFMT_DEFAULT 0
#define OFMT_PARENTHESIS 1
#define OFMT_PREFIX 2
#define OFMT_POSTFIX 3
#define OFMT_SEXPRESSION 4

#define LIBPT24_VERSION "0.0.1"

/* libpt24_find_solution
//
//    - Given 4 long (64-bit) numbers, find the expression.
//
//PARAMETERS
//
//    a        : An array of 4 long numbers.
//    buf      : Buffer. The function will
//               write the string representation
//               of the expression into it.
//    capacity : The capacity of the buffer.
//    ofmt     : Output format. Be it the macros
//               that starts with ``OFMT_''.
//
//RETURN
//
//    0 : if no expression of these 4 numbers can be 24.
//    1 : Success.
//    -1: Buffer overflow. Larger buffer needed.
//
//EXAMPLE
//
//    long nums[4] = {1, 2, 3, 4};
//    char buf[512] = {0};
//    libpt24_find_solution(nums, buf, 512, OFMT_PARENTHESIS);
//    printf("%s\n", buf);
*/
int libpt24_find_solution(
	long a[4],
	char *buf,
	int capacity,
	int ofmt
);

#endif
