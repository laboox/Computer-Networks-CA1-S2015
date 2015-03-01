include ../Makefile

all: client.out
client.out: main.o register.o
	$(CC) $(CFLAGS) *.o $(CLIBS) -o client.out
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
register.o: sock_client.o register.cpp register.h
	$(CC) $(CFLAGS) -c register.cpp
sock_client.o: sock_client.cpp sock_client.h
	$(CC) $(CFLAGS) -c sock_client.cpp
	

clean:
	rm *.o *.out
