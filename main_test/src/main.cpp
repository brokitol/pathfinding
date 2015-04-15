#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dlfcn.h>

#include "main.hpp"
#include <sys/time.h>

void	aff_time(int t);

int main(int argc, char **argv)
{
	std::ifstream f;
	std::srand(time(0));

	if (argc < 4)
		std::cout << "usage : " << argv[0] << " maze nb_test lib {lib}" << std::endl;
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

	int	nb_test = atoi(argv[2]);
	for (int i = 3 ; i < argc ; i++)
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
		timeval	avant;
		timeval	apres;
		std::list<int> list_res;
		for (int i = 0; i < nb_test; i++)
		{
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

			gettimeofday(&avant, NULL);
			auto v = pathfinder->get_path(debut, fin);
			gettimeofday(&apres, NULL);

			int res = (apres.tv_sec - avant.tv_sec) * 1000000;
			res += apres.tv_usec - avant.tv_usec;
			list_res.push_front(res);

			int	sec;
			int mili;
			int micro;
	
			int tmp = apres.tv_usec - avant.tv_usec;
			sec = apres.tv_sec - avant.tv_sec;
			if (tmp < 0)
			{
				sec--;
				tmp += 1000000;
			}
			mili = tmp / 1000;
			micro = tmp - mili * 1000;

			std::cout << "test " << i << " :	temps mis : " << sec << "s,	" << mili << "ms,	" << micro << "μs" << std::endl;
		}	
		int total = 0;
		int min = 0;
		int max = 0;
		for (int i : list_res)
		{
			max = (i > max) ? i : max;
			min = (i < min || min == 0) ? i : min;
			total += i;
		}
		std::cout << "moyenne des appels :	" ; aff_time(total/list_res.size()) ; std::cout << std::endl;
		std::cout << "le plus rapide :    	" ; aff_time(min) ; std::cout << std::endl;
		std::cout << "le plus lent :      	" ; aff_time(max) ; std::cout << std::endl;

		/* debut	dechargement	API */
		delete pathfinder;
		dlclose(hndl);
		/* fin		dechargement	API */
	}
}

void	aff_time(int t)
{
	int sec = t / 1000000;
	t -= sec;
	int mili = t / 1000;
	t -= mili * 1000;
	int micro = t;
	std::cout << sec << "s,	" << mili << "ms,	" << micro << "μs";
}
