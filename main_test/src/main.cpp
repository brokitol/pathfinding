/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:41:00 by bgauci            #+#    #+#             */
/*   Updated: 2015/04/25 15:45:35 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "main.hpp"
#include "dlib.hpp"
#include "timestamp.hpp"
#include <sys/time.h>

std::string error_path;

void	aff_time(int t);

void init_maze2D(std::vector< std::vector< bool > > *maze, std::ifstream *f)
{
	for (std::string s; getline(*f,s);)
	{
		std::vector<bool>	tmp;
		for (char c : s)
		{
			if (c == ' ')
				tmp.push_back(true);
			else
				tmp.push_back(false);
		}
		maze->push_back(tmp);
	}
}

bool verif_path(std::list<coordonnee> const path, coordonnee const debut, coordonnee const fin, std::vector< std::vector< bool > > const maze)
{
	if (path.front() != debut) {error_path = "point de depart invalide";return false;}
	if (path.back() != fin) {error_path = "point de fin invalide";return false;}
	auto a = path.begin();
	auto b = path.begin();
	b++;
	while (a != path.end() and b != path.end())
	{
		if (maze[a->x][a->y] == false) {error_path = "point a invalide";return false;}
		if (maze[b->x][b->y] == false) {error_path = "point b invalide";return false;}
		if ((a->x != b->x and a->y != b->y) or ((a->x != b->x or a->y != b->y) and a->z != b->z)) {error_path = "passage entre a et b impossible";return false;}
		a++;
		b++;
	}
	if (path.size() > 2)
		return true;
	return false;
}

int main(int argc, char **argv)
{
	std::ifstream	f;
	Dlib *			chargeur_lib;

	if (argc < 5)
	{
		std::cout << "usage : " << argv[0] << " maze nb_test rand_seed lib {lib}" << std::endl;
		exit(0);
	}
	std::vector< std::vector< bool > > maze;

	f.open (argv[1], std::ifstream::in);
	init_maze2D(&maze, &f);

	int	nb_test = atoi(argv[2]);
	for (int i = 4 ; i < argc ; i++)
	{
		API *(*pmaker)(labi2D);
		API *	pathfinder = NULL;
		int		x = 0;
		int		y = 0;
		timeval	avant;
		timeval	apres;

		/* debut	chargement		API */
		try
		{
			chargeur_lib = new Dlib(argv[i]);
			pmaker = chargeur_lib->get_create_pathfinder2D();
		}
		catch (Exception *e)
		{
			std::cerr << "exception : " << e->what() << std::endl;
			continue;
		}

		gettimeofday(&avant, NULL);
		pathfinder = pmaker(maze);
		gettimeofday(&apres, NULL);

		std::cout << "temps d'initialisation de lib : " << Timestamp(apres) - Timestamp(avant) << std::endl; 
		/* fin		chargement		API */

		/* debut	utilisation		API */
		std::list<Timestamp> list_res;
		std::srand(atoi(argv[3]));

		for (int i = 0; i < nb_test; i++)
		{
			do {
				x = std::rand() % maze.size();
				y = std::rand() % maze[x].size();
			} while (maze[x][y] == false);
			coordonnee const debut(x, y);
    
			do {
				x = std::rand() % maze.size();
				y = std::rand() % maze[x].size();
			} while (maze[x][y] == false);
			coordonnee const fin(x, y);

			gettimeofday(&avant, NULL);
			auto v = pathfinder->get_path(debut, fin);
			gettimeofday(&apres, NULL);


			auto tmp = Timestamp(apres) - Timestamp(avant);
			list_res.push_front(tmp);

			std::cout << "test " << i << " :	temps mis : " << tmp;
			if (verif_path(v, debut, fin, maze) == false)
				std::cout << "\033[1;31m path invalide : " << error_path << "\033[0;m" ;
			std::cout << std::endl;
		}	
		Timestamp total;
		Timestamp min;
		Timestamp max;
		for (auto i : list_res)
		{
			max = (i > max) ? i : max;
			min = (i < min || min == Timestamp()) ? i : min;
			total += i;
		}
		std::cout << std::endl << "moyenne des appels :	" << total/list_res.size() << std::endl;
		std::cout << "le plus rapide :    	" << min << std::endl;
		std::cout << "le plus lent :      	" << max << std::endl;

		/* debut	dechargement	API */
		delete pathfinder;
		delete chargeur_lib;
		/* fin		dechargement	API */
	}
}
