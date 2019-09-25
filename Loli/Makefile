.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -fsanitize=undefined -O2
CXXFLAGS += -isystem ../include

GENERATORS: CXXFLAGS += -O2
GENERATORS += generators/test

TESTDATA = 01 02 03 04

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(TESTDATA:%=outputs/%.txt)

all: validator solution $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator

inputs/01.txt: generators/test
	generators/test && ./validator < $@

inputs/02.txt:
	./validator < $@

inputs/03.txt:
	./validator < $@

inputs/04.txt:
	./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(INPUTS) $(OUTPUTS)
