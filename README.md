
pour creer un nouveau labyrinte :
> make maze NOM=nom_du_lab

exemple :
> make maze NOM=laby1
> ls Maze
laby1.maze




compiler votre libraire :
> make lib NOM=nom_resultat DIR=chemin

exemple :
> make lib NOM=lib_test DIR=lib_test
> ls | grep .so
lib_test.so 
