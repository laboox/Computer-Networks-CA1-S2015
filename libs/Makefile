include ../Makefile

mylib.a: keys.o sock.o
	ar -cvr -o mylib.a keys.o sock.o 
keys.o: keys.cpp keys.h
	$(CC) $(CFLAGS) -c keys.cpp
sock.o: sock.cpp sock.h
	$(CC) $(CFLAGS) -c sock.cpp
clean: 
	rm *.o *.a
