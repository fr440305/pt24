#include <stdio.h>
#include <string.h>

#define OFMT_DEFAULT 0
#define OFMT_PARENTHESIS 1
#define OFMT_PREFIX 2
#define OFMT_POSTFIX 3
#define OFMT_SEXPRESSION 4

#define CONFIG_NOERR 0
// starts from 1.
#define CONFIG_ERR_ARG_NOT_ENOUGH 1
#define CONFIG_ARR_ARG_UNREGONIZABLE 2

char EXPR_TYPES[5][8] = {
	"fffxxxx",
	"fxfxfxx",
	"fxfxfxx", // TODO
	"fxfxfxx", //
	"fxfxfxx", //
};

struct config {
	char *xxarg; // unregonized argument

	int h;
	int v;
	int ofmt;
	int a, b, c, d;
};

// return err code.
int config_parse_from_args(
	struct config *this,
	int argc,
	char **argv
) {
	return CONFIG_NOERR;
}

void conf_print_err(
	struct config *this,
	int err_code
) {
}

struct fraction {
	int numerator;
	int denominator;
};

int fraction_add(
	const struct fraction *f1,
	const struct fraction *f2,
	struct fraction *res
) {
	return 0;
}

int fraction_sub(
	const struct fraction *f1,
	const struct fraction *f2,
	struct fraction *res
) {
	return 0;
}

int fraction_mul(
	const struct fraction *f1,
	const struct fraction *f2,
	struct fraction *res
) {
	return 0;
}

int fraction_div(
	const struct fraction *f1,
	const struct fraction *f2,
	struct fraction *res
) {
	return 0;
}

int fraction_op(
	char op,
	struct fraction *this,
	struct fraction *that
) {
	switch (op) {
	case '+':
	case '-':
	case '*':
	case '/':
		break;
	}

	return 0;
}

struct expression {
	char type[8]; // type[7] == 0 for all expression
	char f[3]; // either '+', '-', '*', or '/'
	int a[4]; // a1, a2, a3, a4
};

// 0, .. , 4
int expression_set_type_by_idx(struct expression *this, int idx) {
	int i;

	if (!(idx >= 0 && idx <= 5)) {
		return -1;
	}

	for (i = 0; i < 8; i++) {
		this->type[i] = EXPR_TYPES[idx][i];
	}

	return 0;
}


int expression_calculate(
	struct expression *this,
	struct fraction *result
) {
}

int expression_is24(
	struct expression *this
) {
	for (i = 0; i <= 5; i++) {
		if (strcmp(EXPR_TYPES[i], this->type) == 0) {
		}
	}
	return 0; // Not 24. Dummy
}

int expression_print_to_buf(
	struct expression *this,
	char *buf,
	int ofmt
) {
	switch (ofmt) {

	case OFMT_DEFAULT:

	case OFMT_PARENTHESIS:

	case OFMT_PREFIX:

	case OFMT_POSTFIX:

	case OFMT_SEXPRESSION:
		break;
	}

	return 0;
}

/* === pt24 */

int pt24_find_solution(
	const struct config *c,
	struct expression *expr
) {
	expr->a[0] = c->a;
	expr->a[1] = c->b;
	expr->a[2] = c->c;
	expr->a[3] = c->d;

	return 1;
}

void pt24_print_help() {
	printf(
		"This is a help string.\n"
		"This is another help string.\n"
		"This is the last help string.\n"
	);
}

void pt24_print_version() {
	printf("0.0.1");
}

int main(
	int argc,
	char **argv
) {
	struct config conf;

	int conf_err = config_parse_from_args(&conf, argc, argv);

	if (conf_err) {
		config_print_err(&conf, conf_err);
		return 2;
	}

	if (conf.h) {
		pt24_print_help();
		return 0;
	}

	if (conf.v) {
		pt24_print_version();
		return 0;
	}



	
	return 0;
}
