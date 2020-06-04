CC=g++
CFLAGS=-std=c++11

run: main.o alg.o experiment.o
	$(CC) -o run main.o alg.o experiment.o

main.o: main.cpp 
	$(CC) -c -o main.o main.cpp $(CFLAGS)
	
alg.o: 
	$(CC) -c -o alg.o alg.cpp $(CFLAGS)

experiment.o:
	$(CC) -c -o experiment.o experiment.cpp $(CFLAGS)

clean:
	rm *.o
