CC = gcc

atm:
	${CC} -o bin/atm src/main.c src/system.c src/input.c src/auth.c

clean:
	rm -f bin/*



