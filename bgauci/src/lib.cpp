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
	tmp.path.push_front(depart);
	tmp.maze = this->maze;
	tmp.maze[depart.x][depart.y] = FAIT;
	lst.push_back(tmp);

	try
	{
		do {
			suite.clear();
			for (auto it : lst)
				suite.splice(suite.end(), fonc(it, objectif));
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

void						Dijkstra_Simple::decoupage(const situ *actu, coordonnee const objectif, coordonnee *tmp, std::list<situ> *res)
{
	if (*tmp == objectif)
	{
		situ copy = *actu;
		copy.path.push_back(*tmp);
		aff(copy.maze);
		throw copy.path;
	}
	if (actu->maze[tmp->x][tmp->y] == LIBRE)
	{
		situ copy = *actu;
		copy.maze[tmp->x][tmp->y] = FAIT;
		copy.path.push_back(*tmp);
		res->push_front(copy);
	}
}
std::list<situ>				Dijkstra_Simple::fonc(const situ actu, coordonnee const objectif)
{
	std::list<situ>	res;
	coordonnee courante = actu.path.back();

	// sud
	coordonnee tmp = courante;
	tmp.y += 1;
	decoupage(&actu, objectif, &tmp, &res);

	// est
	tmp = courante;
	tmp.x -= 1;
	decoupage(&actu, objectif, &tmp, &res);
	// nord
	tmp = courante;
	tmp.y -= 1;
	decoupage(&actu, objectif, &tmp, &res);
	// ouest
	tmp = courante;
	tmp.x += 1;
	decoupage(&actu, objectif, &tmp, &res);

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
				case FAIT :
					std::cout << "\033[1;32mX\033[0;m";
					break;
				case BLOCK : std::cout << ".";	break;
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
