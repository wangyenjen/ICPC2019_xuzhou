CXX = g++

all: generators/gen
	mkdir -p inputs
	mkdir -p outputs
	cd generators && ./gen

generators/gen: generators/gen.cpp
	$(CXX) generators/gen.cpp -o generators/gen

.PHONY: clean

clean:
	rm inputs/*.in
	rm outputs/*.out
	rm generators/gen


