CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic

all: FastUpscaler TestObjectLyfecycle

cmake: *.cpp
	@cmake --build build/ --config Release --target all -j 6

# FastUpscaler: FastUpscaler.cpp
# 	$(CXX) $(CXXFLAGS) -o build/FastUpscaler FastUpscaler.cpp

TestObjectLyfecycle: testObjectLifecycle.cpp
	$(CXX) $(CXXFLAGS) -o build/TestObjectLifecycle testObjectLifecycle.cpp
