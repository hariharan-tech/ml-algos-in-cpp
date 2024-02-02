run_win: main.cpp
	g++ main.cpp -o main.exe
	.\main.exe

test_SVD: SVD.cpp test.py
	python test.py
	g++ SVD.cpp -o SVD.exe
	.\SVD.exe

create_so: main.cpp
	g++ main.cpp -shared -fPIC -m64 -o main.dll
	g++ main.cpp -shared -fPIC -m64 -o main.so

run_linux: main.cpp
	g++ main.cpp -o main.out
	./main.out

# python_test: test.py
# 	python test.py [[4,2],[2,8]]