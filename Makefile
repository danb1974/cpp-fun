CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic

all: FastUpscaler TestObjectLyfecycle

# Link object files to create the executable
FastUpscaler: FastUpscaler.cpp
	$(CXX) $(CXXFLAGS) -o build/FastUpscaler FastUpscaler.cpp

TestObjectLyfecycle: testObjectLifecycle.cpp
	$(CXX) $(CXXFLAGS) -o build/TestObjectLifecycle testObjectLifecycle.cpp
