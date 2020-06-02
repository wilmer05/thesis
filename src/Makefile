CC=g++
CFLAGS=-std=c++11

run: main.o
	$(CC) -o run main.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
