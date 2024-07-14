CC = gcc
CFLAGS = -I./include -lyaml
OBJ = main.o config.o
DEPS = config.h

%.o: ./src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main
