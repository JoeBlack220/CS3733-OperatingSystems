all: assign1-0 assign1 runalla

assign1-0: assign1-0.c pslibrary.c
	cc -o assign1-0 assign1-0.c pslibrary.c

assign1: assign1.c pslibrary.c
	cc -o assign1 assign1.c pslibrary.c

runalla:
	cc -o runalla runalla.c pslibrary.c

clean:
	rm -f assign1-0 assign1 runalla *.o

run1:
	./assign1 3 8 7 3 6 3 2 > Test-1.txt
run2:
	./assign1 3 8 7 3 6 7 2 > Test-2.txt
run3:
	./assign1 4 8 7 3 6 1 2 > Test-3.txt
run4:
	./assign1 3 3 3 4 2 1 2 > Test-4.txt
run5:
	./assign1 3 3 2 3 2 1 2 > Test-5.txt
run6:
	./assign1 3 5 2 5 4 1 1 > Test-6.txt
