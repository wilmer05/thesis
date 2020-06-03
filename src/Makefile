CC=g++
CFLAGS=-std=c++11

run: main.o
	$(CC) -o run main.o alg.o

main.o: main.cpp alg.o 
	$(CC) -c -o main.o main.cpp $(CFLAGS)
	
alg.o: 
	$(CC) -c -o alg.o alg.cpp $(CFLAGS)

clean:
	rm *.o
