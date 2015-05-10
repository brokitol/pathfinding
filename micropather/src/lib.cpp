#include "API.hpp"
#include "lib.hpp"

Test_API::Test_API(labi2D maze) : maze(maze)
{
	mode = l2D;
	max_x = this->maze.l2->size();
	max_y = this->maze.l2[0].size();

	//std::cout << "map ["<< max_x << ", " << max_y << "]" << std::endl;
}
Test_API::Test_API(labi3D maze) : maze(maze)
{
	mode = l3D;
	max_x = this->maze.l3->size();
	max_y = this->maze.l3[0].size();
	max_z = this->maze.l3[0][0].size();
}

Test_API::~Test_API() {}

std::list<coordonnee>		Test_API::get_path(coordonnee depart, coordonnee objectif)
{
//	std::list<coordonnee> v;
//	v.push_back(depart);
//	v.push_back(coordonnee(4,5));
//	v.push_back(objectif);
	//std::cout << "get_path in" << std::endl;
	micropather::MicroPather pather( this );

	std::vector< void* > path;
	float totalCost;

	//std::cout << "slove in : depart [" << depart.x << ", " << depart.y << ", " << depart.z << "] obj [" << objectif.x << ", " << objectif.y << ", " << objectif.z << "]" << std::endl;
	pather.Solve( get_state(depart.x, depart.y, depart.z), get_state(objectif.x, objectif.y, objectif.z), &path, &totalCost );
	//std::cout << "slove out" << std::endl;
	
	std::list<coordonnee> v;
	v.push_back(depart);
	for (auto it : path)
	{
		int x, y, z;
		get_pos(it, &x, &y, &z);	
		//std::cout << "x : " << x << " | y : " << y << " | z : " << z << std::endl;
		v.push_back(coordonnee(x, y));
	}
	v.push_back(objectif);
	//std::cout << "get_path out" << std::endl;

	return v;
}

void *	Test_API::get_state(int x, int y, int z)
{
	if (mode == l2D)
		return (void *) (long) (x + y * max_x);
	if (mode == l3D)
		return (void *) (long) (x + y * max_x + z + max_x * max_y);
	return NULL;
}

void	Test_API::get_pos(void * state, int *x, int *y, int *z)
{
	int s = (int) (long) state;
	if (mode == l3D)
	{
	*z = s / (max_x * max_y);
	s -= s % (max_x * max_y);
	}
	else
		*z = 0;
	*y = s / max_x;
	s = s % max_x;
	*x = s;
	//std::cout << "x : " << *x << " | y : " << *y << " | z : " << *z << std::endl;
}

float	Test_API::LeastCostEstimate(void * stateStart, void * stateEnd)
{
	//std::cout << "LeastCostEstimate in" << std::endl;
	int x1, y1, z1;
	get_pos(stateStart, &x1, &y1, &z1);
	int x2, y2, z2;
	get_pos(stateEnd, &x2, &y2, &z2);
	auto res = std::abs(x1 - x2);
	res += std::abs(y1 - y2);
	res += std::abs(z1 - z2);
	//std::cout << "LeastCostEstimate out" << std::endl;
	return res;
}

void	Test_API::AdjacentCost(void * state, std::vector< micropather::StateCost > *adjacent)
{
	//std::cout << "AdjacentCost in" << std::endl;
	int x, y, z;
	get_pos(state, &x, &y, &z);
	//std::cout << "AdjacentCost if 1 " << x << " " << y << std::endl;
	//std::cout << "AdjacentCost if in" << std::endl;
	if (mode == l2D)
	{
		//std::cout << "AdjacentCost if 1 " << x << " " << y << std::endl;
		if (x - 1 >= 0 and (*maze.l2)[x - 1][y] == true) {micropather::StateCost s; s.state = get_state(x - 1, y, 0); s.cost = 1; adjacent->push_back(s);}
		//std::cout << "AdjacentCost if 2" << std::endl;
		if (x + 1 < max_x and (*maze.l2)[x + 1][y] == true) {micropather::StateCost s; s.state = get_state(x + 1, y, 0); s.cost = 1; adjacent->push_back(s);}
		//std::cout << "AdjacentCost if 3" << std::endl;
		if (y + 1 < max_y and (*maze.l2)[x][y + 1] == true) {micropather::StateCost s; s.state = get_state(x, y + 1, 0); s.cost = 1; adjacent->push_back(s);}
		//std::cout << "AdjacentCost if 4" << std::endl;
		if (y - 1 >= 0 and (*maze.l2)[x][y - 1] == true) {micropather::StateCost s; s.state = get_state(x, y - 1, 0); s.cost = 1; adjacent->push_back(s);}
	}
	//std::cout << "AdjacentCost if out" << std::endl;
	//std::cout << "AdjacentCost out" << std::endl;
}

void	Test_API::PrintStateInfo(void * state)
{
	int x, y, z;
	get_pos(state, &x, &y, &z);
	//std::cout << " x : " << x << " | y : " << y << " | z : " << z;
}

extern "C"
{
	API* create_pathfinder2D(labi2D maze)
	{
		return new Test_API(maze);
	}

	API* create_pathfinder3D(labi3D maze)
	{
		return new Test_API(maze);
	}
}
