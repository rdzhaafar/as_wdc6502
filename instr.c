#include "asm6502.h"
#include <ctype.h>

typedef enum {
    AM_ABS_I = 0,
    AM_ABSII_I,
    AM_ABSX_I,
    AM_ABSY_I,
    AM_ABSI_I,
    AM_ACC_I,
    AM_IMM_I,
    AM_IMPL_I,
    AM_PCR_I,
    AM_STK_I,
    AM_ZP_I,
    AM_ZPII_I,
    AM_ZPX_I,
    AM_ZPY_I,
    AM_ZPI_I,
    AM_ZPIIY_I,
} opcode_i;

typedef enum {
    AM_ABS   = 1 << AM_ABS_I,   // a       Absolute
    AM_ABSII = 1 << AM_ABSII_I, // (a,x)   Absolute indexed indirect
    AM_ABSX  = 1 << AM_ABSX_I,  // a,x     Absolute indexed with X
    AM_ABSY  = 1 << AM_ABSY_I,  // a,y     Absolute indexed with Y
    AM_ABSI  = 1 << AM_ABSI_I,  // (a)     Absolute indirect
    AM_ACC   = 1 << AM_ACC_I,   // A       Accumulator
    AM_IMM   = 1 << AM_IMM_I,   // #       Immediate
    AM_IMPL  = 1 << AM_IMPL_I,  // i       Implied
    AM_PCR   = 1 << AM_PCR_I,   // r       Program counter relative
    AM_STK   = 1 << AM_STK_I,   // s       Stack
    AM_ZP    = 1 << AM_ZP_I,    // zp      Zero page
    AM_ZPII  = 1 << AM_ZPII_I,  // (zp,x)  Zero page indexed indirect
    AM_ZPX   = 1 << AM_ZPX_I,   // zp,x    Zero page indexed with X
    AM_ZPY   = 1 << AM_ZPY_I,   // zp,y    Zero page indexed with Y
    AM_ZPI   = 1 << AM_ZPI_I,   // (zp)    Zero page indirect
    AM_ZPIIY = 1 << AM_ZPIIY_I, // (zp),y  Zero page indirect indexed with Y
} addressing_mode;

typedef struct {
    char *mnem;
    unsigned char opcode[16];
    addressing_mode am;
} instruction;

