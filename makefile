CC:=g++

all: main.o Lexer.o
	$(CC) -o main main.o Lexer.o
dep: main.cpp src/Lexer.cpp
	$(CC) -c -W main.cpp
	$(CC) -c -W src/Lexer.cpp
clean:
	rm *.o