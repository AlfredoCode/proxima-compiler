FILES = main.o lexer.o
aurora:	$(FILES)
	gcc -g $(FILES) -o proxima

main.o: main.c
	gcc -c main.c

scanner.o: lexer.c lexer.h
	gcc -c lexer.c

clean:
	rm *.o proxima