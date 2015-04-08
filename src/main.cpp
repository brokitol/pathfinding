#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dlfcn.h>

#include "main.hpp"

int main(int argc, char **argv)
{
	std::ifstream f;
	std::srand(time(0));

	if (argc < 3)
		std::cout << "usage : " << argv[0] << " maze lib {lib}" << std::endl;
	std::vector< std::vector< bool > > maze;

	f.open (argv[1], std::ifstream::in);
	for (std::string s; getline(f,s);)
	{
		std::vector<bool>	tmp;
		for (char c : s)
		{
			if (c == ' ')
				tmp.push_back(true);
			else
				tmp.push_back(false);
		}
		maze.push_back(tmp);
	}

	for (int i = 2 ; i < argc ; i++)
	{
		void *	hndl = NULL;
		API *	pathfinder = NULL;
		void *	mkr = NULL;
		int		x = 0;
		int		y = 0;

		/* debut	chargement		API */
		API *(*pmaker)(labi2D);

		if((hndl = dlopen(argv[i], RTLD_LOCAL)) == NULL)
		{
			std::cerr << "erreur de chargement de la lib (dlopen): " << dlerror() << std::endl;
			continue;
		}

		if ((mkr = dlsym(hndl, "create_pathfinder2D")) == NULL)
		{
			std::cerr << "erreur d'initialisation de la lib (dlsym): "<< dlerror() << std::endl;
			dlclose(hndl);
			continue;
		}
		pmaker = reinterpret_cast<API *(*)(labi2D)>(mkr);
		pathfinder = pmaker(maze);
		/* fin		chargement		API */

		/* debut	utilisation		API */
		do {
			x = std::rand() % maze.size();
			y = std::rand() % maze[x].size();
		} while (maze[x][y] == false);
		coordonnee debut(x, y);

		do {
			x = std::rand() % maze.size();
			y = std::rand() % maze[x].size();
		} while (maze[x][y] == false);
		coordonnee fin(x, y);

		auto v = pathfinder->get_path(debut, fin);
		
		for (coordonnee i : v)
			std::cout << "[ " << i.x << " , " << i.y << " , " << i.z << " ]" << std::endl;
		/* fin		utilisation		API */

		/* debut	dechargement	API */
		delete pathfinder;
		dlclose(hndl);
		/* fin		dechargement	API */
	}
}
