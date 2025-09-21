all: main.o Engine.o EngineVisualization.o ui.o
	g++ -o main.out Engine.o EngineVisualization.o main.o ui.o -lsfml-graphics -lsfml-window -lsfml-system

ui.o: src/ui.cpp include/ui.h
	g++ -c src/ui.cpp -lsfml-graphics -lsfml-window -lsfml-system

Engine.o: Engine.cpp Engine.h
	g++ -c Engine.cpp

EngineVisualization.o: EngineVisualization.h EngineVisualization.cpp
	g++ -c EngineVisualization.cpp -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp Engine.h
	g++ -c main.cpp -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f *.o main.out