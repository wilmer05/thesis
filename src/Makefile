CC=g++
CFLAGS=-std=c++11

run: main.o alg.o experiments.o utils.o
	$(CC) -o run main.o alg.o experiments.o utils.o

main.o: main.cpp 
	$(CC) -c -o main.o main.cpp $(CFLAGS)

utils.o: 
	$(CC) -c -o utils.o utils.cpp $(CFLAGS)
	
alg.o: 
	$(CC) -c -o alg.o alg.cpp $(CFLAGS)

experiments.o:
	$(CC) -c -o experiments.o experiments.cpp $(CFLAGS)

regression:
	$(CC) -o regression regression.cpp

clean:
	rm *.o regression
