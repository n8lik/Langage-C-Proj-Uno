CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -ansi -std=gnu11
CLIBS= -lm
EXE= executable
OBJ= main.o\
     card.o

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c card.h
card.o : card.c card.h

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf $(OBJ)
	rm -rf $(EXE)