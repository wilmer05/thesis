CC=g++
CFLAGS=-std=c++11

run: main.o alg.o experiments.o
	$(CC) -o run main.o alg.o experiments.o

main.o: main.cpp 
	$(CC) -c -o main.o main.cpp $(CFLAGS)
	
alg.o: 
	$(CC) -c -o alg.o alg.cpp $(CFLAGS)

experiments.o:
	$(CC) -c -o experiments.o experiments.cpp $(CFLAGS)

clean:
	rm *.o
