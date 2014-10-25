CXXFLAGS=-Wall -Wextra -ggdb -std=c++11 -lboost_regex
CC=g++

monety: monety.o
	$(CC) $(CXXFLAGS) -o monety monety.o

%.o: %.cc
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -f monety monety.o

.PHONY: clean

.DEFAULT: monety
