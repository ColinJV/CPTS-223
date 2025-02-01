CXXFLAGS = -g -Wall -Wextra
PA1: main.cpp Data.cpp Game.cpp Player.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^