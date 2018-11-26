CC=g++
FLAGS=-Wall

SRC=src/
OBJ=obj/

DEPS=$(OBJ)graph.o $(OBJ)sudoku.o
NAME=sudoku-graph-coloring

$(OBJ)%.o: $(SRC)%.cpp $(OBJ)
	$(CC) -c -o $@ $<

$(NAME): $(DEPS)
	$(CC) main.cpp $(DEPS) -o $(NAME)

run: $(NAME)
	./$(NAME)

$(OBJ):
	mkdir $(OBJ)

clean:
	rm $(NAME)
	rm -rf $(OBJ)
