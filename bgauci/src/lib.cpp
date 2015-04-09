#include "API.hpp"
#include "lib.hpp"

Dijkstra_Simple::Dijkstra_Simple(labi2D maze)
{
	auto x = maze.size();
	auto y = maze.front().size();

	this->maze = std::vector< std::vector< Dijkstra_Simple::option > >(x, std::vector< Dijkstra_Simple::option >(y, BLOCK));
	for (unsigned long i = 0; i < x ; i++)
	{
		for (unsigned long j = 0; j < y ; j++)
		{
			if (maze[i][j])
				this->maze[i][j] = LIBRE;
			else
				this->maze[i][j] = BLOCK;
		}
	}
//	aff(this->maze);
}

Dijkstra_Simple::~Dijkstra_Simple() {}

std::list<coordonnee>		Dijkstra_Simple::get_path(coordonnee depart, coordonnee objectif)
{
	std::list<situ> lst;
	std::list<situ> suite;

	situ tmp;
	tmp.path.push_back(depart);
	tmp.maze = this->maze;
	tmp.maze[depart.x][depart.y] = FAIT;
	lst.push_back(tmp);

	try
	{
		do {
			for (auto it : lst)
				suite.splice(suite.end(), fonc(it, objectif));
			std::cout << suite.front().path.size() << std::endl;
			lst = suite;
		} while (suite.size() > 0);
	}
	catch(std::list<coordonnee> path) 
	{
		return path;
	}

	std::list<coordonnee> res;
	return res;
}

std::list<situ>				Dijkstra_Simple::fonc(const situ actu, coordonnee objectif)
{
	std::list<situ>	res;
	coordonnee courante = actu.path.front();

	aff(actu.maze);
	// sud
	coordonnee tmp = courante;
	tmp.y += 1;
	if (tmp == objectif)
	{
		situ copy = actu;
		copy.path.push_front(tmp);
		throw copy.path;
	}
	if (actu.maze[tmp.x][tmp.y] == LIBRE)
	{
		situ copy = actu;
		copy.maze[tmp.x][tmp.y] = FAIT;
		copy.path.push_front(tmp);
		res.push_front(copy);
	}
	else
	{
		//std::cout << "SUD non" << std::endl;
	}
	// est
	tmp = courante;
	tmp.x -= 1;
	if (tmp == objectif)
	{
		situ copy = actu;
		copy.path.push_front(tmp);
		throw copy.path;
	}
	if (actu.maze[tmp.x][tmp.y] == LIBRE)
	{
		situ copy = actu;
		copy.maze[tmp.x][tmp.y] = FAIT;
		copy.path.push_front(tmp);
		res.push_front(copy);
	}
	else
	{
		//std::cout << "EST non" << std::endl;
	}
	// nord
	tmp = courante;
	tmp.y -= 1;
	if (tmp == objectif)
	{
		situ copy = actu;
		copy.path.push_front(tmp);
		throw copy.path;
	}
	if (actu.maze[tmp.x][tmp.y] == LIBRE)
	{
		situ copy = actu;
		copy.maze[tmp.x][tmp.y] = FAIT;
		copy.path.push_front(tmp);
		res.push_front(copy);
	}
	else
	{
		//std::cout << "NORD non" << std::endl;
	}
	// ouest
	tmp = courante;
	tmp.x += 1;
	if (tmp == objectif)
	{
		situ copy = actu;
		copy.path.push_front(tmp);
		throw copy.path;
	}
	if (actu.maze[tmp.x][tmp.y] == LIBRE)
	{
		situ copy = actu;
		copy.maze[tmp.x][tmp.y] = FAIT;
		copy.path.push_front(tmp);
		res.push_front(copy);
	}

	return res;
}

void	Dijkstra_Simple::aff(std::vector< std::vector< Dijkstra_Simple::option > > map)
{
	for (auto it : map)
	{
		for (auto o : it)
		{
			switch (o)
			{
				case LIBRE : std::cout << " ";	break;
				case FAIT : std::cout << ".";	break;
				case BLOCK : std::cout << "X";	break;
				default : std::cout << "?";
			}
		}
		std::cout << std::endl;
	}
}

extern "C"
{
	API* create_pathfinder2D(labi2D maze)
	{
		return new Dijkstra_Simple(maze);
	}
}
