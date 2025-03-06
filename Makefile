all: FastUpscaler TestObjectLifecycle

cmake: *.cpp
	@cmake --build build/ --config Release --target all -j 6

FastUpscaler: FastUpscaler.cpp
	@cmake --build build/ --config Release --target FastUpscaler

TestObjectLifecycle: testObjectLifecycle.cpp
	@cmake --build build/ --config Release --target TestObjectLifecycle
