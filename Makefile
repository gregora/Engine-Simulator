all: TwoStroke.o main.o
	g++ -o main.out TwoStroke.o main.o

TwoStroke.o: TwoStroke.cpp TwoStroke.h
	g++ -c TwoStroke.cpp

main.o: main.cpp TwoStroke.h
	g++ -c main.cpp
