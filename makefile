#CS483 PEX2 makefile
#C2C Justin Niquette
#8 Feb 2015

shell: shell.o
	gcc shell.o -o shell

shell.o: shell.c makefile
	gcc -c shell.c

run:	shell
	./shell

clean:
	rm -rf *.o shell *~
