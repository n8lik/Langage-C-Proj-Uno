CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -ansi
CLIBS= -lm
EXE= executable
OBJ= main.o\
     arraylist.o\
     hashmap.o

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

main.o : main.c player.h card.h
card.o : arraylist.c arraylist.h
player.o : hashmap.c hashmap.h 

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf $(OBJ)
	rm -rf $(EXE)