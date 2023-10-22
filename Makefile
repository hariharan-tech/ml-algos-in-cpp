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

test_linreg: ./src/Test_LinReg.cpp ./lib/activation.cpp ./lib/activation.h ./lib/dataframe.cpp ./lib/dataframe.h ./lib/Regression.cpp ./lib/Regression.h ./lib/statistics.cpp ./lib/statistics.h
	g++ -c ./lib/activation.cpp -o ./obj/activation.o
	g++ -c ./lib/dataframe.cpp -o ./obj/dataframe.o
	g++ -c ./lib/statistics.cpp -o ./obj/statistics.o
	g++ -c ./lib/Regression.cpp -o ./obj/Regression.o
	g++ -c ./src/Test_LinReg.cpp -o ./obj/Test_LinReg.o
	g++ ./obj/activation.o ./obj/dataframe.o ./obj/statistics.o ./obj/Regression.o ./obj/Test_LinReg.o -o ./build/test_linreg.out

test_logreg: ./src/Test_LogReg.cpp ./lib/activation.cpp ./lib/activation.h ./lib/dataframe.cpp ./lib/dataframe.h ./lib/Regression.cpp ./lib/Regression.h ./lib/statistics.cpp ./lib/statistics.h
	g++ -c ./lib/activation.cpp -o ./obj/activation.o
	g++ -c ./lib/dataframe.cpp -o ./obj/dataframe.o
	g++ -c ./lib/statistics.cpp -o ./obj/statistics.o
	g++ -c ./lib/Regression.cpp -o ./obj/Regression.o
	g++ -c ./src/Test_LogReg.cpp -o ./obj/Test_LogReg.o
	g++ ./obj/activation.o ./obj/dataframe.o ./obj/statistics.o ./obj/Regression.o ./obj/Test_LogReg.o -o ./build/test_logreg.out

test_df: ./src/test_df.cpp ./lib/dataframe.cpp ./lib/dataframe.h
	g++ -c ./lib/dataframe.cpp -o ./obj/dataframe.o
	g++ -c ./src/test_df.cpp -o ./obj/test_df.o
	g++ ./obj/dataframe.o ./obj/test_df.o -o ./build/test_df.out 

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
