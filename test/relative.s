; Relative relocations test

.org 0
    bbr0 jump_here
.org 127
jump_here:
    stp

.org 256
    bbr0 jump_there
.org 128
jump_there:
    stp