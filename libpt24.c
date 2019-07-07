#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libpt24.h"

char EXPR_TYPES[5][8] = {
	"ffxxfxx",
	"fffxxxx",
	"ffxfxxx",
	"fxffxxx",
	"fxfxfxx"
};

char *EXPR_TYPE_FFXXFXX = EXPR_TYPES[0];
char *EXPR_TYPE_FFFXXXX = EXPR_TYPES[1];
char *EXPR_TYPE_FFXFXXX = EXPR_TYPES[2];
char *EXPR_TYPE_FXFFXXX = EXPR_TYPES[3];
char *EXPR_TYPE_FXFXFXX = EXPR_TYPES[4];

/* === fraction */

struct fraction {
	long n;
	long d;
};

struct fraction fraction_new(long a) {
	struct fraction ret;

	ret.n = a;
	ret.d = 1;

	return ret;
}

struct fraction fraction_add(
	const struct fraction f1,
	const struct fraction f2
) {
	struct fraction ret;

	ret.n = f1.n * f2.d + f2.n * f1.d;
	ret.d = f1.d * f2.d;

	return ret;
}

struct fraction fraction_sub(
	const struct fraction f1,
	const struct fraction f2
) {
	struct fraction ret;

	ret.n = f1.n * f2.d - f2.n * f1.d;
	ret.d = f1.d * f2.d;

	return ret;
}

struct fraction fraction_mul(
	const struct fraction f1,
	const struct fraction f2
) {
	struct fraction ret;

	ret.n = f1.n * f2.n;
	ret.d = f1.d * f2.d;

	return ret;
}

struct fraction fraction_div(
	const struct fraction f1,
	const struct fraction f2
) {
	struct fraction ret;

	ret.n = f1.n * f2.d;
	ret.d = f1.d * f2.n;

	return ret;
}

struct fraction fraction_op(
	char op,
	const struct fraction f1,
	const struct fraction f2
) {
	struct fraction dummy;

	switch (op) {
	case '+': return fraction_add(f1, f2);
	case '-': return fraction_sub(f1, f2);
	case '*': return fraction_mul(f1, f2);
	case '/': return fraction_div(f1, f2);
	}

	printf("INTERAL_ERROR: fraction_op: op == %c\n", op);
	return dummy;

}

/* === expression */

struct expression {
	//char type[8]; // type[7] == 0 for all expression
	char *type;
	long *a; // a0, a1, a2, a3
	char f[3]; // either '+', '-', '*', or '/'
};

void expression_print(const struct expression *this);

int expression_calculate(
	const struct expression *this,
	struct fraction *result
) {
	char f = this->f[0];
	char g = this->f[1];
	char h = this->f[2];
	struct fraction a = fraction_new(this->a[0]);
	struct fraction b = fraction_new(this->a[1]);
	struct fraction c = fraction_new(this->a[2]);
	struct fraction d = fraction_new(this->a[3]);

	if (this->type == EXPR_TYPE_FFXXFXX) {
		*result = fraction_op(f, fraction_op(g, a, b), fraction_op(h, c, d));
	} else if (this->type == EXPR_TYPE_FFFXXXX) {
		*result = fraction_op(f, fraction_op(g, fraction_op(h, a, b), c), d);
	} else if (this->type == EXPR_TYPE_FFXFXXX) {
		*result = fraction_op(f, fraction_op(g, a, fraction_op(h, b, c)), d);
	} else if (this->type == EXPR_TYPE_FXFFXXX) {
		*result = fraction_op(f, a, fraction_op(g, fraction_op(h, b, c), d));
	} else if (this->type == EXPR_TYPE_FXFXFXX) {
		*result = fraction_op(f, a, fraction_op(g, b, fraction_op(h, c, d)));
	} else {
		printf(
			"INTERNAL_ERROR:"
			"expression_calculate. strlen(expr->type), expr->type == %ld, %s\n",
			
			strlen(this->type), this->type
		);
		expression_print(this);
	}

	return 0;
}

void expression_print(const struct expression *this) { // XXX
	struct fraction result;
	expression_calculate(this, &result);

	printf(
		"struct expression {\n"	
		"    type:       %s\n"
		"    f, g, h:    %c, %c, %c\n"
		"    a, b, c, d: %ld, %ld, %ld, %ld\n"
		"} == %ld / %ld\n",

		this->type,
		this->f[0], this->f[1], this->f[2],
		this->a[0], this->a[1], this->a[2], this->a[3],
		result.n, result.d
	);
}

int expression_is24(
	struct expression *this
) {
	struct fraction result;

	expression_calculate(this, &result);

	return (
		(result.d != 0) &&
		(result.n != 0) &&
		(result.n / result.d == 24) &&
		(result.n % result.d == 0)
	);
}

void expression_setup_permutation(
	const long a[4],
	long aa[24][4]
) {
	int i, j;
	int idxs[24][4] = {
		{0, 1, 2, 3},
		{0, 1, 3, 2},
		{0, 2, 1, 3},
		{0, 2, 3, 1},
		{0, 3, 1, 2},
		{0, 3, 2, 1},

		{1, 0, 2, 3},
		{1, 0, 3, 2},
		{1, 2, 0, 3},
		{1, 2, 3, 0},
		{1, 3, 0, 2},
		{1, 3, 2, 0},
		
		{2, 0, 1, 3},
		{2, 0, 3, 1},
		{2, 1, 0, 3},
		{2, 1, 3, 0},
		{2, 3, 0, 1},
		{2, 3, 1, 0},

		{3, 0, 1, 2},
		{3, 0, 2, 1},
		{3, 1, 0, 2},
		{3, 1, 2, 0},
		{3, 2, 0, 1},
		{3, 2, 1, 0}
	};

	for (i = 0; i < 24; i++) {
		for (j = 0; j < 4; j++) {
			aa[i][j] = a[idxs[i][j]];
		}
	}
}

