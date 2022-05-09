# as_wdc6502 Documentation

## Syntax:

The grammar can be expressed in the following BNF notation.
```
source_file := line*
line := label* line_body eol
eol := newline | EOF
newline := '\n' | '\r\n'
label := ID ':'
line_body := instruction | directive
instruction := ID operand?
directive := ID directive_operands
operand :=
        | val
        | '(' val ',' 'x' ')'
        | val ',' 'x'
        | val ',' 'y'
        | '(' val ')'
        | '(' val ')' ',' 'y'
        | '#' val
val := ID | INT
```

`directive_operands` are specific to a directive and should be looked up in the
corresponding section.

Integer literals can be written as decimal `1234`, binary `0b1010`, octal
`0o171`, or hexadecimal `0xDEAD`. Prefixes and digits are case-insensitive.

Identifiers are any strings of characters that start with a `.` or `_` or
any ASCII letter followed by any number of ASCII letters, `_`'s, '.''s or
ASCII digits.

## Directives:

### .org
```
.org INT
```
Continues assembly at address specified by the integer.

### .byte
```
.byte INT
```
Inserts a 1-byte constant into the assembled program.

## Linking:

All labels are global. This means that if you are assembling any two sources
together, any label from these sources is available in both during linking.
This also means that special care must be taken to not have name labels with the
same names. Re-defining a label is an error.

There are three special labels: `_brk`, `_resb`, and `_nmib`. When defined,
these labels point to the code that should be executed when the CPU reads
`BRK/IRQB`, `RESB`, and `NMIB` vectors respectively. If any of these are not
defined, their value is set to 0.

## Output:

The output file is a simple 16-KB binary ROM image. It is only produced when no
errors were encountered during assembly.