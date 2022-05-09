#include "asm6502.h"

static void asm_src(program *p, scanner *s)
{
    tok t;
next:
    t = scan_tok(s);
    if (t == TOK_NEWL) {
        goto next;
    }
    if (t == TOK_EOF) {
        return;
    }
    err_set_loc(s->path, s->tok_line);

    if (t != TOK_ID) {
        err_at("expected an instruction, directive or label");
        scan_discard_line(s);
        goto next;
    }
    char *mnem = s->tok_id;
    t = scan_tok(s);
    if (t == TOK_COLON) {
        prog_add_sym(p, mnem, p->pc, true);
        goto next;
    }

    int instr = instr_get(mnem);
    if (instr != NONE) {
        instr_asm(p, s, instr);
        goto next;
    }
    int dir = dir_get(mnem);
    if (dir != NONE) {
        dir_asm(p, s, dir);
        goto next;
    }
    err_at("unknown instruction or directive %s", mnem);
    scan_discard_line(s);
    goto next;
}

void asm_all(program *p, char **srcs, int srcs_len)
{
    prog_init(p);
    for (int i = 0; i < srcs_len; i++) {
        char *src = srcs[i];
        scanner *s = scan_read_file(src);
        if (!s) {
            err("can't open file %s", src);
        } else {
            asm_src(p, s);
        }
    }
}

// 65C02 vectors
#define RESB_LO ((unsigned char)0xFFFD)
#define RESB_HI ((unsigned char)0xFFFC)
#define BRK_HI  ((unsigned char)0xFFFF)
#define BRK_LO  ((unsigned char)0xFFFE)
#define NMIB_HI ((unsigned char)0xFFFB)
#define NMIB_LO ((unsigned char)0xFFFA)

void asm_link(program *p)
{
    for (int i = 0; i < p->relocs_len; i++) {
        relocation r = p->relocs[i];
        err_set_loc(r.path, r.line);
        long long addr;
        if (!prog_get_sym(p, r.need, true, &addr)) {
            err_at("label %s is not defined", r.need);
            continue;
        }
        if (!r.isabs && addr > BYTE_MAX) {
            err_at("label %s is larger than 0xFF (%d)", r.need, addr);
            continue;
        }
        unsigned char hi, lo;
        hi = (addr >> 8) & 0xFF;
        lo = addr & 0xFF;
        if (r.isabs) {
            p->data[r.pc] = hi;
            p->data[r.pc + 1] = lo;
        } else {
            p->data[r.pc] = lo;
        }
    }
}
