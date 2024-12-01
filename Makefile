run: build
	@build/FastUpscaler

build: *.cpp
	@cmake --build build/ --config Release --target all -j 6
