CC=g++
CFLAGS=-c -Wall
INCPATH=

all: test

test: test.o filedb.o
	$(CC) test.o filedb.o -o test

test.o: test.cpp filedb.h
	$(CC) $(CFLAGS) $(INCPATH) -o test.o test.cpp -lboost_unit_test_framework

filedb.o: filedb.cpp filedb.h
	$(CC) $(CFLAGS) $(INCPATH) -o filedb.o filedb.cpp

clean:
	rm -rf *.o test
