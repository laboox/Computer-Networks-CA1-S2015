include ../Makefile

all: ca.out
ca.out: main.o
	$(CC) *.o $(CLIBS) -o ca.out 
main.o: main.cpp server.o
	$(CC) $(CFLAGS) -c main.cpp
server.o: server.cpp server.h
	$(CC) $(CFLAGS) -c server.cpp
	
clean:
	rm *.o *.out
