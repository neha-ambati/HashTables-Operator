CC = gcc

CFLAGS = -std=c99 -Wall -pedantic -g

OBJS = hash.o hash.h

all: hash.o

hash.o: hash.c
	$(CC) $(CFLAGS) -c hash.c

htest1.o: htest1.c
	$(CC) $(CFLAGS) -c htest1.c

htest1: htest1.o $(OBJS) hash.h
	$(CC) $(CFLAGS) -o htest1 htest1.o $(OBJS)

htest2.o: htest2.c
	$(CC) $(CFLAGS) -c htest2.c

htest2: htest2.o $(OBJS) hash.h
	$(CC) $(CFLAGS) -o htest2 htest2.o $(OBJS)

htest3.o: htest3.c
	$(CC) $(CFLAGS) -c htest3.c

htest3: htest3.o $(OBJS) hash.h
	$(CC) $(CFLAGS) -o htest3 htest3.o $(OBJS)

htest4.o: htest4.c
	$(CC) $(CFLAGS) -c htest4.c

htest4: htest4.o $(OBJS) hash.h
	$(CC) $(CFLAGS) -o htest4 htest4.o $(OBJS)

clean:
	rm *o htest1 htest2 htest3 htest4
