include ../Makefile

all: server.out
server.out: main.o
	$(CC) $(CFLAGS) *.o $(CLIBS) -o server.out
main.o: main.cpp ElectionManager.o
	$(CC) $(CFLAGS) -c main.cpp
ElectionManager.o: ElectionManager.cpp ElectionManager.h Box.o Candidate.o
	$(CC) $(CFLAGS) -c ElectionManager.cpp
Box.o: Box.cpp Box.h
	$(CC) $(CFLAGS) -c Box.cpp
Candidate.o: Candidiate.cpp Candidate.h
	$(CC) $(CFLAGS) -c Candidate.cpp

clean:
	rm *.o *.out
