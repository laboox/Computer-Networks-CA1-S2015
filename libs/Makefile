include ../Makefile

mylib.a: keys.o sock.o user.o
	ar -cvr -o mylib.a keys.o sock.o user.o
keys.o: keys.cpp keys.h
	$(CC) $(CFLAGS) -c keys.cpp
sock.o: sock.cpp sock.h
	$(CC) $(CFLAGS) -c sock.cpp
user.o: user.cpp user.h
	$(CC) $(CFLAGS) -c user.cpp
	
clean: 
	rm *.o *.a
