CXXFLAGS = -std=c++11 -fopenmp -Wall -W -Werror -pedantic -g -O3
CXXLINKS = -lncursesw -lm
CXX = g++
PROG = game

$(PROG): main.cpp game_map.o player.o frame.o
	$(CXX) $(CXXFLAGS) -o $(PROG) $^ $(CXXLINKS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(CXXLINKS)

clean:
	rm $(PROG) *.o
