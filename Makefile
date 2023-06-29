CC = gcc

atm:
	${CC} -o bin/atm src/main.c src/system.c src/data.c src/input.c src/auth.c obj/sqlite3.o

clean:
	rm -f bin/*



