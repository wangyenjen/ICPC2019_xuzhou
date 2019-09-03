.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=undefined
CXXFLAGS += -isystem ../include

GENERATORS += generators/tree
GENERATORS += generators/graph
GENERATORS += generators/cycle
GENERATORS += generators/forest

INPUTS += inputs/03.txt
INPUTS += inputs/04.txt
INPUTS += inputs/05.txt
INPUTS += inputs/06.txt

OUTPUTS += outputs/01-sample.txt
OUTPUTS += outputs/02-sample.txt
OUTPUTS += outputs/03.txt
OUTPUTS += outputs/04.txt
OUTPUTS += outputs/05.txt
OUTPUTS += outputs/06.txt

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
