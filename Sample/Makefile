.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/tree
GENERATORS += generators/graph
GENERATORS += generators/cycle
GENERATORS += generators/forest

TESTDATA = 01-sample 02-sample 03 04 05 06

INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(TESTDATA:%=outputs/%.txt)

all: validator solution $(INPUTS) $(OUTPUTS)

validator: validator.cpp

solution: CXXFLAGS += -O2
solution: solution.cpp

$(GENERATORS): %: %.cpp

$(INPUTS): validator

inputs/03.txt: generators/tree
	generators/tree 1000000 > $@ && ./validator < $@
inputs/04.txt: generators/graph
	generators/graph 1000000 999999 > $@ && ./validator < $@
inputs/05.txt: generators/cycle
	generators/cycle 1000000 > $@ && ./validator < $@
inputs/06.txt: generators/forest
	generators/forest 1000000 2 > $@ && ./validator < $@

$(OUTPUTS): outputs/% : inputs/% solution
	@mkdir -p $(@D)
	./solution < $< > $@

clean:
	$(RM) validator solution $(GENERATORS) $(INPUTS) $(OUTPUTS)
