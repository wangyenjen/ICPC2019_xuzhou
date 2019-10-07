CXXFLAGS = -O2 -Wall -I../include

VALIDATOR = ./val
GENERATOR = ./generator
CHECKER = ./checker
SOLUTION = ./solutions/sol
GEN_ANS = ./solutions/clp

EXES = $(VALIDATOR) $(GENERATOR) $(SOLUTION) $(CHECKER) $(GEN_ANS)
TESTDATA = 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
SAMPLE = sample1 sample2

INPUTS = $(TESTDATA:%=data/%.in)
OUTPUTS = $(TESTDATA:%=data/%.out) $(SAMPLE:%=data/%.out)

all: $(INPUTS) $(OUTPUTS)

$(EXES): %: %.cpp
./solutions/clp: LDLIBS += -lClp -lCoinUtils

$(OUTPUTS): %.out: %.in $(SOLUTION) $(GEN_ANS) $(CHECKER)
	$(GEN_ANS) < $< > $@
	\time $(SOLUTION) < $< > $(@:.out=.tmp)
	$(CHECKER) $< $(@:.out=.tmp) $@
	$(RM) $(@:.out=.tmp)

$(INPUTS): $(EXES)

data/01.in:
	$(GENERATOR) 1000 3 0 > $@
	$(VALIDATOR) < $@
data/02.in:
	$(GENERATOR) 1000 10 1 > $@
	$(VALIDATOR) < $@
data/03.in:
	$(GENERATOR) 1000 50 2 > $@
	$(VALIDATOR) < $@
data/04.in:
	$(GENERATOR) 1000 50 1 > $@
	$(VALIDATOR) < $@
data/05.in:
	$(GENERATOR) 20000 3 1 > $@
	$(VALIDATOR) < $@
data/06.in:
	$(GENERATOR) 20000 3 2 > $@
	$(VALIDATOR) < $@
data/07.in:
	$(GENERATOR) 20000 4 0 > $@
	$(VALIDATOR) < $@
data/08.in:
	$(GENERATOR) 20000 50 0 > $@
	$(VALIDATOR) < $@
data/09.in:
	$(GENERATOR) 20000 50 1 > $@
	$(VALIDATOR) < $@
data/10.in:
	$(GENERATOR) 20000 50 2 > $@
	$(VALIDATOR) < $@
data/11.in:
	$(GENERATOR) 20000 49 1 > $@
	$(VALIDATOR) < $@
data/12.in:
	$(GENERATOR) 20000 48 0 > $@
	$(VALIDATOR) < $@
data/13.in:
	$(GENERATOR) 20000 20 1 > $@
	$(VALIDATOR) < $@
data/14.in:
	$(GENERATOR) 20000 27 0 > $@
	$(VALIDATOR) < $@
data/15.in:
	$(GENERATOR) 20000 16 2 > $@
	$(VALIDATOR) < $@

clean:
	$(RM) $(EXES) $(INPUTS) $(OUTPUTS)
clean_exe:
	$(RM) $(EXES)
