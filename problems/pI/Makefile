.PHONY: all clean
.DELETE_ON_ERROR:

CXXFLAGS = -std=c++17 -Wall -Wextra -fsanitize=undefined -O2
CXXFLAGS += -isystem ../include

TESTDATA = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21
INPUTS = $(TESTDATA:%=inputs/%.txt)
OUTPUTS = $(TESTDATA:%=outputs/%.txt)

all : validator solution generators/test compile

validator : validator.cpp
solution: solution.cpp

generators/test : generators/test.cpp
compile : generators/test
	generators/./test

clean:
	$(RM) validator solution generators/test compile $(INPUTS) $(OUTPUTS)