CC = gcc
COPS =-D_GNU_SOURCE
LINT = lint
LOPS = -x -u

all: bank customer

bank: bank.c
	$(CC) $(COPS) -o bank bank.c

customer: customer.c
	$(CC) $(COPS) -o customer customer.c

lintall: lintBank lintCostumer

lintBank:
	$(LINT) $(LOPS) Bank.c
lintCostumer:
	$(LINT) $(LOPS) customer.c

clean:
	rm -f *.o bank customer ATM1 ATM2
