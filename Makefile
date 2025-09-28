CPPFLAGS = $(shell pkg-config --cflags opencv4)
LDLIBS = $(shell pkg-config --libs opencv4)

all: main.o Engine.o EngineVisualization.o ui.o TwoStroke.o FourStroke.o Dynamometer.o Video.o
	g++ -o main.out Engine.o EngineVisualization.o main.o ui.o TwoStroke.o FourStroke.o Dynamometer.o Video.o -lsfml-graphics -lsfml-window -lsfml-system $(CPPFLAGS) $(LDLIBS) -std=c++11 

ui.o: src/ui.cpp include/ui.h
	g++ -c src/ui.cpp -lsfml-graphics -lsfml-window -lsfml-system

Engine.o: Engine.cpp Engine.h
	g++ -c Engine.cpp

EngineVisualization.o: EngineVisualization.h EngineVisualization.cpp
	g++ -c EngineVisualization.cpp -lsfml-graphics -lsfml-window -lsfml-system

TwoStroke.o: TwoStroke.cpp TwoStroke.h Engine.h
	g++ -c TwoStroke.cpp

FourStroke.o: FourStroke.cpp FourStroke.h Engine.h
	g++ -c FourStroke.cpp

Dynamometer.o: Dynamometer.cpp Dynamometer.h Engine.h
	g++ -c Dynamometer.cpp

main.o: main.cpp Engine.h
	g++ -c main.cpp -lsfml-graphics -lsfml-window -lsfml-system $(CPPFLAGS) $(LDLIBS)

Video.o: src/Video.cpp include/Video.h
	g++ -c src/Video.cpp $(CPPFLAGS) $(LDLIBS) -std=c++11 

clean:
	rm -f *.o main.out