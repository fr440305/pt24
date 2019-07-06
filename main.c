#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libpt24/libpt24.h>

/* #define CONFIG_NOERR 0 */
// starts from 1.

#define ERR_CONFIG_ARG_NOT_ENOUGH 1
#define ERR_CONFIG_ARG_UNREGONIZABLE 2
#define ERR_EXPR_TOO_LONG 3

#define PT24_HELP\
	"Help string.\n"\
	"Another line.\n"\
	"End of help.\n"


#define developing 1

/* === config */

struct config {
	char *xxarg; // unregonized argument

	int h;
	int v;
	int ofmt;
	long a[4];
};

// return err code.
int config_parse_from_args(
	struct config *this,
	int argc,
	char **argv
) {
	int num_off;
	long nums[4];
	char *endptr[1];
	int i;

	explicit_bzero(this, sizeof(struct config));

	if (argc <= 1) {
		return ERR_CONFIG_ARG_NOT_ENOUGH;
	}

	if (argv[1][0] == '-') {
		if (strcmp(argv[1], "-h") == 0) {
			this->h = 1;
			return 0;
		}

		if (strcmp(argv[1], "-v") == 0) {
			this->v = 1;
			return 0;
		}

		/* a.out -ofmt a b c d => argc == 6 */
		if (argc < 6) {
			return ERR_CONFIG_ARG_NOT_ENOUGH;
		}

		if (strcmp(argv[1], "-prefix") == 0) {
			this->ofmt = OFMT_PREFIX;
		} else if (strcmp(argv[1], "-postfix") == 0) {
			this->ofmt = OFMT_POSTFIX;
		} else if (strcmp(argv[1], "-parenthesis") == 0) {
			this->ofmt = OFMT_PARENTHESIS;
		} else if (strcmp(argv[1], "-sexpression") == 0) {
			this->ofmt = OFMT_SEXPRESSION;
		} else {
			this->xxarg = argv[1];
			return ERR_CONFIG_ARG_UNREGONIZABLE;
		}

		num_off = 2;
	} else {
		if (argc < 5) {
			return ERR_CONFIG_ARG_NOT_ENOUGH;
		}

		num_off = 1;
	}

	/* Reading numbers */
	for (i = 0; i < 4; i++) {
		this->a[i] = strtol(argv[num_off + i], endptr, 10);
		if (**endptr != '\0') {
			this->xxarg = argv[num_off + i];
			return ERR_CONFIG_ARG_UNREGONIZABLE;
		}

	}

	return 0;
}

/* For debugging use only */
#if developing
void config_print(
	struct config *conf
) {
	char *ofmt_strings[5] = {
		"OFMT_DEFAULT",
		"OFMT_PARENTHESIS",
		"OFMT_PREFIX",
		"OFMT_POSTFIX",
		"OFMT_SEXPRESSION"
	};

	printf(
		"struct config {\n"
		"    xxarg : %s\n"
		"    h, v  : %d, %d\n"
		"    ofmt  : %s\n"
		"\n"
		"    a, b, c, d: %ld, %ld, %ld, %ld\n"
		"}\n",

		conf->xxarg,
		conf->h, conf->v,
		ofmt_strings[conf->ofmt],
		conf->a[0], conf->a[1], conf->a[2], conf->a[3]
	);
}
#endif

void config_print_err(
	struct config *this,
	int err_code
) {
	if (err_code) {
		switch (err_code) {
		case ERR_CONFIG_ARG_NOT_ENOUGH:
			fprintf(stderr, "ERROR: Too few argument.\n");
			break;
		case ERR_CONFIG_ARG_UNREGONIZABLE:
			fprintf(
				stderr,
				"ERROR: Unregonizable argument: %s\n",
				this->xxarg
			);
			break;
		}
	}
}

/* === pt24_command_line */

void pt24_print_help(FILE *o) {
	fprintf(o, "%s\n", PT24_HELP);
}

void pt24_print_version() {
	printf("%s\n", PT24_VERSION);
}

int main(
	int argc,
	char **argv
) {
	struct config conf;
	char expr_str[128] = {0};

	int conf_err = config_parse_from_args(&conf, argc, argv);

#if developing
	config_print(&conf);
#endif

	if (conf_err) {
		config_print_err(&conf, conf_err);
		pt24_print_help(stderr);
		return 2;
	}

	if (conf.h) {
		pt24_print_help(stdout);
		return 0;
	}

	if (conf.v) {
		pt24_print_version();
		return 0;
	}

	switch (libpt24_find_solution(conf.a, expr_str, 128, conf.ofmt)) {
	case -1:
		fprintf(stderr, "WARNING: Expression too long.\n");
		return -1;
	case 0:
		printf("No solution.\n");
		break;
	case 1:
		printf("%s\n", expr_str);
		break;
	}

	return 0;
}
