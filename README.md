
pour creer un nouveau labyrinte :
> make maze NOM=nom_du_lab

exemple :
> make maze NOM=laby1
> ls Maze
laby1.maze




compiler votre libraire :
> make lib NOM=nom_resultat SRC_DIR=chemin_vers_vos_sources INC_DIR=chemin_vers_vos_includes

exemple :
> make lib NOM=lib_test SRC_DIR=lib_test_src INC_DIR=lib_test_include
> ls | grep .so
lib_test.so 
