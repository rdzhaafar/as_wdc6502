/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf --output-file=instr_lookup.c instr.gperf  */
/* Computed positions: -k'1-4' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 2 "instr.gperf"

#include "asm6502.h"
#include "instr.h"

#define TOTAL_KEYWORDS 98
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 4
#define MIN_HASH_VALUE 13
#define MAX_HASH_VALUE 238
/* maximum key range = 226, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (register const char *str, register size_t len)
{
  static const unsigned char asso_values[] =
    {
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239,  35,  30,
       25,  20,  15,  10,   5,   0, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239,   2,  20,   5,
       10, 105,  10, 239, 239,  75,  82,  20,  25,  50,
       57,  70,  15,   2,  50,   0,  25,  12,  70,  97,
       90,  30,   7, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239, 239, 239, 239,
      239, 239, 239, 239, 239, 239, 239
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]+1];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

const struct instruction *
instr_get_intern (register const char *str, register size_t len)
{
  static const struct instruction wordlist[] =
    {
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0},
#line 86 "instr.gperf"
      {"sbc", {[AM_ABS_I]=0xED, [AM_ABSX_I]=0xFD, [AM_ABSY_I]=0xF9, [AM_IMM_I]=0xE9, [AM_ZP_I]=0xE5, [AM_ZPII_I]=0xE1, [AM_ZPX_I]=0xF5, [AM_ZPI_I]=0xF2, [AM_ZPIIY_I]=0xF1}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
      {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 98 "instr.gperf"
      {"sta", {[AM_ABS_I]=0x8D, [AM_ABSX_I]=0x9D, [AM_ABSY_I]=0x99, [AM_ZP_I]=0x85, [AM_ZPII_I]=0x81, [AM_ZPX_I]=0x95, [AM_ZPI_I]=0x92, [AM_ZPIIY_I]=0x91}, AM_ABS | AM_ABSX | AM_ABSY | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
#line 87 "instr.gperf"
      {"sec", {[AM_IMPL_I]=0x38}, AM_IMPL},
      {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 102 "instr.gperf"
      {"stz", {[AM_ABS_I]=0x9C, [AM_ABSX_I]=0x9E, [AM_ZP_I]=0x64, [AM_ZPX_I]=0x74}, AM_ABS | AM_ABSX | AM_ZP | AM_ZPX},
#line 88 "instr.gperf"
      {"sed", {[AM_IMPL_I]=0xF8}, AM_IMPL},
      {"",{0},0},
#line 40 "instr.gperf"
      {"bra", {[AM_PCR_I]=0x80}, AM_PCR},
      {"",{0},0}, {"",{0},0},
#line 51 "instr.gperf"
      {"dec", {[AM_ABS_I]=0xCE, [AM_ABSX_I]=0xDE, [AM_ACC_I]=0x3A, [AM_ZP_I]=0xC6, [AM_ZPX_I]=0xD6}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
#line 32 "instr.gperf"
      {"bbs7", {[AM_PCR_I]=0xFF}, AM_PCR},
#line 99 "instr.gperf"
      {"stp", {[AM_IMPL_I]=0xDB}, AM_IMPL},
      {"",{0},0}, {"",{0},0},
#line 34 "instr.gperf"
      {"bcs", {[AM_PCR_I]=0xB0}, AM_PCR},
#line 31 "instr.gperf"
      {"bbs6", {[AM_PCR_I]=0xEF}, AM_PCR},
#line 35 "instr.gperf"
      {"beq", {[AM_PCR_I]=0xF0}, AM_PCR},
      {"",{0},0},
#line 110 "instr.gperf"
      {"tya", {[AM_IMPL_I]=0x98}, AM_IMPL},
#line 33 "instr.gperf"
      {"bcc", {[AM_PCR_I]=0x90}, AM_PCR},
#line 30 "instr.gperf"
      {"bbs5", {[AM_PCR_I]=0xDF}, AM_PCR},
#line 50 "instr.gperf"
      {"cpy", {[AM_ABS_I]=0xCC, [AM_IMM_I]=0xC0, [AM_ZP_I]=0xC4}, AM_ABS | AM_IMM | AM_ZP},
      {"",{0},0}, {"",{0},0},
#line 41 "instr.gperf"
      {"brk", {[AM_PCR_I]=0x00}, AM_STK},
#line 29 "instr.gperf"
      {"bbs4", {[AM_PCR_I]=0xCF}, AM_PCR},
#line 101 "instr.gperf"
      {"sty", {[AM_ABS_I]=0x8C, [AM_ZP_I]=0x84, [AM_ZPX_I]=0x94}, AM_ABS | AM_ZP | AM_ZPX},
      {"",{0},0}, {"",{0},0},
#line 105 "instr.gperf"
      {"trb", {[AM_ABS_I]=0x1C, [AM_ZP_I]=0x14}, AM_ABS | AM_ZP},
#line 28 "instr.gperf"
      {"bbs3", {[AM_PCR_I]=0xBF}, AM_PCR},
#line 39 "instr.gperf"
      {"bpl", {[AM_PCR_I]=0x10}, AM_PCR},
      {"",{0},0}, {"",{0},0},
#line 53 "instr.gperf"
      {"dey", {[AM_IMPL_I]=0x88}, AM_IMPL},
#line 27 "instr.gperf"
      {"bbs2", {[AM_PCR_I]=0xAF}, AM_PCR},
#line 16 "instr.gperf"
      {"asl", {[AM_ABS_I]=0x0E, [AM_ABSX_I]=0x1E, [AM_ACC_I]=0x0A, [AM_ZP_I]=0x06, [AM_ZPX_I]=0x16}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
      {"",{0},0}, {"",{0},0},
#line 109 "instr.gperf"
      {"txs", {[AM_IMPL_I]=0x9A}, AM_IMPL},
#line 26 "instr.gperf"
      {"bbs1", {[AM_PCR_I]=0x9F}, AM_PCR},
#line 108 "instr.gperf"
      {"txa", {[AM_IMPL_I]=0x8A}, AM_IMPL},
      {"",{0},0}, {"",{0},0},
#line 44 "instr.gperf"
      {"clc", {[AM_IMPL_I]=0x18}, AM_IMPL},
#line 25 "instr.gperf"
      {"bbs0", {[AM_PCR_I]=0x8F}, AM_PCR},
#line 85 "instr.gperf"
      {"rts", {[AM_STK_I]=0x60}, AM_STK},
      {"",{0},0}, {"",{0},0},
#line 45 "instr.gperf"
      {"cld", {[AM_IMPL_I]=0xD8}, AM_IMPL},
      {"",{0},0},
#line 70 "instr.gperf"
      {"pla", {[AM_STK_I]=0x68}, AM_STK},
      {"",{0},0}, {"",{0},0},
#line 106 "instr.gperf"
      {"tsb", {[AM_ABS_I]=0x0C, [AM_ZP_I]=0x04}, AM_ABS | AM_ZP},
      {"",{0},0},
#line 65 "instr.gperf"
      {"ora", {[AM_ABS_I]=0x0D, [AM_ABSX_I]=0x1D, [AM_ABSY_I]=0x19, [AM_IMM_I]=0x09, [AM_ZP_I]=0x05, [AM_ZPII_I]=0x01, [AM_ZPX_I]=0x15, [AM_ZPI_I]=0x12, [AM_ZPIIY_I]=0x11}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
      {"",{0},0}, {"",{0},0},
#line 104 "instr.gperf"
      {"tay", {[AM_IMPL_I]=0xA8}, AM_IMPL},
#line 24 "instr.gperf"
      {"bbr7", {[AM_PCR_I]=0x7F}, AM_PCR},
#line 48 "instr.gperf"
      {"cmp", {[AM_ABS_I]=0xCD, [AM_ABSX_I]=0xDD, [AM_ABSY_I]=0xD9, [AM_IMM_I]=0xC9, [AM_ZP_I]=0xC5, [AM_ZPII_I]=0xC1, [AM_ZPX_I]=0xD5, [AM_ZPI_I]=0xD2, [AM_ZPIIY_I]=0xD1}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
#line 97 "instr.gperf"
      {"smb7", {[AM_ZP_I]=0xF7}, AM_ZP},
      {"",{0},0},
#line 71 "instr.gperf"
      {"plp", {[AM_STK_I]=0x28}, AM_STK},
#line 23 "instr.gperf"
      {"bbr6", {[AM_PCR_I]=0x6F}, AM_PCR},
#line 15 "instr.gperf"
      {"and", {[AM_ABS_I]=0x2D, [AM_ABSX_I]=0x3D, [AM_ABSY_I]=0x39, [AM_IMM_I]=0x29, [AM_ZP_I]=0x25, [AM_ZPII_I]=0x21, [AM_ZPX_I]=0x35, [AM_ZPI_I]=0x32, [AM_ZPIIY_I]=0x31}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
#line 96 "instr.gperf"
      {"smb6", {[AM_ZP_I]=0xE7}, AM_ZP},
      {"",{0},0},
#line 89 "instr.gperf"
      {"sei", {[AM_IMPL_I]=0x78}, AM_IMPL},
#line 22 "instr.gperf"
      {"bbr5", {[AM_PCR_I]=0x5F}, AM_PCR},
#line 64 "instr.gperf"
      {"nop", {[AM_IMPL_I]=0xEA}, AM_IMPL},
#line 95 "instr.gperf"
      {"smb5", {[AM_ZP_I]=0xD7}, AM_ZP},
      {"",{0},0},
#line 82 "instr.gperf"
      {"rol", {[AM_ABS_I]=0x2E, [AM_ABSX_I]=0x3E, [AM_ACC_I]=0x2A, [AM_ZP_I]=0x26, [AM_ZPX_I]=0x36}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
#line 21 "instr.gperf"
      {"bbr4", {[AM_PCR_I]=0x4F}, AM_PCR},
#line 66 "instr.gperf"
      {"pha", {[AM_STK_I]=0x48}, AM_STK},
#line 94 "instr.gperf"
      {"smb4", {[AM_ZP_I]=0xC7}, AM_ZP},
      {"",{0},0},
#line 73 "instr.gperf"
      {"ply", {[AM_STK_I]=0x7A}, AM_STK},
#line 20 "instr.gperf"
      {"bbr3", {[AM_PCR_I]=0x3F}, AM_PCR},
#line 49 "instr.gperf"
      {"cpx", {[AM_ABS_I]=0xEC, [AM_IMM_I]=0xE0, [AM_ZP_I]=0xE4}, AM_ABS | AM_IMM | AM_ZP},
#line 93 "instr.gperf"
      {"smb3", {[AM_ZP_I]=0xB7}, AM_ZP},
      {"",{0},0},
#line 63 "instr.gperf"
      {"lsr", {[AM_ABS_I]=0x4E, [AM_ABSX_I]=0x5E, [AM_ACC_I]=0x4A, [AM_ZP_I]=0x46, [AM_ZPX_I]=0x56}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
#line 19 "instr.gperf"
      {"bbr2", {[AM_PCR_I]=0x2F}, AM_PCR},
#line 100 "instr.gperf"
      {"stx", {[AM_ABS_I]=0x8E, [AM_ZP_I]=0x86, [AM_ZPY_I]=0x96}, AM_ABS | AM_ZP | AM_ZPY},
#line 92 "instr.gperf"
      {"smb2", {[AM_ZP_I]=0xA7}, AM_ZP},
      {"",{0},0},
#line 67 "instr.gperf"
      {"php", {[AM_STK_I]=0x08}, AM_STK},
#line 18 "instr.gperf"
      {"bbr1", {[AM_PCR_I]=0x1F}, AM_PCR},
      {"",{0},0},
#line 91 "instr.gperf"
      {"smb1", {[AM_ZP_I]=0x97}, AM_ZP},
      {"",{0},0},
#line 52 "instr.gperf"
      {"dex", {[AM_IMPL_I]=0xCA}, AM_IMPL},
#line 17 "instr.gperf"
      {"bbr0", {[AM_PCR_I]=0x0F}, AM_PCR},
#line 14 "instr.gperf"
      {"adc", {[AM_ABS_I]=0x6D, [AM_ABSX_I]=0x7D, [AM_ABSY_I]=0x79, [AM_IMM_I]=0x69, [AM_ZP_I]=0x65, [AM_ZPII_I]=0x61, [AM_ZPX_I]=0x75, [AM_ZPI_I]=0x72, [AM_ZPIIY_I]=0x71}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
#line 90 "instr.gperf"
      {"smb0", {[AM_ZP_I]=0x87}, AM_ZP},
      {"",{0},0},
#line 83 "instr.gperf"
      {"ror", {[AM_ABS_I]=0x6E, [AM_ABSX_I]=0x7E, [AM_ACC_I]=0x6A, [AM_ZP_I]=0x66, [AM_ZPX_I]=0x76}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
      {"",{0},0},
#line 43 "instr.gperf"
      {"bvs", {[AM_PCR_I]=0x70}, AM_PCR},
      {"",{0},0}, {"",{0},0},
#line 69 "instr.gperf"
      {"phy", {[AM_STK_I]=0x5A}, AM_STK},
      {"",{0},0},
#line 42 "instr.gperf"
      {"bvc", {[AM_PCR_I]=0x50}, AM_PCR},
      {"",{0},0}, {"",{0},0},
#line 47 "instr.gperf"
      {"clv", {[AM_IMPL_I]=0xB8}, AM_IMPL},
      {"",{0},0},
#line 36 "instr.gperf"
      {"bit", {[AM_ABS_I]=0x2C, [AM_ABSX_I]=0x3C, [AM_IMM_I]=0x89, [AM_ZP_I]=0x24, [AM_ZPX_I]=0x34}, AM_ABS | AM_ABSX | AM_IMM | AM_ZP | AM_ZPX},
#line 81 "instr.gperf"
      {"rmb7", {[AM_ZP_I]=0x77}, AM_ZP},
      {"",{0},0},
#line 46 "instr.gperf"
      {"cli", {[AM_IMPL_I]=0x58}, AM_IMPL},
      {"",{0},0},
#line 60 "instr.gperf"
      {"lda", {[AM_ABS_I]=0xAD, [AM_ABSX_I]=0xBD, [AM_ABSY_I]=0xB9, [AM_IMM_I]=0xA9, [AM_ZP_I]=0xA5, [AM_ZPII_I]=0xA1, [AM_ZPX_I]=0xB5, [AM_ZPI_I]=0xB2, [AM_ZPIIY_I]=0xB1}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
#line 80 "instr.gperf"
      {"rmb6", {[AM_ZP_I]=0x67}, AM_ZP},
      {"",{0},0},
#line 103 "instr.gperf"
      {"tax", {[AM_IMPL_I]=0xAA}, AM_IMPL},
      {"",{0},0},
#line 84 "instr.gperf"
      {"rti", {[AM_STK_I]=0x40}, AM_STK},
#line 79 "instr.gperf"
      {"rmb5", {[AM_ZP_I]=0x57}, AM_ZP},
      {"",{0},0},
#line 107 "instr.gperf"
      {"tsx", {[AM_IMPL_I]=0xBA}, AM_IMPL},
      {"",{0},0}, {"",{0},0},
#line 78 "instr.gperf"
      {"rmb4", {[AM_ZP_I]=0x47}, AM_ZP},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 77 "instr.gperf"
      {"rmb3", {[AM_ZP_I]=0x37}, AM_ZP},
      {"",{0},0},
#line 55 "instr.gperf"
      {"inc", {[AM_ABS_I]=0xEE, [AM_ABSX_I]=0xFE, [AM_ACC_I]=0x1A, [AM_ZP_I]=0xE6, [AM_ZPX_I]=0xF6}, AM_ABS | AM_ABSX | AM_ACC | AM_ZP | AM_ZPX},
      {"",{0},0},
#line 37 "instr.gperf"
      {"bmi", {[AM_PCR_I]=0x30}, AM_PCR},
#line 76 "instr.gperf"
      {"rmb2", {[AM_ZP_I]=0x27}, AM_ZP},
#line 58 "instr.gperf"
      {"jmp", {[AM_ABS_I]=0x4C, [AM_ABSII_I]=0x7C, [AM_ABSI_I]=0x6C}, AM_ABS | AM_ABSII | AM_ABSI},
#line 72 "instr.gperf"
      {"plx", {[AM_STK_I]=0xFA}, AM_STK},
      {"",{0},0},
#line 59 "instr.gperf"
      {"jsr", {[AM_ABS_I]=0x20}, AM_ABS},
#line 75 "instr.gperf"
      {"rmb1", {[AM_ZP_I]=0x17}, AM_ZP},
      {"",{0},0},
#line 62 "instr.gperf"
      {"ldy", {[AM_ABS_I]=0xAC, [AM_ABSX_I]=0xBC, [AM_IMM_I]=0xA0, [AM_ZP_I]=0xA4, [AM_ZPX_I]=0xB4}, AM_ABS | AM_ABSX | AM_IMM | AM_ZP | AM_ZPX},
      {"",{0},0}, {"",{0},0},
#line 74 "instr.gperf"
      {"rmb0", {[AM_ZP_I]=0x07}, AM_ZP},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0},
#line 54 "instr.gperf"
      {"eor", {[AM_ABS_I]=0x4D, [AM_ABSX_I]=0x5D, [AM_ABSY_I]=0x59, [AM_IMM_I]=0x49, [AM_ZP_I]=0x45, [AM_ZPII_I]=0x41, [AM_ZPX_I]=0x55, [AM_ZPI_I]=0x52, [AM_ZPIIY_I]=0x51}, AM_ABS | AM_ABSX | AM_ABSY | AM_IMM | AM_ZP | AM_ZPII | AM_ZPX | AM_ZPI | AM_ZPIIY},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 57 "instr.gperf"
      {"iny", {[AM_IMPL_I]=0xC8}, AM_IMPL},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 68 "instr.gperf"
      {"phx", {[AM_STK_I]=0xDA}, AM_STK},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 111 "instr.gperf"
      {"wai", {[AM_IMPL_I]=0xCB}, AM_IMPL},
      {"",{0},0}, {"",{0},0},
#line 38 "instr.gperf"
      {"bne", {[AM_PCR_I]=0xD0}, AM_PCR},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
#line 61 "instr.gperf"
      {"ldx", {[AM_ABS_I]=0xAE, [AM_ABSY_I]=0xBE, [AM_IMM_I]=0xA2, [AM_ZP_I]=0xA6, [AM_ZPY_I]=0xB6}, AM_ABS | AM_ABSY | AM_IMM | AM_ZP | AM_ZPY},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0}, {"",{0},0}, {"",{0},0},
      {"",{0},0}, {"",{0},0},
#line 56 "instr.gperf"
      {"inx", {[AM_IMPL_I]=0xE8}, AM_IMPL}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].mnem;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
#line 112 "instr.gperf"