// Instruction table
static instruction instrs[] = {
    {"adc", {[AM_ABS_I]=0x6D, [AM_ABSX_I]=0x7D, [AM_ABSY_I]=0x79, [AM_IMM_I]=0x69, [AM_ZP_I]=0x65, [AM_ZPII_I]=0x61, [AM_ZPX_I]=0x75, [AM_ZPI_I]=0x72, [AM_ZPIIY_I]=0x71}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"and", {[AM_ABS_I]=0x2D, [AM_ABSX_I]=0x3D, [AM_ABSY_I]=0x39, [AM_IMM_I]=0x29, [AM_ZP_I]=0x25, [AM_ZPII_I]=0x21, [AM_ZPX_I]=0x35, [AM_ZPI_I]=0x32, [AM_ZPIIY_I]=0x31}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"asl", {[AM_ABS_I]=0x0E, [AM_ABSX_I]=0x1E, [AM_ACC_I]=0x0A, [AM_ZP_I]=0x06, [AM_ZPX_I]=0x16}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
    {"bbr0", {[AM_PCR_I]=0x0F}, AM_PCR},
    {"bbr1", {[AM_PCR_I]=0x1F}, AM_PCR},
    {"bbr2", {[AM_PCR_I]=0x2F}, AM_PCR},
    {"bbr3", {[AM_PCR_I]=0x3F}, AM_PCR},
    {"bbr4", {[AM_PCR_I]=0x4F}, AM_PCR},
    {"bbr5", {[AM_PCR_I]=0x5F}, AM_PCR},
    {"bbr6", {[AM_PCR_I]=0x6F}, AM_PCR},
    {"bbr7", {[AM_PCR_I]=0x7F}, AM_PCR},
    {"bbs0", {[AM_PCR_I]=0x8F}, AM_PCR},
    {"bbs1", {[AM_PCR_I]=0x9F}, AM_PCR},
    {"bbs2", {[AM_PCR_I]=0xAF}, AM_PCR},
    {"bbs3", {[AM_PCR_I]=0xBF}, AM_PCR},
    {"bbs4", {[AM_PCR_I]=0xCF}, AM_PCR},
    {"bbs5", {[AM_PCR_I]=0xDF}, AM_PCR},
    {"bbs6", {[AM_PCR_I]=0xEF}, AM_PCR},
    {"bbs7", {[AM_PCR_I]=0xFF}, AM_PCR},
    {"bcc", {[AM_PCR_I]=0x90}, AM_PCR},
    {"bcs", {[AM_PCR_I]=0xB0}, AM_PCR},
    {"beq", {[AM_PCR_I]=0xF0}, AM_PCR},
    {"bit", {[AM_ABS_I]=0x2C, [AM_ABSX_I]=0x3C, [AM_IMM_I]=0x89, [AM_ZP_I]=0x24, [AM_ZPX_I]=0x34}, AM_ABS | AM_ABSX | AM_IMM | AM_ZP | AM_ZPX},
    {"bmi", {[AM_PCR_I]=0x30}, AM_PCR},
    {"bne", {[AM_PCR_I]=0xD0}, AM_PCR},
    {"bpl", {[AM_PCR_I]=0x10}, AM_PCR},
    {"bra", {[AM_PCR_I]=0x80}, AM_PCR},
    {"brk", {[AM_PCR_I]=0x00}, AM_STK},
    {"bvc", {[AM_PCR_I]=0x50}, AM_PCR},
    {"bvs", {[AM_PCR_I]=0x70}, AM_PCR},
    {"clc", {[AM_IMPL_I]=0x18}, AM_IMPL},
    {"cld", {[AM_IMPL_I]=0xD8}, AM_IMPL},
    {"cli", {[AM_IMPL_I]=0x58}, AM_IMPL},
    {"clv", {[AM_IMPL_I]=0xB8}, AM_IMPL},
    {"cmp", {[AM_ABS_I]=0xCD, [AM_ABSX_I]=0xDD, [AM_ABSY_I]=0xD9, [AM_IMM_I]=0xC9, [AM_ZP_I]=0xC5, [AM_ZPII_I]=0xC1, [AM_ZPX_I]=0xD5, [AM_ZPI_I]=0xD2, [AM_ZPIIY_I]=0xD1}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"cpx", {[AM_ABS_I]=0xEC, [AM_IMM_I]=0xE0, [AM_ZP_I]=0xE4}, AM_ABS | AM_IMM | AM_ZP},
    {"cpy", {[AM_ABS_I]=0xCC, [AM_IMM_I]=0xC0, [AM_ZP_I]=0xC4}, AM_ABS | AM_IMM | AM_ZP},
    {"dec", {[AM_ABS_I]=0xCE, [AM_ABSX_I]=0xDE, [AM_ACC_I]=0x3A, [AM_ZP_I]=0xC6, [AM_ZPX_I]=0xD6}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
    {"dex", {[AM_IMPL_I]=0xCA}, AM_IMPL},
    {"dey", {[AM_IMPL_I]=0x88}, AM_IMPL},
    {"eor", {[AM_ABS_I]=0x4D, [AM_ABSX_I]=0x5D, [AM_ABSY_I]=0x59, [AM_IMM_I]=0x49, [AM_ZP_I]=0x45, [AM_ZPII_I]=0x41, [AM_ZPX_I]=0x55, [AM_ZPI_I]=0x52, [AM_ZPIIY_I]=0x51}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"inc", {[AM_ABS_I]=0xEE, [AM_ABSX_I]=0xFE, [AM_ACC_I]=0x1A, [AM_ZP_I]=0xE6, [AM_ZPX_I]=0xF6}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
    {"inx", {[AM_IMPL_I]=0xE8}, AM_IMPL},
    {"iny", {[AM_IMPL_I]=0xC8}, AM_IMPL},
    {"jmp", {[AM_ABS_I]=0x4C, [AM_ABSII_I]=0x7C, [AM_ABSI_I]=0x6C}, AM_ABS | AM_ABSII | AM_ABSI},
    {"jsr", {[AM_ABS_I]=0x20}, AM_ABS},
    {"lda", {[AM_ABS_I]=0xAD, [AM_ABSX_I]=0xBD, [AM_ABSY_I]=0xB9, [AM_IMM_I]=0xA9, [AM_ZP_I]=0xA5, [AM_ZPII_I]=0xA1, [AM_ZPX_I]=0xB5, [AM_ZPI_I]=0xB2, [AM_ZPIIY_I]=0xB1}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"ldx", {[AM_ABS_I]=0xAE, [AM_ABSY_I]=0xBE, [AM_IMM_I]=0xA2, [AM_ZP_I]=0xA6, [AM_ZPY_I]=0xB6}, AM_ABS | AM_ABSY | AM_IMM | AM_ZP | AM_ZPY},
    {"ldy", {[AM_ABS_I]=0xAC, [AM_ABSX_I]=0xBC, [AM_IMM_I]=0xA0, [AM_ZP_I]=0xA4, [AM_ZPX_I]=0xB4}, AM_ABS | AM_ABSX | AM_IMM | AM_ZP | AM_ZPX},
    {"lsr", {[AM_ABS_I]=0x4E, [AM_ABSX_I]=0x5E, [AM_ACC_I]=0x4A, [AM_ZP_I]=0x46, [AM_ZPX_I]=0x56}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
    {"nop", {[AM_IMPL_I]=0xEA}, AM_IMPL},
    {"ora", {[AM_ABS_I]=0x0D, [AM_ABSX_I]=0x1D, [AM_ABSY_I]=0x19, [AM_IMM_I]=0x09, [AM_ZP_I]=0x05, [AM_ZPII_I]=0x01, [AM_ZPX_I]=0x15, [AM_ZPI_I]=0x12, [AM_ZPIIY_I]=0x11}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"pha", {[AM_STK_I]=0x48}, AM_STK},
    {"php", {[AM_STK_I]=0x08}, AM_STK},
    {"phx", {[AM_STK_I]=0xDA}, AM_STK},
    {"phy", {[AM_STK_I]=0x5A}, AM_STK},
    {"pla", {[AM_STK_I]=0x68}, AM_STK},
    {"plp", {[AM_STK_I]=0x28}, AM_STK},
    {"plx", {[AM_STK_I]=0xFA}, AM_STK},
    {"ply", {[AM_STK_I]=0x7A}, AM_STK},
    {"rmb0", {[AM_ZP_I]=0x07}, AM_ZP},
    {"rmb1", {[AM_ZP_I]=0x17}, AM_ZP},
    {"rmb2", {[AM_ZP_I]=0x27}, AM_ZP},
    {"rmb3", {[AM_ZP_I]=0x37}, AM_ZP},
    {"rmb4", {[AM_ZP_I]=0x47}, AM_ZP},
    {"rmb5", {[AM_ZP_I]=0x57}, AM_ZP},
    {"rmb6", {[AM_ZP_I]=0x67}, AM_ZP},
    {"rmb7", {[AM_ZP_I]=0x77}, AM_ZP},
    {"rol", {[AM_ABS_I]=0x2E, [AM_ABSX_I]=0x3E, [AM_ACC_I]=0x2A, [AM_ZP_I]=0x26, [AM_ZPX_I]=0x36}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
    {"ror", {[AM_ABS_I]=0x6E, [AM_ABSX_I]=0x7E, [AM_ACC_I]=0x6A, [AM_ZP_I]=0x66, [AM_ZPX_I]=0x76}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
    {"rti", {[AM_STK_I]=0x40}, AM_STK},
    {"rts", {[AM_STK_I]=0x60}, AM_STK},
    {"sbc", {[AM_ABS_I]=0xED, [AM_ABSX_I]=0xFD, [AM_ABSY_I]=0xF9, [AM_IMM_I]=0xE9, [AM_ZP_I]=0xE5, [AM_ZPII_I]=0xE1, [AM_ZPX_I]=0xF5, [AM_ZPI_I]=0xF2, [AM_ZPIIY_I]=0xF1}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"sec", {[AM_IMPL_I]=0x38}, AM_IMPL},
    {"sed", {[AM_IMPL_I]=0xF8}, AM_IMPL},
    {"sei", {[AM_IMPL_I]=0x78}, AM_IMPL},
    {"smb0", {[AM_ZP_I]=0x87}, AM_ZP},
    {"smb1", {[AM_ZP_I]=0x97}, AM_ZP},
    {"smb2", {[AM_ZP_I]=0xA7}, AM_ZP},
    {"smb3", {[AM_ZP_I]=0xB7}, AM_ZP},
    {"smb4", {[AM_ZP_I]=0xC7}, AM_ZP},
    {"smb5", {[AM_ZP_I]=0xD7}, AM_ZP},
    {"smb6", {[AM_ZP_I]=0xE7}, AM_ZP},
    {"smb7", {[AM_ZP_I]=0xF7}, AM_ZP},
    {"sta", {[AM_ABS_I]=0x8D, [AM_ABSX_I]=0x9D, [AM_ABSY_I]=0x99, [AM_ZP_I]=0x85, [AM_ZPII_I]=0x81, [AM_ZPX_I]=0x95, [AM_ZPI_I]=0x92, [AM_ZPIIY_I]=0x91}, AM_ABS | AM_ABSX | AM_ABSY | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
    {"stp", {[AM_IMPL_I]=0xDB}, AM_IMPL},
    {"stx", {[AM_ABS_I]=0x8E, [AM_ZP_I]=0x86, [AM_ZPY_I]=0x96}, AM_ABS | AM_ZP | AM_ZPY},
    {"sty", {[AM_ABS_I]=0x8C, [AM_ZP_I]=0x84, [AM_ZPX_I]=0x94}, AM_ABS | AM_ZP | AM_ZPX},
    {"stz", {[AM_ABS_I]=0x9C, [AM_ABSX_I]=0x9E, [AM_ZP_I]=0x64, [AM_ZPX_I]=0x74}, AM_ABS | AM_ABSX | AM_ZP | AM_ZPX},
    {"tax", {[AM_IMPL_I]=0xAA}, AM_IMPL},
    {"tay", {[AM_IMPL_I]=0xA8}, AM_IMPL},
    {"trb", {[AM_ABS_I]=0x1C, [AM_ZP_I]=0x14}, AM_ABS | AM_ZP},
    {"tsb", {[AM_ABS_I]=0x0C, [AM_ZP_I]=0x04}, AM_ABS | AM_ZP},
    {"tsx", {[AM_IMPL_I]=0xBA}, AM_IMPL},
    {"txa", {[AM_IMPL_I]=0x8A}, AM_IMPL},
    {"txs", {[AM_IMPL_I]=0x9A}, AM_IMPL},
    {"tya", {[AM_IMPL_I]=0x98}, AM_IMPL},
    {"wai", {[AM_IMPL_I]=0xCB}, AM_IMPL},
};

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

int instr_get(char *mnem)
{
    size_t len = sizeof(instrs) / sizeof(instruction);
    for (size_t i = 0; i < len; i++) {
        if (!strcicmp(instrs[i].mnem, mnem)) {
            return i;
        }
    }
    return NONE;
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

void instr_asm(program *p, scanner *s, int instr)
{
    err_set_loc(s->path, s->line);
    instruction *i = &instrs[instr];

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
