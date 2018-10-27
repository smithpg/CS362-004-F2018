CFLAGS= -Wall -fpic -coverage -lm -std=c99

runTest: testMe
	./testMe

testMe: testMe.c 
	gcc -o testMe testMe.c $(CFLAGS)

clean:
	rm testMe 
