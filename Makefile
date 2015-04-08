NAME = PathFinder

FLAG = -std=c++1y -Wall -Werror -Wextra

${NAME} : main.cpp
	g++ -o ${NAME} ${FLAG} main.cpp

all : ${NAME} maze

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
