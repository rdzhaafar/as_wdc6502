#ifndef INSTR_H
#define INSTR_H

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

struct instruction {
    char *mnem;
    unsigned char opcode[16];
    addressing_mode am;
};

const struct instruction *
instr_get_intern(register const char *str, register size_t len);

#endif
