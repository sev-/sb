CC = rcc
CFLAGS =

OBJS = parse.o sb.o lex.o errors.o go.o loops.o conds.o input.o print.o vars.o

HEADERS = sb.h global.h proto.h

sb: $(OBJS)
	$(CC) -o sb $(OBJS)

clean:
	rm -f core *.[ob]

$(OBJS): $(HEADERS)
