#include "as_wdc6502.h"

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

    instruction i = instr_get(mnem);
    if (i != NULL) {
        instr_asm(p, s, i);
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

typedef enum {
    RESB_HI = 0xFFFD,
    RESB_LO = 0xFFFC,
    BRK_HI  = 0xFFFF,
    BRK_LO  = 0xFFFE,
    NMIB_HI = 0xFFFB,
    NMIB_LO = 0xFFFA,
} vectors;

void asm_link(program *p)
{
    long long addr;
    unsigned char hi, lo;
    for (int i = 0; i < p->relocs_len; i++) {
        relocation *r = &p->relocs[i];
        err_set_loc(r->path, r->line);
        if (!prog_get_sym(p, r->need, true, &addr)) {
            err_at("%s is not defined", r->need);
            continue;
        }
        if (r->isabs) {
            // Absolute relocation
            hi = (addr >> 8) & 0xFF;
            lo = addr & 0xFF;
            p->data[r->pc] = hi;
            p->data[r->pc + 1] = lo;
        } else if (r->isrel) {
            // PC-relative relocation
            char rel = addr - r->pc;
            int br = addr - r->pc;
            if (br != rel) {
                err_at("%s is out of range for relative addressing", r->need);
                continue;
            }
            // pointer magic preserves the sign bit
            p->data[r->pc] = *((unsigned char *) &rel);
        } else {
            // Zero-page offset
            if (addr > BYTE_MAX) {
                err_at("%s is out of range for zero-page addressing", r->need);
                continue;
            }
            lo = addr & 0xFF;
            p->data[r->pc] = lo;
        }
    }

    if (prog_get_sym(p, "_resb", true, &addr)) {
        lo = addr & 0xFF;
        hi = (addr >> 8) & 0xFF;
        p->data[RESB_HI] = hi;
        p->data[RESB_LO] = lo;
    }
    if (prog_get_sym(p, "_nmib", true, &addr)) {
        lo = addr & 0xFF;
        hi = (addr >> 8) & 0xFF;
        p->data[NMIB_HI] = hi;
        p->data[NMIB_LO] = lo;
    }
    if (prog_get_sym(p, "_brk", true, &addr)) {
        lo = addr & 0xFF;
        hi = (addr >> 8) & 0xFF;
        p->data[BRK_HI] = hi;
        p->data[BRK_LO] = lo;
    }
}
