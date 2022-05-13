#include "as_wdc6502.h"

typedef struct {
    char *name;
    void (*handler)(program *, scanner *);
} directive;

static bool eol(tok t)
{
    return t == TOK_NEWL || t == TOK_EOF;
}

static bool get_num(scanner *s, unsigned long long *num)
{
    tok t = s->tok;
    if (t != TOK_INT) {
        scan_discard_line(s);
        return false;
    }
    *num = s->tok_num;
    t = scan_tok(s);
    if (!eol(t)) {
        scan_discard_line(s);
        return false;
    }
    return true;
}

static void org(program *p, scanner *s)
{
    unsigned long long org;
    if (!get_num(s, &org)) {
        err_at(".org expects an offset");
        return;
    }
    if (org > WORD_MAX) {
        err_at(".org offset too large");
        return;
    }
    p->pc = org;
}

static void byte(program *p, scanner *s)
{
    unsigned long long b;
    if (!get_num(s, &b)) {
        err_at(".byte expects a digit");
        return;
    }
    if (b > BYTE_MAX) {
        err_at(".byte digit too large");
        return;
    }
    prog_add_byte(p, b);
}

static directive dirs[] = {
    {".org", org},
    {".byte", byte},
};

int dir_get(char *name)
{
    size_t len = sizeof(dirs) / sizeof(directive);
    for (size_t i = 0; i < len; i++) {
        if (!strcmp(name, dirs[i].name)) {
            return i;
        }
    }
    return NONE;
}

void dir_asm(program *p, scanner *s, int dir)
{
    directive *d = &dirs[dir];
    err_set_loc(s->path, s->line);
    d->handler(p, s);
}
