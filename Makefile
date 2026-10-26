TARGET = kalsel
OBJ = build/main.o \
      build/lexer.o 
COM = g++
CFLAGS = -Wall -g -Iincludes


$(TARGET): $(OBJ)
	$(COM) $(CFLAGS) $(OBJ) -o $(TARGET)

build/main.o: main.cpp
	$(COM)  $(CFLAGS) -c main.cpp -o build/main.o

build/lexer.o: src/lexer.cpp
	$(COM) $(CFLAGS) -c src/lexer.cpp -o build/lexer.o

clean:
	rm -Rf build kalsel
