CC=g++
CFLAGS=`pkg-config --cflags libssl` -I../libs/
CLIBS=../libs/mylib.a `pkg-config --cflags --libs libssl`
