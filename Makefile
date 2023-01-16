FILES = main.o lexer.o parser.o err.o keywords.o
aurora:	$(FILES)
	gcc -g $(FILES) -o proxima

main.o: main.c
	gcc -g -c main.c

lexer.o: lexer.c lexer.h keywords.c keywords.h
	gcc -g -c lexer.c

parser.o: lexer.c lexer.h err.h err.c parser.h parser.c
	gcc -g -c parser.c	

err.o: err.c err.h
	gcc -g -c err.c

keywords.o: keywords.c keywords.h
	gcc -g -c keywords.c
	
clean:
	rm *.o proxima