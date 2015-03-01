include ../Makefile

all: ca.out
ca.out: main.o
	$(CC) *.o -o ca.out $(CLIBS) 
main.o: main.cpp server.o
	$(CC) $(CFLAGS) -c main.cpp
server.o: server.cpp server.h
	$(CC) $(CFLAGS) -c server.cpp
	
clean:
	rm *.o *.out
