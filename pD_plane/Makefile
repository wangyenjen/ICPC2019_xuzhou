CXXFLAGS = -O2 -Wall -I../include

VALIDATOR = ./val
GENERATOR = ./generator.py
SOLUTION = ./sol

EXES = $(VALIDATOR) $(SOLUTION)
TESTDATA = 01 02 03 04 05 06 07 08 09 10 11
SAMPLE = sample1 sample2

INPUTS = $(TESTDATA:%=data/%.in)
OUTPUTS = $(TESTDATA:%=data/%.out) $(SAMPLE:%=data/%.out)

all: $(INPUTS) $(OUTPUTS)

$(EXES): %: %.cpp

$(OUTPUTS): %.out: %.in $(SOLUTION)
	\time $(SOLUTION) < $< > $@

$(INPUTS): $(EXES) $(GENERATOR)

data/01.in:
	$(GENERATOR) 10 10 3 > $@
	$(VALIDATOR) < $@
data/02.in:
	$(GENERATOR) 20 10 2 > $@
	$(VALIDATOR) < $@
data/03.in:
	$(GENERATOR) 50 50 1 > $@
	$(VALIDATOR) < $@
data/04.in:
	$(GENERATOR) 100 40 3 > $@
	$(VALIDATOR) < $@
data/05.in:
	$(GENERATOR) 1000 40 3 > $@
	$(VALIDATOR) < $@
data/06.in:
	$(GENERATOR) 1000 1000 3 > $@
	$(VALIDATOR) < $@
data/07.in:
	$(GENERATOR) 10000 1000 3 > $@
	$(VALIDATOR) < $@
data/08.in:
	$(GENERATOR) 10000 5000 3 > $@
	$(VALIDATOR) < $@
data/09.in:
	$(GENERATOR) 10000 10000 3 > $@
	$(VALIDATOR) < $@
data/10.in:
	$(GENERATOR) 10000 8000 2 > $@
	$(VALIDATOR) < $@
data/11.in:
	$(GENERATOR) 3000 100 3 > $@
	$(VALIDATOR) < $@

clean:
	$(RM) $(EXES) $(INPUTS) $(OUTPUTS)
clean_exe:
	$(RM) $(EXES)
