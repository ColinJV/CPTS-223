CXXFLAGS = -g -Wall -Wextra -std=c++11
PA2: main.cpp USCity.cpp testAVLMap.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^