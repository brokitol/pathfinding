/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:41:00 by bgauci            #+#    #+#             */
/*   Updated: 2015/05/12 18:54:03 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>

#include "main.hpp"
#include "dlib.hpp"
#include "timestamp.hpp"
#include "chargement_verif.hpp"
#include <sys/time.h>

int main(int argc, char **argv)
{
	if (argc < 5)	{std::cout << "usage : " << argv[0] << " lib nb_test rand_seed maze_dir/*" << std::endl;exit(0);}

	Dlib *								chargeur_lib;
	timeval								avant, apres;
	labi3D								maze3D;
	API *								pathfinder = NULL;
	API *(*pmaker)(labi3D);
	int									nb_test = atoi(argv[2]), x = 0, y = 0, z = 0;
	std::list<Timestamp>				list_res;
	std::minstd_rand0					r(atoi(argv[3]));

	init_maze3D(&maze3D, argv, argc);

/*
	int a = 0, b = 0, c = 0;
	for (auto it : maze3D)
	{
		b = 0;
		for (auto o : it)
		{
			c = 0;
			for (auto t : o)
			{
				if (t == ESCALIER) {std::cout << "a:" << a << " b:" << b << " c:" << c << std::endl;}
				switch (t)
				{
					case LIBRE : std::cout << " ";		break;
					case MUR : std::cout << "X";		break;
					case ESCALIER : std::cout << "E";	break;
					default : std::cout << "?";
				}
				c++;
			}
//			std::cout << std::endl;
			b++;
		}
		a++;
//		std::cout << std::endl;
//		std::cout << std::endl;
	}//*/

	/* debut	chargement		API */
	try	{chargeur_lib = new Dlib(argv[1]); pmaker = chargeur_lib->get_create_pathfinder3D();}
	catch (Exception *e) {std::cerr << "exception : " << e->what() << std::endl; exit(0);}

	gettimeofday(&avant, NULL);
	pathfinder = pmaker(maze3D);
	gettimeofday(&apres, NULL);

	std::cout << "temps d'initialisation de lib : " << Timestamp(apres) - Timestamp(avant) << std::endl; 
	/* fin		chargement		API */

	/* debut	utilisation		API */
	for (int i = 0; i < nb_test; i++)
	{
		int max_z = maze3D.size();
		int max_y = maze3D[0].size();
		int max_x = maze3D[0][0].size();

		do {
			x = r() % max_x;
			y = r() % max_y;
			z = r() % max_z;
		} while (maze3D[z][y][x] == MUR);
		coordonnee const debut(x, y, z);
    
		do {
			x = r() % max_x;
			y = r() % max_y;
			z = r() % max_z;
		} while (maze3D[z][y][x] == MUR);
		coordonnee const fin(x, y, z);

	//	std::cout << "debut [" << debut.x << ", " << debut.y << ", " << debut.z << "] obj [" << fin.x << ", " << fin.y << ", " << fin.z << "]" << std::endl;
		gettimeofday(&avant, NULL);
		auto v = pathfinder->get_path(debut, fin);
		gettimeofday(&apres, NULL);

		auto tmp = Timestamp(apres) - Timestamp(avant);
		list_res.push_front(tmp);

		std::cout << "test " << i << " :	nb_step : " << v.size() << "	temps mis : " << tmp;
		if (verif_path3D(v, debut, fin, maze3D) == false)
			std::cout << "\033[1;31m path invalide : " << error_path << "\033[0;m" ;
		std::cout << std::endl;
	}
	stat(list_res);

	/* debut	dechargement	API */
	delete pathfinder;
	delete chargeur_lib;
	/* fin		dechargement	API */
}
