CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic

all: TestOptimizations TestObjectLyfecycle

# Link object files to create the executable
TestOptimizations: testOptimizations.cpp
	$(CXX) $(CXXFLAGS) -o build/TestOptimizations testOptimizations.cpp

TestObjectLyfecycle: testObjectLifecycle.cpp
	$(CXX) $(CXXFLAGS) -o build/TestObjectLifecycle testObjectLifecycle.cpp
