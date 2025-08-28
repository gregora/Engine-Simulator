all: TwoStroke.o main.o EngineVisualization.o ui.o
	g++ -o main.out TwoStroke.o EngineVisualization.o main.o ui.o -lsfml-graphics -lsfml-window -lsfml-system

ui.o: src/ui.cpp include/ui.h
	g++ -c src/ui.cpp -lsfml-graphics -lsfml-window -lsfml-system

TwoStroke.o: TwoStroke.cpp TwoStroke.h
	g++ -c TwoStroke.cpp

EngineVisualization.o: EngineVisualization.h EngineVisualization.cpp
	g++ -c EngineVisualization.cpp -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp TwoStroke.h
	g++ -c main.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o main.out