CC = cc
COPS =-D_GNU_SOURCE
LINT = lint
LOPS = -x -u

all: RecC1

RecC1: RecC1.c
	$(CC) $(COPS) -o RecC1 RecC1.c

lintall: RecC1

lintRecC1:
	$(LINT) $(LOPS) RecC1.c

clean:
	rm -f *.o RecC1
