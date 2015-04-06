NAME = PathFinder

FLAG = -std=c++1y -Wall -Werror -Wextra

${NAME} : main.cpp
	g++ -o ${NAME} ${FLAG} main.cpp

all : ${NAME} maze

maze :
	ruby gen.rb > Maze/${NOM}.maze

lib :
	g++ -shared ${FLAG} -o ${NOM}.so ${SRC_DIR}/* -I${INC_DIR} -I .

.PHONY: all maze
