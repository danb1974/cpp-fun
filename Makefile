# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic

# Source files
SRCS = *.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output binary
TARGET = TestOptimizations

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o build/$@ $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) build/$(TARGET)

run: all
	@./build/$(TARGET)

# Phony targets
.PHONY: all clean
