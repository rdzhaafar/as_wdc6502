#include "asm6502.h"

void prog_init(program *p)
{
    p->pc = 0;
    p->relocs = calloc(sizeof(relocation), 16);
    p->relocs_cap = 16;
    p->relocs_len = 0;
    p->syms = calloc(sizeof(symbol), 16);
    p->syms_cap = 16;
    p->syms_len = 0;
}

void prog_add_byte(program *p, unsigned char b)
{
    if (p->pc > WORD_MAX) {
        err_at("program too large");
        return;
    }
    p->data[p->pc] = b;
    p->pc++;
}

void prog_add_reloc(program *p, char *need, bool isabs, char *path, int line)
{
    if (p->relocs_len == p->relocs_cap) {
        int cap = p->relocs_cap * 2;
        p->relocs = realloc(p->relocs, cap);
        p->relocs_cap = cap;
    }
    int i = p->relocs_len;
    p->relocs[i].path = path;
    p->relocs[i].line = line;
    p->relocs[i].need = need;
    p->relocs[i].pc = p->pc;
    p->relocs[i].isabs = isabs;
    p->relocs_len++;
}

void prog_add_sym(program *p, char *name, long long val, bool lab)
{
    long long _;
    if (prog_get_sym(p, name, lab, &_)) {
        err_at("%s is already defined", name);
        return;
    }
    if (p->syms_len == p->syms_cap) {
        int cap = p->syms_cap * 2;
        p->syms = realloc(p->syms, cap);
        p->syms_cap = cap;
    }
    int i = p->syms_len;
    p->syms[i].name = name;
    p->syms[i].islab = lab;
    p->syms[i].val = val;
    p->syms_len++;
}

bool prog_get_sym(program *p, char *name, bool lab, long long *val)
{
    for (int i = 0; i < p->syms_len; i++) {
        symbol s = p->syms[i];
        if (!strcmp(name, s.name) && s.islab == lab) {
            *val = s.val;
            return true;
        }
    }
    return false;
}

void prog_write(program *p, char *path)
{
    int errs = err_total();
    if (errs) {
        err_die("%d errors total, refusing to write output", errs);
    }
    FILE *out = fopen(path, "w");
    if (!out) {
        err_die("can't open %s", path);
    }
    fwrite(p->data, WORD_MAX, 1, out);
    fclose(out);
}
