CC=clang
CFLAGS=-Wall -Wextra -std=c99 -pedantic-errors
BIN=as_wdc6502
OBJS=asm.o dir.o err.o instr.o main.o prog.o scan.o

.PHONY: all, clean
all: $(BIN)

clean:
	rm -rf $(OBJS) $(BIN)

asm.o: asm.c
	$(CC) $(CFLAGS) -c -o $@ $?

dir.o: dir.c
	$(CC) $(CFLAGS) -c -o $@ $?

err.o: err.c
	$(CC) $(CFLAGS) -c -o $@ $?

instr.o: instr.c
	$(CC) $(CFLAGS) -c -o $@ $?

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $?

prog.o: prog.c
	$(CC) $(CFLAGS) -c -o $@ $?

scan.o: scan.c
	$(CC) $(CFLAGS) -c -o $@ $?

$(BIN): $(OBJS)
	$(CC) -o $@ $^
