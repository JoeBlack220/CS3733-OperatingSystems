CC = cc
COPS =-D_GNU_SOURCE
LINT = lint
LOPS = -x -u

all: driver1 driver2

driver1: driver1.c myio.c
	$(CC) $(COPS) -o driver1 driver1.c  myio.c

driver2: driver2.c myio.c
	$(CC) $(COPS) -o driver2 driver2.c  myio.c

lintall: lintdriver1 lintdriver2

lintdriver1:
	$(LINT) $(LOPS) driver1.c myio.c

lintdriver2:
	$(LINT) $(LOPS) driver2.c myio.c

clean:
	rm -f *.o core driver1 driver2
