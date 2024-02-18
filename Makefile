CC= gcc
CFLAGS= -O2 -Wall -Wextra -Werror -std=c99
CLIBS= -lm -lSDL -lSDL_ttf -lSDL_image -lSDL_gfx
EXE= executable
OBJ= obj/
FILEC:= $(wildcard *.c)
FILEH:= $(wildcard *.h)
FILEO:= $(patsubst %.c,$(OBJ)%.o,$(FILEC))

all: $(OBJ) $(EXE)

$(OBJ):
	mkdir -p $(OBJ)

$(EXE) : $(FILEO)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(OBJ)%.o : %.c $(FILEH)
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(OBJ)*.o
	rm -rf $(EXE)
