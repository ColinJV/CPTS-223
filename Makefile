CXXFLAGS = -g -Wall -Wextra -std=c++11
PA2: main.cpp Destination.cpp ListMyJosephus.cpp VectorMyJosephus.cpp TestListMyJosephus.cpp TestVectorMyJosephus.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^