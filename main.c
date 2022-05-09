#include "asm6502.h"

typedef struct {
    char *prog;
    char *out;
    char **in;
    int in_len;
} options;

static void usage(int code, char *prog)
{
    printf(
        "usage: %s [options] SOURCE...\n"
        "options:\n"
        " -h --help          print this help and exit\n"
        " -o --output OUT    write output to OUT\n",
    prog);
    exit(code);
}

static void parse_args(int argc, char **argv, options *opt)
{
    opt->in = calloc(sizeof(char *), argc);
    opt->in_len = 0;
    opt->prog = argv[0];
    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        if (!strcmp(arg, "-o") || !strcmp(arg, "--output")) {
            if (opt->out != NULL) {
                err_die("usage: multiple output files given for %s", arg);
            }
            i++;
            if (i >= argc) {
                err_die("usage: no file given for %s", arg);
            }
            opt->out = argv[i];
        } else if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
            usage(0, opt->prog);
        } else {
            opt->in[opt->in_len] = arg;
            opt->in_len++;
        }
    }
    if (opt->out == NULL) {
        opt->out = "wdc6502.rom";
    }
}

int main(int argc, char **argv)
{
    options opt = {0};
    parse_args(argc, argv, &opt);
    if (opt.in_len == 0) {
        usage(1, opt.prog);
    }
    program p = {0};
    asm_all(&p, opt.in, opt.in_len);
    asm_link(&p);
    prog_write(&p, opt.out);
    return 0;
}
