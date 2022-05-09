#include "asm6502.h"

typedef struct {
    char *prog;
    char *out;
    char **in;
    int in_len;
} options;

static void parse_args(int argc, char **argv, options *opt)
{
    opt->in = calloc(sizeof(char *), argc);
    opt->in_len = 0;
    opt->prog = argv[0];
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (!strcmp(arg, "-o")) {
            opt->out = arg;
        } else {
            opt->in[opt->in_len] = arg;
            opt->in_len++;
        }
    }
    if (opt->out == NULL) {
        opt->out = "6502.rom";
    }
}

int main(int argc, char **argv)
{
    options opt = {0};
    parse_args(argc, argv, &opt);
    if (opt.in_len == 0) {
        err_die("usage: %s [-o OUT] SOURCE...", opt.prog);
    }
    program p = {0};
    asm_all(&p, opt.in, opt.in_len);
    asm_link(&p);
    prog_write(&p, opt.out);
    return 0;
}
