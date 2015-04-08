#include "API.hpp"
#include "lib.hpp"

Dijkstra_Simple::Dijkstra_Simple(labi2D maze)
{
	this->maze.resize(maze.size());
	for (unsigned long i = 0; i < maze.size() ; i++)
	{
		this->maze[i].resize(maze[i].size());
		for (unsigned long j = 0; j < maze[i].size() ; j++)
			this->maze[i][j] = (maze[i][j]) ? LIBRE : BLOCK ;
	}
}

Dijkstra_Simple::~Dijkstra_Simple() {}

std::vector<coordonnee>		Dijkstra_Simple::get_path(coordonnee depart, coordonnee objectif)
{
	std::list<situ> lst;
	std::list<situ> suite;

	situ tmp;
	tmp.path.push_back(depart);
	tmp.maze = this->maze;
	lst.push_back(tmp);

	do {
		for (auto it : lst)
			suite.splice (suite.end(), fonc(it));
	} while (suite.size() > 0);

	std::vector<coordonnee> v;
	v.push_back(depart);
	v.push_back(coordonnee(4,5));
	v.push_back(objectif);

	return v;
}
/*
std::vector<coordonnee>		Test_API::get_path(coordonnee depart, coordonnee objectif)
{
	std::vector<coordonnee> v;
	v.push_back(depart);
	v.push_back(coordonnee(4,5));
	v.push_back(objectif);

	return v;
}
*/
extern "C"
{
	API* create_pathfinder2D(labi2D maze)
	{
		return new Dijkstra_Simple(maze);
	}
}


/*
 *
 * lst fonc (situ)
 *
 * prend situ en param, retourn une list de situ avec un saut de plus
 *
 *
 */
