CXXFLAGS = -O2 -Wall -I../include

VALIDATOR = ./val
GENERATOR = ./generator
SOLUTION = ./solutions/sol

EXES = $(VALIDATOR) $(GENERATOR) $(SOLUTION)
TESTDATA = 01 02 03 04 05 06
SAMPLE = sample1

INPUTS = $(TESTDATA:%=data/%.in)
OUTPUTS = $(TESTDATA:%=data/%.out) $(SAMPLE:%=data/%.out)

all: $(INPUTS) $(OUTPUTS)

$(EXES): %: %.cpp

$(OUTPUTS): %.out: %.in $(SOLUTION) $(GEN_ANS) $(CHECKER)
	\time $(SOLUTION) < $< > $@

$(INPUTS): $(EXES)

data/01.in:
	$(GENERATOR) 1000 100000000000000 > $@
	$(VALIDATOR) < $@
data/02.in:
	$(GENERATOR) 1000 1000000000000000000 > $@
	$(VALIDATOR) < $@
data/03.in:
	$(GENERATOR) 100000 100000000000000 > $@
	$(VALIDATOR) < $@
data/04.in:
	$(GENERATOR) 100000 10000000000000000 > $@
	$(VALIDATOR) < $@
data/05.in:
	$(GENERATOR) 100000 100000000000000000 > $@
	$(VALIDATOR) < $@
data/06.in:
	$(GENERATOR) 100000 1000000000000000000 > $@
	$(VALIDATOR) < $@

clean:
	$(RM) $(EXES) $(INPUTS) $(OUTPUTS)
clean_exe:
	$(RM) $(EXES)
