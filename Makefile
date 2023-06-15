main: comp
	./a.out

mem: comp
	valgrind ./a.out

comp:
	g++ *.cpp -Wall -Wextra -g -std=c++11