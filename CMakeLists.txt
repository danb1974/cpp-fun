cmake_minimum_required(VERSION 3.10)

# Project Name
project(FastUpscaler)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the executable
add_executable(FastUpscaler FastUpscaler.cpp)
add_executable(TestObjectLifecycle TestObjectLifecycle.cpp)

# Link OpenCV libraries
target_link_libraries(FastUpscaler ${OpenCV_LIBS})
