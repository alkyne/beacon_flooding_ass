all: runme

runme: main.o
	g++ -g -o runme main.o -ltins -std=c++11

main.o: main.cpp
	g++ -g -c -o main.o main.cpp -std=c++11

clean:
	rm -rf *.o
	rm -rf runme
