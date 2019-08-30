CXXFLAGS = -g -Wall -W -Werror -pedantic
CXX = g++
PROG = test

$(PROG): game_map.o player.o
	$(CXX) $(CXXFLAGS) -o test game_map.o test.cpp

player.o:
	$(CXX) $(CXXFLAGS) -c -o player.o player.cpp

game_map.o:
	$(CXX) $(CXXFLAGS) -c -o game_map.o game_map.cpp

clean:
	rm $(PROG) *.o
