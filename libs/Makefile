include ../Makefile

mylib.a: keys.o
	ar -cvr -o mylib.a keys.o
keys.o: keys.cpp keys.h
	$(CC) $(CFLAGS) -c keys.cpp

clean: 
	rm *.o *.a
