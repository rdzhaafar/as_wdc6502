#ifndef ASM6502_H
#define ASM6502_H

// Maximum 8 and 16 bit values
#define BYTE_MAX ((int)0xFF)
#define WORD_MAX ((int)0xFFFF)
// Indicates no results
#define NONE     ((int)-1)

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// err.c
void err_set_loc(char *path, int line);
void err_set_max(int max);
void err(char *fmt, ...);
void err_at(char *fmt, ...);
#define err_die(FMT, ...) err(FMT, __VA_ARGS__); exit(EXIT_FAILURE)
#define err_die_at(FMT, ...) err_at(FMT, __VA_ARGS__); exit(EXIT_FAILURE)
int err_get_num();

// scan.c
typedef enum {
    TOK_EOF = 0,
    TOK_NEWL = (int)'\n',
    TOK_LBRACE = (int)'(',
    TOK_RBRACE = (int)')',
    TOK_COMMA = (int)',',
    TOK_COLON = (int)':',
    TOK_HASH = (int)'#',
    TOK_ID = 129,
    TOK_INT,
    TOK_STR,
} tok;

typedef struct {
    char *path;
    char *text;
    int line;

    tok tok;
    char *tok_pos;
    int tok_line;
    unsigned long long tok_num;
    char *tok_id;
} scanner;

scanner *scan_read_file(char *path);
tok scan_tok(scanner *s);
tok scan_discard_line(scanner *s);

typedef struct {
    char *path;
    int line;
    bool isabs; // Absolute addressing mode relocation
    char *need;
    int pc;
} relocation;

typedef struct {
    char *name;
    bool islab;
    long long val;
} symbol;

typedef struct {
    unsigned char data[WORD_MAX];
    int pc;
    relocation *relocs;
    int relocs_len;
    int relocs_cap;
    symbol *syms;
    int syms_len;
    int syms_cap;
} program;

// prog.c
void prog_init(program *p);
void prog_add_byte(program *p, unsigned char b);
void prog_add_reloc(program *p, char *need, bool isabs, char *fpath, int line);
void prog_add_sym(program *p, char *name, long long val, bool lab);
bool prog_get_sym(program *p, char *name, bool lab, long long *val);
void prog_write(program *p, char *path);

// instr.c
int instr_get(char *mnem);
void instr_asm(program *p, scanner *s, int instr);

// dir.c
int dir_get(char *name);
void dir_asm(program *p, scanner *s, int dir);

// asm.c
void asm_all(program *p, char **srcs, int srcs_len);
void asm_link(program *p);

#endif
