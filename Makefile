CFLAGS = -I. -g

relocatable = mybc.o lexer.o

mybc: $(relocatable)
	$(CC) -o mybc $(relocatable)

clean:
	$(RM) *.o