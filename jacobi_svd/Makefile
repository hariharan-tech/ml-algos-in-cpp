run_win: main.cpp
	g++ main.cpp -o main.exe
	.\main.exe

run_win_test: main.cpp test.py
	g++ main.cpp -o main.exe
	.\main.exe
	python test.py [[8,2],[2,4]]

create_so: main.cpp
	g++ main.cpp -shared -fPIC -m64 -o main.dll
	g++ main.cpp -shared -fPIC -m64 -o main.so

run_linux: main.cpp
	g++ main.cpp -o main.out
	./main.out

# python_test: test.py
# 	python test.py [[4,2],[2,8]]