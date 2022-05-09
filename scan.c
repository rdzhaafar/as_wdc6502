#include "asm6502.h"
#include <ctype.h>

static tok set(scanner *s, tok t)
{
    s->tok = t;
    return t;
}

static char peek(scanner *s)
{
    return *(s->text);
}

static bool eof(scanner *s)
{
    return !peek(s);
}

static void next(scanner *s)
{
    if (peek(s) == '\n') {
        s->line++;
    }
    s->text++;
}

tok scan_discard_line(scanner *s)
{
    for (;;) {
        if (eof(s)) {
            return set(s, TOK_EOF);
        }
        if (peek(s) == TOK_NEWL) {
            return set(s, TOK_NEWL);
        }
        next(s);
    }
    // XXX: Unreachable
    return TOK_EOF;
}

static bool space(scanner *s)
{
    char c = peek(s);
    return c == ' ' || c == '\t' || c == '\r';
}

static bool dec(scanner *s)
{
    char c = peek(s);
    return c >= '0' && c <= '9';
}

static bool bin(scanner *s)
{
    char c = peek(s);
    return c == '0' || c == '1';
}

static bool oct(scanner *s)
{
    char c = peek(s);
    return c >= '0' && c <= '7';
}

static bool idhead(scanner *s)
{
    char c = peek(s);
    return isalpha(c) || c == '_' || c == '.';
}

static bool idbody(scanner *s)
{
    return idhead(s) || dec(s) || peek(s) == '.';
}

static bool punct(scanner *s)
{
    char c = peek(s);
    return c == '\n' ||
        c == ',' ||
        c == '#' ||
        c == ':' ||
        c == '(' ||
        c == ')';
}

scanner *scan_read_file(char *path)
{
    FILE *in = fopen(path, "r");
    if (!in) {
        return NULL;
    }
    fseek(in, 0, SEEK_END);
    int len = ftell(in);
    fseek(in, 0, SEEK_SET);
    char *text = calloc(len + 1, 1);
    int read = 0;
    while (read < len) {
        read += fread(text + read, 1, len - read, in);
    }
    fclose(in);
    int pathl = strlen(path);
    char *pathc = calloc(pathl + 1, 1);
    strncpy(pathc, path, pathl);

    scanner *s = calloc(sizeof(scanner), 1);
    s->path = pathc;
    s->text = text;
    s->line = 1;

    return s;
}

tok scan_tok(scanner *s)
{
skip:
    s->tok_pos = s->text;
    s->tok_line = s->line;
    err_set_loc(s->path, s->line);

    if (eof(s)) {
        // EOF
        return set(s, TOK_EOF);
    } else if (space(s)) {
        // Whitespace
        while (space(s)) {
            next(s);
        }
        goto skip;
    } else if (peek(s) == ';') {
        // Line comment
        while (peek(s) != '\n' && !eof(s)) {
            next(s);
        }
        goto skip;
    } else if (idhead(s)) {
        // Identifier
        next(s);
        while (idbody(s)) {
            next(s);
        }
        int len = s->text - s->tok_pos;
        char *id = calloc(len + 1, 1);
        strncpy(id, s->tok_pos, len);
        s->tok_id = id;
        return set(s, TOK_ID);
    } else if (isdigit(peek(s))) {
        // Integer literal
        char *d = s->tok_pos;
        int base = 10;
        if (peek(s) == '0') {
            next(s);
            switch (peek(s)) {
            case 'b':
            case 'B':
                d += 2;
                base = 2;
                next(s);
                break;
            case 'o':
            case 'O':
                d += 2;
                base = 8;
                next(s);
                break;
            case 'x':
            case 'X':
                d += 2;
                base = 16;
                next(s);
                break;
            }
        }
        switch (base) {
        case 2:
            while (bin(s)) {
                next(s); 
            }
            break;
        case 8:
            while (oct(s)) {
                next(s);
            }
            break;
        case 10: 
            while (isdigit(peek(s))) {
                next(s);
            }
            break;
        case 16: 
            while (isxdigit(peek(s))) {
                next(s);
            }
            break;
        }
        if (isalnum(peek(s))) {
            while (isalnum(peek(s))) {
                next(s);
            }
            err_at("invalid digit in integer");
            return scan_discard_line(s);
        }
        char *end;
        unsigned long long n = strtoull(d, &end, base);
        if (end != s->text) {
            err_at("integer literal too large");
            return scan_discard_line(s);
        }
        s->tok_num = n;
        return set(s, TOK_INT);
    } else if (punct(s)) {
        // Punctuation character
        char p = peek(s);
        next(s);
        return set(s, (tok)p);
    } else {
        // Unknown token
        err_at("unknown character");
        return scan_discard_line(s);
    }
}
