CXXFLAGS = -g -Wall -Wextra -Wsign-compare -std=c++11
PA5: main.cpp Product.cpp ProductInventoryQuery.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^