/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chargement_verif.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 18:43:43 by bgauci            #+#    #+#             */
/*   Updated: 2015/05/12 17:11:27 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chargement_verif.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>

#include "main.hpp"
#include "dlib.hpp"
#include "timestamp.hpp"
#include <sys/time.h>

std::string error_path;

void init_maze2D(std::vector< std::vector< bool > > *maze, std::string s)
{
	std::ifstream	f;
	f.open (s, std::ifstream::in);
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
		maze->push_back(tmp);
	}
}

void init_maze3D(std::vector< std::vector< std::vector< Element > > > *maze, char ** argv, int argc)
{
	for (int i = 4 ; i < argc ; i++)// pour chaque fichier
	{
		std::ifstream	f;
		f.open (argv[i], std::ifstream::in);

		std::vector< std::vector < Element > >	tmp;
		for (std::string s; getline(f,s);) // pour chaque ligne
		{
			std::vector<Element>	tmp2;
			for (char c : s) // pour chaque caractere
			{
				if (c == ' ')
					tmp2.push_back(LIBRE);
				else if (c == 'E')
					tmp2.push_back(ESCALIER);
				else
					tmp2.push_back(MUR);
			}
			tmp.push_back(tmp2);
		}
		maze->push_back(tmp);
	}
}

bool verif_path2D(std::list<coordonnee> const path, coordonnee const debut, coordonnee const fin, labi2D const maze)
{
	if (path.front() != debut) {error_path = "point de depart invalide";return false;}
	if (path.back() != fin) {error_path = "point de fin invalide";return false;}
	auto a = path.begin();
	auto b = path.begin();
	b++;
	while (a != path.end() and b != path.end())
	{
		if (maze[a->x][a->y] == false) {std::stringstream ss; ss << "point a("<<a->x<<","<<a->y<<") invalide";error_path = ss.str();return false;}
		if (maze[b->x][b->y] == false) {std::stringstream ss; ss << "point b("<<b->x<<","<<b->y<<") invalide";error_path = ss.str();return false;}
		if ((a->x != b->x and a->y != b->y) or ((a->x != b->x or a->y != b->y) and a->z != b->z)) {std::stringstream ss; ss << "passage entre a("<<a->x<<","<<a->y<<") et b("<<b->x<<","<<b->y<<") impossible  invalide";error_path = ss.str();return false;}
		a++;
		b++;
	}
	if (path.size() > 2)
		return true;
	return false;
}

bool verif_path3D(std::list<coordonnee> const path, coordonnee const debut, coordonnee const fin, labi3D const maze)
{
	if (path.front() != debut) {error_path = "point de depart invalide";return false;}
	if (path.back() != fin) {error_path = "point de fin invalide";return false;}
	auto a = path.begin();
	auto b = path.begin();
	b++;
	while (a != path.end() and b != path.end())
	{
		if (maze[a->z][a->y][a->x] == MUR) {std::stringstream ss; ss << "point a(x:"<<a->x<<",y:"<<a->y<<",z:"<<a->z<<") invalide";error_path = ss.str();return false;}
		if (maze[b->z][b->y][b->x] == MUR) {std::stringstream ss; ss << "point b(x:"<<b->x<<",y:"<<b->y<<",z:"<<b->z<<") invalide";error_path = ss.str();return false;}
		if ((a->x != b->x and a->y != b->y) or ((a->x != b->x or a->y != b->y) and a->z != b->z)) {std::stringstream ss; ss << "passage entre a(x:"<<a->x<<",y:"<<a->y<<",z:"<<a->z<<") et b(x:"<<b->x<<",y:"<<b->y<<",z:"<<b->z<<") impossible";error_path = ss.str();return false;}
		a++;
		b++;
	}
	if (path.size() > 2)
		return true;
	return false;
}

void	stat(std::list<Timestamp> list_res)
{
	Timestamp total, min, max;
	for (auto i : list_res)
	{
		max = (i > max) ? i : max;
		min = (i < min || min == Timestamp()) ? i : min;
		total += i;
	}
	std::cout << std::endl << "moyenne des appels :	" << total/list_res.size() << std::endl;
	std::cout << "le plus rapide :    	" << min << std::endl;
	std::cout << "le plus lent :      	" << max << std::endl;
}
