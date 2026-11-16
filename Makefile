CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRC      = src/escaleras.cpp src/monedas.cpp

all: build/dp

build/dp: $(SRC) src/main.cpp src/escaleras.h src/monedas.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $(SRC) src/main.cpp

build/test_dp: $(SRC) tests/test_dp.cpp src/escaleras.h src/monedas.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $(SRC) tests/test_dp.cpp

test: build/test_dp
	./build/test_dp

clean:
	rm -rf build

.PHONY: all test clean
