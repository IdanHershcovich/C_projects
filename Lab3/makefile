#!/usr/bin/make -f
CC=gcc
CFLAGS= -lpthread -o

all: client server

client: client.c csapp.h csapp.c
	$(CC) client.c -o client -lpthread
	./client $(HOST) $(PORT) $(FILE)

server: server.c csapp.h csapp.c
	$(CC) server.c -o server -lpthread
	./server $(PORT)

clean:
	rm -rf *.o