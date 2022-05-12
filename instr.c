#include "asm6502.h"
#include "instr.h"
#include <ctype.h>

instruction instr_get(char *mnem)
{
    const struct instruction *i = instr_get_intern(mnem, strlen(mnem));
    return (instruction)i;
}

// Converts addressing mode bit flag to an opcode[16] index in
// `instruction`
static opcode_i am_to_opcode_i(addressing_mode am)
{
    int i = -1;
    while (am > 0) {
        am >>= 1;
        i++;
    }
    return i;
}

static int strcicmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

static bool eol(tok t)
{
    return t == TOK_NEWL || t == TOK_EOF;
}

static bool val(tok t)
{
    return t == TOK_INT || t == TOK_ID;
}

typedef struct {
    addressing_mode am;
    bool is_imm;
    unsigned long long imm;
    char *sym;
} operand;

static void set_val(scanner *s, operand *op)
{
    if (s->tok == TOK_INT) {
        op->imm = s->tok_num;
        op->is_imm = true;
    } else {
        op->sym = s->tok_id;
        op->is_imm = false;
    }
}

static bool get_op(scanner *s, operand *op)
{
    tok t = s->tok;

    if (t == TOK_HASH) {
        // '#'
        t = scan_tok(s);
        if (val(t)) {
            // '#' val
            set_val(s, op);
            t = scan_tok(s);
            if (eol(t)) {
                // '#' val eol
                op->am = AM_IMM;
                return true;
            } else {
                // '#' val ?
                scan_discard_line(s);
                return false;
            }
        } else {
            // '#' ?
            scan_discard_line(s);
            return false;
        }
    } else if (val(t)) {
        // val
        set_val(s, op);
        t = scan_tok(s);
        if (eol(t)) {
            // val eol
            op->am = AM_ABS | AM_ZP | AM_PCR;
            return true;
        } else if (t == TOK_COMMA) {
            // val ','
            t = scan_tok(s);
            if (t == TOK_ID && !strcicmp(s->tok_id, "x")) {
                // val ',' 'x'
                t = scan_tok(s);
                if (eol(t)) {
                    // val ',' 'x' eol
                    op->am = AM_ABSX | AM_ZPX;
                    return true;
                } else {
                    // val ',' 'x' ?
                    scan_discard_line(s);
                    return false;
                }
            } else if (t == TOK_ID && !strcicmp(s->tok_id, "y")) {
                // val ',' 'y'
                t = scan_tok(s);
                if (eol(t)) {
                    // val ',' 'y' eol
                    op->am = AM_ABSY | AM_ZPY;
                    return true;
                } else {
                    // val ',' 'y' ?
                    scan_discard_line(s);
                    return false;
                }
            } else { 
                // val ',' ?
                scan_discard_line(s);
                return false;
            }
        } else {
            // val ?
            scan_discard_line(s);
            return false;
        }
    } else if (t == TOK_LBRACE) {
        // '('
        t = scan_tok(s);
        if (val(t)) {
            // '(' val
            set_val(s, op);
            t = scan_tok(s);
            if (t == TOK_RBRACE) {
                // '(' val ')'
                t = scan_tok(s);
                if (eol(t)) {
                    // '(' val ')' eol
                    op->am = AM_ABSI | AM_ZPI;
                    return true;
                } else if (t == TOK_COMMA) {
                    // '(' val ')' ','
                    t = scan_tok(s);
                    if (t == TOK_ID && !strcicmp(s->tok_id, "y")) {
                        // '(' val ')' ',' 'y'
                        t = scan_tok(s);
                        if (eol(t)) {
                            // '(' val ')' ',' 'y' eol
                            op->am = AM_ZPIIY;
                            return true;
                        } else {
                            // '(' val ')' ',' 'y' ?
                            scan_discard_line(s);
                            return false;
                        }
                    } else {
                        // '(' val ')' ',' ?
                        scan_discard_line(s);
                        return false;
                    }
                } else {
                    // '(' val ')' ',' ?
                    scan_discard_line(s);
                    return false;
                }
            } else if (t == TOK_COMMA) {
                // '(' val ','
                t = scan_tok(s);
                if (t == TOK_ID && !strcicmp(s->tok_id, "x")) {
                    // '(' val ',' 'x'
                    t = scan_tok(s);
                    if (t == TOK_RBRACE) {
                        // '(' val ',' 'x' ')'
                        t = scan_tok(s);
                        if (eol(t)) {
                            // '(' val ',' 'x' ')' eol
                            op->am = AM_ABSII | AM_ZPII;
                            return true;
                        } else {
                            // '(' val ',' 'x' ')' ?
                            scan_discard_line(s);
                            return false;
                        }
                    } else {
                        // '(' val ',' 'x' ?
                        scan_discard_line(s);
                        return false;
                    }
                } else {
                    // '(' val ',' ?
                    scan_discard_line(s);
                    return false;
                }
            } else {
                // '(' val ?
                scan_discard_line(s);
                return false;
            }
        } else {
            // '(' ?
            scan_discard_line(s);
            return false;
        }
    } else if (eol(t)) {
        // eol
        op->am = AM_IMPL | AM_STK | AM_ACC;
        return true;
    } else {
        // ?
        scan_discard_line(s);
        return false;
    }
}

