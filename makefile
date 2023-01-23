OBJ = main.o utils.o

all: link
utils.o: utils.c
	gcc -g -c utils.c -o utils.o
main.o: main.c utils.o
	gcc -g -c main.c `pkg-config --cflags --libs gtk+-3.0` -o main.o
link: main.o utils.o
	gcc -g $(OBJ) `pkg-config --cflags --libs gtk+-3.0` -o out
clean:
	rm -f *.o
