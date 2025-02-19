CXXFLAGS = -g -Wall -Wextra -std=c++11
MA2: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^