CXXFLAGS = -g -Wall -Wextra -Wsign-compare -std=c++11
PA4: main.cpp Product.cpp ProductInventoryQuery.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^