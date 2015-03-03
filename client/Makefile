include ../Makefile

all: client.out
client.out: main.o register.o
	$(CC) $(CFLAGS) *.o $(CLIBS) -o client.out
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
register.o: register.cpp register.h
	$(CC) $(CFLAGS) -c register.cpp
clean:
	rm *.o *.out
