; 0000: 00 0a 20 00 0b 20 00 0c 20 00 00 00 00 00 00 00
; *
; fff0: 00 00 00 00 00 00 00 00 00 00 0c 00 0b 00 0a

    .org 0xA
_brk:
    .org 0xB
_resb:
    .org 0xC
_nmib:
    .org 0
    jsr _brk
    jsr _resb
    jsr _nmib