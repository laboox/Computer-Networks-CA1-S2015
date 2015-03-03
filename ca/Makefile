include ../Makefile

all: ca.out
ca.out: main.o
	$(CC) *.o $(CLIBS) -o ca.out 
main.o: main.cpp user.o
	$(CC) $(CFLAGS) -c main.cpp
user.o: user.cpp user.h
	$(CC) $(CFLAGS) -c user.cpp
	
clean:
	rm *.o *.out
