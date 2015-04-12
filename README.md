
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

paris avec mikael :
	- date de rendu max : 2 semaine apres la piscine
	- temps de reponse : 25ms sois 40 appel par seconde
	- 1G de ram max
	- 2G sur le disque dur max (sgoinfre = disque dur)
	- taille des maps : 200 x 200 x 100
	- il peut y avoir un chemin, ou pas. (meme temps de reponce dans touts les cas)
	- l'initialisation du pathfinder n'est pas pris en compte dans le temps de reponse, mais il est inclue dans les limites de memoire et doit prendre moins de 5s.
