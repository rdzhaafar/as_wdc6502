#include "asm6502.h"
#include <stdarg.h>

static int max_err = 10;
static int errs = 0;
static char *path = "<unknown>";
static int line = 1;

// Set maximum allowed number of errors
void err_set_max(int max)
{
    max_err = max;
}

int err_get_num()
{
    return errs;
}

// Set error source file location
void err_set_loc(char *p, int l)
{
    path = p;
    line = l;
}

// Check if the maximum amount of errors has been reached
static void chk()
{
    if (errs >= max_err) {
        fprintf(stderr, "maximum amount of errors reached, aborting\n");
        exit(EXIT_FAILURE);
    }
}

// Print error located at `set_err_loc(...)`
void err_at(char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "error: (%s:%d): ", path, line);
    vfprintf(stderr, fmt, va);
    fprintf(stderr, "\n");
    va_end(va);
    errs++;
    chk();
}

// Print error
void err(char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, va);
    fprintf(stderr, "\n");
    va_end(va);
    errs++;
    chk();
}
