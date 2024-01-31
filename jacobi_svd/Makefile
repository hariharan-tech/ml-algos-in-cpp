run_win: main.c test.py
	gcc main.c -o main.exe
	.\main.exe
	python test.py [[8,2],[2,4]]

create_so: main.c
	 gcc main.c -shared -fPIC -m64 -o main.dll
	 gcc main.c -shared -fPIC -m64 -o main.so

run_linux: main.c
	gcc main.c -o main.out
	./main.out

# python_test: test.py
# 	python test.py [[4,2],[2,8]]