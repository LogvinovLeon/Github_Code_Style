MAIN=monety
GCCOPT=-Wall -O2 -std=c++11 -lboost_regex

all: $(MAIN)

$(MAIN): %: %.cc
	g++ -o $(MAIN) $(GCCOPT) $<

clean:
	rm -f $(MAIN) *.out
