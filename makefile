#
# makefile to compile all programs for the AED.P04 computer lab class
#

clean:
	rm -f examples assignment a.out

all:		examples

run_all:	all
	./examples 1


examples:	examples.c
	cc -Wall -O2 examples.c -o $@ -lm

.PHONY:		extra
extra:		solution_tsp.c cities.h
	cc -Wall -O3 -march=native solution_tsp.c -lm


assignment:	assignment.c
	cc -Wall -O2 assignment.c -o $@ -lm

