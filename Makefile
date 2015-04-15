NAME = PathFinder

FLAG = -std=c++1y -Wall -Werror -Wextra

${NAME} : src/main.cpp
	g++ -o ${NAME} ${FLAG} main_test/src/main.cpp -I main_test/inc

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
