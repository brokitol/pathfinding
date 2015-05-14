NAME = PathFinder

DIR_PATHFINDER = main_test
DIR_SRC_PATHFINDER = ${DIR_PATHFINDER}/src
DIR_INC_PATHFINDER = ${DIR_PATHFINDER}/inc

SRC_PATHFINDER = ${DIR_SRC_PATHFINDER}/main.cpp				\
				 ${DIR_SRC_PATHFINDER}/dlib.cpp				\
				 ${DIR_SRC_PATHFINDER}/chargement_verif.cpp	\
				 ${DIR_SRC_PATHFINDER}/timestamp.cpp
NOM = lib

FLAG = -std=c++1y -Wall -Werror -Wextra

${NAME} : ${SRC_PATHFINDER}
	g++ -o ${NAME} ${FLAG} ${SRC_PATHFINDER} -I${DIR_INC_PATHFINDER} -ldl

all : ${NAME}

clean:

fclean: clean
	rm -rf ${NAME}
	rm -f *.so

re: fclean all

maze :
	ruby gen.rb > Maze/${NOM}.maze

test_maze :
	./${NAME} ${LIB} ${NB_TEST} ${RAND} ${DIR}/lvl_?.maze ${DIR}/lvl_1?.maze ${DIR}/lvl_2?.maze ${DIR}/lvl_3?.maze ${DIR}/lvl_4?.maze ${DIR}/lvl_5?.maze ${DIR}/lvl_6?.maze ${DIR}/lvl_7?.maze ${DIR}/lvl_8?.maze ${DIR}/lvl_9?.maze

lib :
	g++ -shared ${FLAG} -o ${NOM}.so ${DIR}/src/* -I${DIR}/inc -I${DIR_PATHFINDER}/inc -fPIC

help :
	@echo "regle all, PathFinder"
	@echo "	compile le main de test des librairies externe de pathfinding"
	@echo ""
	@echo "	option : aucune"
	@echo ""
	@echo "	exemple : 'make'"
	@echo ""
	@echo ""
	@echo "regle maze"
	@echo "	cree un labyrinte et le sauvegarde dans le dossier Maze"
	@echo ""
	@echo "	option :"
	@echo "		-NOM => le nom du fichier contenant le labyrinte (l'extention .maze est rajouter automatiquement)"
	@echo ""
	@echo "	exemple : 'make maze NOM=maze_test'"
	@echo ""
	@echo ""
	@echo "regle lib"
	@echo "	compile une librairie externe de pathfinding"
	@echo ""
	@echo "	option :"
	@echo "		-NOM => le nom de la lib (l'extention .so est rajouter automatiquement), valeur par default : lib"
	@echo "		-DIR => dossier contenant les source de la lib. ce dossier doit avoir les sous dossier inc et src"
	@echo ""
	@echo "	exemple : 'make lib NOM=lib_test DIR=lib_test'"
	@echo ""
	@echo ""
	@echo "regle test_maze"
	@echo "	lance le test d'une librairie externe de pathfinding"
	@echo ""
	@echo "	option :"
	@echo "		-LIB => le chemin et le nom complet de la lib"
	@echo "		-NB_TEST => le nombre de test a faire"
	@echo "		-RAND => la seed pour le random"
	@echo "		-DIR => dossier contenant les fichiers du labyrinthe"
	@echo ""
	@echo "	exemple : 'make test_maze LIB=micro.so NB_TEST=10 RAND=1 DIR=Maze/big_berta'"

.PHONY: all maze help lib clean fclean re
