# -*- Makefile -*-

all: test_code

test_code: statistics.o test_code.o
	g++ ./obj/statistics.o ./obj/test_code.o -o ./build/main.out

kmeans: ./src/kmeans.cpp ./lib/node.cpp ./lib/node.h
	g++ -c ./lib/node.cpp -o ./obj/node.o
	g++ -c ./src/kmeans.cpp -o ./obj/kmeans.o
	g++ ./obj/kmeans.o ./obj/node.o -o ./build/main.out

test_activ: ./src/test_activ.cpp ./lib/activation.cpp ./lib/activation.h
	g++ -c ./lib/activation.cpp -o ./obj/activation.o
	g++ -c ./src/test_activ.cpp -o ./obj/test_activ.o
	g++ ./obj/activation.o ./obj/test_activ.o -o ./build/test_activ.out

dataframe.o: ./lib/dataframe.cpp ./lib/dataframe.h
	g++ -c ./lib/dataframe.cpp -o ./obj/dataframe.o

activation.o: ./lib/activation.cpp ./lib/activation.h
	g++ -c ./lib/activation.cpp -o ./obj/activation.o

statistics.o: ./lib/statistics.h ./lib/statistics.cpp
	g++ -c ./lib/statistics.cpp -o ./obj/statistics.o

test_code.o: ./test_code.cpp
	g++ -c ./test_code.cpp -o ./obj/test_code.o

clean:
	rm -f ./obj/*.o
	rm -f ./build/*.out
