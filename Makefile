CC = clang
CFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm
NAME = game
SRC = $(wildcard src/*.c) 
HED = $(wildcard inc/*.h)

all: $(NAME)

$(NAME): $(HED) $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) 

uninstall:
	rm -f $(NAME)

clean:

reinstall: uninstall all

