.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -fsanitize=undefined -O2
CXXFLAGS += -isystem ../include

GENERATORS: CXXFLAGS += -O2
GENERATORS += generators/test

TESTDATA = 01 02 03 04 05 06 07 08 09 10

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

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	time ./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(INPUTS) $(OUTPUTS)
