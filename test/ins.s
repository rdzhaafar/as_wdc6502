; List of all possible WDC65C02 instructions

    adc 0xABCD     ; AB CD 6D     a
    adc 0xABCD,x   ; AB CD 7D     a,x
    adc 0xABCD,y   ; AB CD 79     a,y
    adc #0xAB      ;    AB 69     #
    adc 0xAB       ;    AB 65     zp
    adc (0xAB,x)   ;    AB 61     (zp,x)
    adc 0xAB,x     ;    AB 75     zp,x
    adc (0xAB)     ;    AB 72     (zp)
    adc (0xAB),y   ;    AB 71     (zp),y
    and 0xABCD     ; AB CD 2D     a
    and 0xABCD,x   ; AB CD 3D     a,x
    and 0xABCD,y   ; AB CD 39     a,y
    and #0xAB      ;    AB 29     #
    and 0xAB       ;    AB 25     zp
    and (0xAB,x)   ;    AB 21     (zp,x)
    and 0xAB,x     ;    AB 35     zp,x
    and (0xAB)     ;    AB 32     (zp)
    and (0xAB),y   ;    AB 31     (zp),y
    asl 0xABCD     ; AB CD 0E     a
    asl 0xABCD,x   ; AB CD 1E     a,x
    asl            ;       0A     A
    asl 0xAB       ;    AB 06     zp
    asl 0xAB,x     ;    AB 16     zp,x
    bbr0 0xAB      ;    AB 0F     r
    bbr1 0xAB      ;    AB 1F     r
    bbr2 0xAB      ;    AB 2F     r
    bbr3 0xAB      ;    AB 3F     r
    bbr4 0xAB      ;    AB 4F     r
    bbr5 0xAB      ;    AB 5F     r
    bbr6 0xAB      ;    AB 6F     r
    bbr7 0xAB      ;    AB 7F     r
    bbs0 0xAB      ;    AB 8F     r
    bbs1 0xAB      ;    AB 9F     r
    bbs2 0xAB      ;    AB AF     r
    bbs3 0xAB      ;    AB BF     r
    bbs4 0xAB      ;    AB CF     r
    bbs5 0xAB      ;    AB DF     r
    bbs6 0xAB      ;    AB EF     r
    bbs7 0xAB      ;    AB FF     r
    bcc 0xAB       ;    AB 90     r
    bcs 0xAB       ;    AB B0     r
    beq 0xAB       ;    AB F0     r
    bit 0xABCD     ; AB CD 2C     a
    bit 0xABCD,x   ; AB CD 3C     a,x
    bit #0xAB      ;    AB 89     #
    bit 0xAB       ;    AB 24     zp
    bit 0xAB,x     ;    AB 34     zp,x
    bmi 0xAB       ;    AB 30     r
    bne 0xAB       ;    AB D0     r
    bpl 0xAB       ;    AB 10     r
    bra 0xAB       ;    AB 80     r
    brk            ;       00     s
    bvc 0xAB       ;    AB 50     r
    bvs 0xAB       ;    AB 70     r
    clc            ;       18     i
    cld            ;       D8     i
    cli            ;       58     i
    clv            ;       B8     i
    cmp 0xABCD     ; AB CD CD     a
    cmp 0xABCD,x   ; AB CD DD     a,x
    cmp 0xABCD,y   ; AB CD D9     a,y
    cmp #0xAB      ;    AB C9     #
    cmp 0xAB       ;    AB C5     zp
    cmp (0xAB,x)   ;    AB C1     (zp,x)
    cmp 0xAB,x     ;    AB D5     zp,x
    cmp (0xAB)     ;    AB D2     (zp)
    cmp (0xAB),y   ;    AB D1     (zp),y
    cpx 0xABCD     ; AB CD EC     a
    cpx #0xAB      ;    AB E0     #
    cpx 0xAB       ;    AB E4     zp
    cpy 0xABCD     ; AB CD CC     a
    cpy #0xAB      ;    AB C0     #
    cpy 0xAB       ;    AB C4     zp
    dec 0xABCD     ; AB CD CE     a
    dec 0xABCD,x   ; AB CD DE     a,x
    dec            ;       3A     A
    dec 0xAB       ;    AB C6     zp
    dec 0xAB,x     ;    AB D6     zp,x
    dex            ;       CA     i
    dey            ;       88     i
    eor 0xABCD     ; AB CD 4D     a
    eor 0xABCD,x   ; AB CD 5D     a,x
    eor 0xABCD,y   ; AB CD 59     a,y
    eor #0xAB      ;    AB 49     #
    eor 0xAB       ;    AB 45     zp
    eor (0xAB,x)   ;    AB 41     (zp,x)
    eor 0xAB,x     ;    AB 55     zp,x
    eor (0xAB)     ;    AB 52     (zp)
    eor (0xAB),y   ;    AB 51     (zp),y
    inc 0xABCD     ; AB CD EE     a
    inc 0xABCD,x   ; AB CD FE     a,x
    inc            ;       1A     A
    inc 0xAB       ;    AB E6     zp
    inc 0xAB,x     ;    AB F6     zp,x
    inx            ;       E8     i
    iny            ;       C8     i
    jmp 0xABCD     ; AB CD 4C     a
    jmp (0xABCD,x) ; AB CD 7C     (a,x)
    jmp (0xABCD)   ; AB CD 6C     (a)
    jsr 0xABCD     ; AB CD 20     a
    lda 0xABCD     ; AB CD AD     a
    lda 0xABCD,x   ; AB CD BD     a,x
    lda 0xABCD,y   ; AB CD B9     a,y
    lda #0xAB      ;    AB A9     #
    lda 0xAB       ;    AB A5     zp
    lda (0xAB,x)   ;    AB A1     (zp,x)
    lda 0xAB,x     ;    AB B5     zp,x
    lda (0xAB)     ;    AB B2     (zp)
    lda (0xAB),y   ;    AB B1     (zp),y
    ldx 0xABCD     ; AB CD AE     a
    ldx 0xABCD,y   ; AB CD BE     a,y
    ldx #0xAB      ;    AB A2     #
    ldx 0xAB       ;    AB A6     zp
    ldx 0xAB,y     ;    AB B6     zp,y
    ldy 0xABCD     ; AB CD AC     a
    ldy 0xABCD,x   ; AB CD BC     a,x
    ldy #0xAB      ;    AB A0     #
    ldy 0xAB       ;    AB A4     zp
    ldy 0xAB,x     ;    AB B4     zp,x
    lsr 0xABCD     ; AB CD 4E     a
    lsr 0xABCD,x   ; AB CD 5E     a,x
    lsr            ;       4A     A
    lsr 0xAB       ;    AB 46     zp
    lsr 0xAB,x     ;    AB 56     zp,x
    nop            ;       EA     i
    ora 0xABCD     ; AB CD 0D     a
    ora 0xABCD,x   ; AB CD 1D     a,x
    ora 0xABCD,y   ; AB CD 19     a,y
    ora #0xAB      ;    AB 09     #
    ora 0xAB       ;    AB 05     zp
    ora (0xAB,x)   ;    AB 01     (zp,x)
    ora 0xAB,x     ;    AB 15     zp,x
    ora (0xAB)     ;    AB 12     (zp)
    ora (0xAB),y   ;    AB 11     (zp),y
    pha            ;       48     s
    php            ;       08     s
    phx            ;       DA     s
    phy            ;       5A     s
    pla            ;       68     s
    plp            ;       28     s
    plx            ;       FA     s
    ply            ;       7A     s
    rmb0 0xAB      ;    AB 07     zp
    rmb1 0xAB      ;    AB 17     zp
    rmb2 0xAB      ;    AB 27     zp
    rmb3 0xAB      ;    AB 37     zp
    rmb4 0xAB      ;    AB 47     zp
    rmb5 0xAB      ;    AB 57     zp
    rmb6 0xAB      ;    AB 67     zp
    rmb7 0xAB      ;    AB 77     zp
    rol 0xABCD     ; AB CD 2E     a
    rol 0xABCD,x   ; AB CD 3E     a,x
    rol            ;       2A     A
    rol 0xAB       ;    AB 26     zp
    rol 0xAB,x     ;    AB 36     zp,x
    ror 0xABCD     ; AB CD 6E     a
    ror 0xABCD,x   ; AB CD 7E     a,x
    ror            ;       6A     A
    ror 0xAB       ;    AB 66     zp
    ror 0xAB,x     ;    AB 76     zp,x
    rti            ;       40     s
    rts            ;       60     s
    sbc 0xABCD     ; AB CD ED     a
    sbc 0xABCD,x   ; AB CD FD     a,x
    sbc 0xABCD,y   ; AB CD F9     a,y
    sbc #0xAB      ;    AB E9     #
    sbc 0xAB       ;    AB E5     zp
    sbc (0xAB,x)   ;    AB E1     (zp,x)
    sbc 0xAB,x     ;    AB F5     zp,x
    sbc (0xAB)     ;    AB F2     (zp)
    sbc (0xAB),y   ;    AB F1     (zp),y
    sec            ;       38     i
    smb0 0xAB      ;    AB 87     zp
    smb1 0xAB      ;    AB 97     zp
    smb2 0xAB      ;    AB A7     zp
    smb3 0xAB      ;    AB B7     zp
    smb4 0xAB      ;    AB C7     zp
    smb5 0xAB      ;    AB D7     zp
    smb6 0xAB      ;    AB E7     zp
    smb7 0xAB      ;    AB F7     zp
    sta 0xABCD     ; AB CD 8D     a
    sta 0xABCD,x   ; AB CD 9D     a,x
    sta 0xABCD,y   ; AB CD 99     a,y
    sta 0xAB       ;    AB 85     zp
    sta (0xAB,x)   ;    AB 81     (zp,x)
    sta 0xAB,x     ;    AB 95     zp,x
    sta (0xAB)     ;    AB 92     (zp)
    sta (0xAB),y   ;    AB 91     (zp),y
    stp            ;       DB     i
    stx 0xABCD     ; AB CD 8E     a
    stx 0xAB       ;    AB 86     zp
    stx 0xAB,y     ;    AB 96     zp,y
    sty 0xABCD     ; AB CD 8C     a
    sty 0xAB       ;    AB 84     zp
    sty 0xAB,x     ;    AB 94     zp,x
    stz 0xABCD     ; AB CD 9C     a
    stz 0xABCD,x   ; AB CD 9E     a,x
    stz 0xAB       ;    AB 64     zp
    stz 0xAB,x     ;    AB 74     zp,x
    tax            ;       AA     i
    tay            ;       A8     i
    trb 0xABCD     ; AB CD 1C     a
    trb 0xAB       ;    AB 14     zp
    tsb 0xABCD     ; AB CD 0C     a
    tsb 0xAB       ;    AB 04     zp
    tsx            ;       BA     i
    txa            ;       8A     i
    txs            ;       9A     i
    tya            ;       98     i
    wai            ;       CB     i