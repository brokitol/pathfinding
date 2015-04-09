NAME = PathFinder

FLAG = -std=c++1y -Wall -Werror -Wextra

${NAME} : src/main.cpp
	g++ -o ${NAME} ${FLAG} src/main.cpp -I inc

all : ${NAME}

clean:

fclean: clean
	rm -rf ${NAME}
	rm -f *.so

re: fclean all

maze :
	ruby gen.rb > Maze/${NOM}.maze

lib :
	g++ -shared ${FLAG} -o ${NOM}.so ${DIR}/src/* -I${DIR}/inc -I inc

.PHONY: all maze