/* if no solution, return 0, else return 1 */
int expression_find_solution(
	struct expression *this,
	long a[4]
) {
	char ops[4] = {'+', '-', '*', '/'};
	long aa[24][4];
	int i, j, k, t, p;

	/* setup aa[][] */
	expression_setup_permutation(a, aa);

	/* traverse */
	for (i = 0; i < 4; i++) {
		this->f[0] = ops[i];
		for (j = 0; j < 4; j++) {
			this->f[1] = ops[j];
			for (k = 0; k < 4; k++) {
				this->f[2] = ops[k];
				for (t = 0; t < 5; t++) {
					this->type = EXPR_TYPES[t];
					for (p = 0; p < 24; p++) {
						this->a = aa[p];

						//expression_print(this);

						if (expression_is24(this)) {
							//printf("INTERNAL_HINT: Find it!\n");
							return 1;
						}
					}
				}
			}
		}
	}

	return 0;
}

/* if buffer overflow, return -1. if success, return 0 */
int expression_print_to_buf( // TODO
	const struct expression *this,
	char *buf,
	const int cap, /* Buffer capacity */
	const int ofmt
) {
	long a = this->a[0];
	long b = this->a[1];
	long c = this->a[2];
	long d = this->a[3];

	char f = this->f[0];
	char g = this->f[1];
	char h = this->f[2];

	switch (ofmt) {

	case OFMT_DEFAULT: /* Not finished yet */ // TODO

	case OFMT_PARENTHESIS:
		if (this->type == EXPR_TYPE_FFXXFXX) {
			sprintf(buf, "((%ld %c %ld) %c (%ld %c %ld))", a, g, b, f, c, h, d);
		} else if (this->type == EXPR_TYPE_FFFXXXX) {
			sprintf(buf, "(((%ld %c %ld) %c %ld) %c %ld)", a, h, b, g, c, f, d);
		} else if (this->type == EXPR_TYPE_FFXFXXX) {
			sprintf(buf, "((%ld %c (%ld %c %ld)) %c %ld)", a, g, b, h, c, f, d);
		} else if (this->type == EXPR_TYPE_FXFFXXX) {
			sprintf(buf, "(%ld %c ((%ld %c %ld) %c %ld))", a, f, b, h, c, g, d);
		} else if (this->type == EXPR_TYPE_FXFXFXX) {
			sprintf(buf, "(%ld %c (%ld %c (%ld %c %ld)))", a, f, b, g, c, h, d);
		}
		return 0;

	case OFMT_PREFIX:
		if (this->type == EXPR_TYPE_FFXXFXX) {
			sprintf(buf, "%c %c %ld %ld %c %ld %ld", f, g, a, b, h, c, d);
		} else if (this->type == EXPR_TYPE_FFFXXXX) {
			sprintf(buf, "%c %c %c %ld %ld %ld %ld", f, g, h, a, b, c, d);
		} else if (this->type == EXPR_TYPE_FFXFXXX) {
			sprintf(buf, "%c %c %ld %c %ld %ld %ld", f, g, a, h, b, c, d);
		} else if (this->type == EXPR_TYPE_FXFFXXX) {
			sprintf(buf, "%c %ld %c %c %ld %ld %ld", f, a, g, h, b, c, d);
		} else if (this->type == EXPR_TYPE_FXFXFXX) {
			sprintf(buf, "%c %ld %c %ld %c %ld %ld", f, a, g, b, h, c, d);
		}
		return 0;

	case OFMT_POSTFIX: return -1 ; // TODO
		if (this->type == EXPR_TYPE_FFXXFXX) {
		} else if (this->type == EXPR_TYPE_FFFXXXX) {
		} else if (this->type == EXPR_TYPE_FFXFXXX) {
		} else if (this->type == EXPR_TYPE_FXFFXXX) {
		} else if (this->type == EXPR_TYPE_FXFXFXX) {
		}
		return 0;

	case OFMT_SEXPRESSION:
		if (strcmp(this->type, "ffxxfxx") == 0) {
			sprintf(buf, "(%c (%c %ld %ld) (%c %ld %ld))", f, g, a, b, h, c, d);
		} else if (strcmp(this->type, "fffxxxx") == 0) {
			sprintf(buf, "(%c (%c (%c %ld %ld) %ld) %ld)", f, g, h, a, b, c, d);
		} else if (strcmp(this->type, "ffxfxxx") == 0) {
			sprintf(buf, "(%c (%c %ld (%c %ld %ld)) %ld)", f, g, a, h, b, c, d);
		} else if (strcmp(this->type, "fxffxxx") == 0) {
			sprintf(buf, "(%c %ld (%c (%c %ld %ld) %ld))", f, a, g, h, b, c, d);
		} else if (strcmp(this->type, "fxfxfxx") == 0) {
			sprintf(buf, "(%c %ld (%c %ld (%c %ld %ld)))", f, a, g, b, h, c, d);
		}
		return 0;

	}

	return 0;
}

/* === libpt24 */

int libpt24_find_solution(
	long a[4],
	char *buf,
	int capacity,
	int ofmt
) {
	struct expression expr;

	if (!expression_find_solution(&expr, a)) {
		return 0;
	}

	if (expression_print_to_buf(&expr, buf, capacity, ofmt) == -1) {
		return -1;
	}

	return 1;
}