// Disambiguates any scenarios where an instruction can use both zero-page
// and absolute addressing.
// - If the operand is not immediate (relocatable symbol), use absolute
//   addressing
// - If the operand is immediate and smaller than 0xFF, use zero-page addressing
// - If the operand is immediate and larger than 0xFF, use absolute addressing
static void disambiguate(operand *op)
{
    if (op->am & (AM_ABS | AM_ZP)) {
        // AM_ABS | AM_ZP
        if (!op->is_imm || op->imm > BYTE_MAX) {
            op->am &= ~AM_ZP;
        } else {
            op->am &= ~AM_ABS;
        }
    }
    if (op->am & (AM_ABSII | AM_ZPII)) {
        // AM_ABSII | AM_ZPII
        if (!op->is_imm || op->imm > BYTE_MAX) {
            op->am &= ~AM_ZPII;
        } else {
            op->am &= ~AM_ABSII;
        }
    }
    if (op->am & (AM_ABSX | AM_ZPX)) {
        // AM_ABSX | AM_ZPX
        if (!op->is_imm || op->imm > BYTE_MAX) {
            op->am &= ~AM_ZPX;
        } else {
            op->am &= ~AM_ABSX;
        }
    }
    if (op->am & (AM_ABSY | AM_ZPY)) {
        if (!op->is_imm || op->imm > BYTE_MAX) {
            op->am &= ~AM_ZPY;
        } else {
            op->am &= ~AM_ABSY;
        }
    }
    if (op->am & (AM_ABSI | AM_ZPI)) {
        if (!op->is_imm || op->imm > BYTE_MAX) {
            op->am &= ~AM_ZPI;
        } else {
            op->am &= ~AM_ABSI;
        }
    }
}

void instr_asm(program *p, scanner *s, instruction ptr)
{
    struct instruction *i = (struct instruction *)ptr;
    err_set_loc(s->path, s->line);

    operand op = {0};
    if (!get_op(s, &op)) {
        err_at("incorrect operands for %s", i->mnem);
        return;
    }

    // Find possible addressing modes
    disambiguate(&op);
    int i_am = i->am & op.am;
    if (!i_am) {
        err_at("incorrect addressing mode for %s", i->mnem);
        return;
    }

    // Get opcode index from the addressing mode
    int am_i = am_to_opcode_i(i_am); 
    unsigned char opc = i->opcode[am_i];

    switch (i_am) {
    unsigned char lo, hi;

    case AM_ABS:
    case AM_ABSII:
    case AM_ABSX:
    case AM_ABSY:
    case AM_ABSI:
        if (op.is_imm && op.imm > WORD_MAX) {
            err("address too large");
            break;
        }
        if (op.is_imm) {
            lo = op.imm & 0xFF;
            hi = (op.imm >> 8) & 0xFF;
            prog_add_byte(p, hi);
            prog_add_byte(p, lo);
        } else {
            // Absolute relocation
            prog_add_reloc(p, op.sym, true, false, s->path, s->line);
            prog_add_byte(p, 0);
            prog_add_byte(p, 0);
        }
        prog_add_byte(p, opc);
        break;

    case AM_IMPL:
    case AM_STK:
    case AM_ACC:
        prog_add_byte(p, opc);
        break;

    case AM_IMM:
    case AM_PCR:
    case AM_ZP:
    case AM_ZPII:
    case AM_ZPX:
    case AM_ZPY:
    case AM_ZPI:
    case AM_ZPIIY:
        if (op.is_imm && op.imm > BYTE_MAX) {
            char *what;
            if (i_am == AM_IMM) {
                what = "immediate";
            } else {
                what = "pc offset";
            }
            // Zero-page address cannot be too large, since AM_ZP... is removed
            // in `disambiguate()` in case immediate is greater than BYTE_MAX
            err_at("%s too large", what);
            break;
        }
        if (op.is_imm) {
            prog_add_byte(p, (unsigned char)op.imm);
        } else {
            if (i_am == AM_PCR) {
                // PC-relative relocation
                prog_add_reloc(p, op.sym, false, true, s->path, s->line);
            } else {
                // Zero-page relocation
                prog_add_reloc(p, op.sym, false, false, s->path, s->line);
            }
            prog_add_byte(p, 0);
        }
        prog_add_byte(p, opc);
        break;
    }
}
