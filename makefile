main: main.o hash.o
	g++ -g main.o hash.o -o main
main.o: main.cpp hash.h
	g++ -g -c main.cpp
hash.o: hash.cpp hash.h TimeInterval.h
	g++ -g -c hash.cpp
clean:
	rm *.o
	rm main
run: main
	./main
debug: main
	gdb main