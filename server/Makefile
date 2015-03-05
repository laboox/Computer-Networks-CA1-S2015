include ../Makefile

all: server.out
server.out: main.o
	$(CC) $(CFLAGS) *.o $(CLIBS) -o server.out
main.o: main.cpp ElectionManager.o
	$(CC) $(CFLAGS) -c main.cpp
ElectionManager.o: ElectionManager.cpp ElectionManager.h Box.o Candidate.o Time.o
	$(CC) $(CFLAGS) -c ElectionManager.cpp
Box.o: Box.cpp Box.h
	$(CC) $(CFLAGS) -c Box.cpp
Candidate.o: Candidate.cpp Candidate.h
	$(CC) $(CFLAGS) -c Candidate.cpp
Time.o: Time.cpp Time.h
	$(CC) $(CFLAGS) -c Time.cpp
clean:
	rm *.o *.out
