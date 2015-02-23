CC=g++
CFLAGS=`mysql_config --cflags` -I../global/ -fpermissive
CLIBS=`mysql_config --libs` ../global/reader.cpp ../global/FileShare.cpp

all: cload.out
cload.out: main.o
	$(CC) *.o -o cload.out $(CLIBS) 
main.o: main.cpp user.h Mysql.o Server.o session.o server.o
	$(CC) $(CFLAGS) -c main.cpp
Server.o: Server.cpp Server.h
	$(CC) $(CFLAGS) -c Server.cpp
session.o: session.cpp session.h Server.h
	$(CC) $(CFLAGS) -c session.cpp
server.o: server.cpp server.h
	$(CC) $(CFLAGS) -c server.cpp

sql: a.out
a.out: MysqlTest.o
	$(CC) *.o `mysql_config --libs`
MysqlTest.o: MysqlTest.cpp Mysql.o
	$(CC) $(CFLAGS) -c MysqlTest.cpp
Mysql.o: Mysql.cpp Mysql.h MysqlException.o FileException.o
	$(CC) $(CFLAGS) -c Mysql.cpp
FileException.o: FileException.cpp
	$(CC) $(CFLAGS) -c FileException.cpp
MysqlException.o: MysqlException.cpp
	$(CC) $(CFLAGS) -c MysqlException.cpp
clean:
	rm *.o *.out
