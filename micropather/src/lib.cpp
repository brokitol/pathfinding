#include "API.hpp"
#include "lib.hpp"

Test_API::Test_API(labi2D maze) : maze(maze)
{
	mode = l2D;
	labi2D *	mymaze = this->maze.l2;
	max_y = mymaze->size();
	max_x = (*mymaze)[0].size();

	//std::cout << "map [x:"<< max_x << ", y:" << max_y << "]" << std::endl;
}
Test_API::Test_API(labi3D maze) : maze(maze)
{
	labi3D *	mymaze = this->maze.l3;
	mode = l3D;
	max_z = mymaze->size();
	max_y = (*mymaze)[0].size();
	max_x = (*mymaze)[0][0].size();

	std::cout << "map [z:"<< max_z << ", y:" << max_y << ", x:" << max_x << "]" << std::endl;
}

Test_API::~Test_API() {}

std::list<coordonnee>		Test_API::get_path(coordonnee depart, coordonnee objectif)
{
	//std::cout << "get_path in" << std::endl;
	micropather::MicroPather pather( this );

	std::vector< void* > path;
	std::list<coordonnee> v;
	float totalCost;

	//std::cout << "slove in : depart [" << depart.x << ", " << depart.y << ", " << depart.z << "] obj [" << objectif.x << ", " << objectif.y << ", " << objectif.z << "]" << std::endl;
	auto toto = pather.Solve( get_state(depart.x, depart.y, depart.z), get_state(objectif.x, objectif.y, objectif.z), &path, &totalCost );
	//std::cout << "slove out ";
	if (toto == micropather::MicroPather::NO_SOLUTION) {return v;}
	//std::cout << std::endl;
	
	v.push_back(depart);
	for (auto it : path)
	{
		int x, y, z;
		get_pos(it, &x, &y, &z);	
		//std::cout << "x : " << x << " | y : " << y << " | z : " << z << std::endl;
		v.push_back(coordonnee(x, y, z));
	}
	v.push_back(objectif);
	//std::cout << "get_path out" << std::endl;

	return v;
}

void *	Test_API::get_state(int x, int y, int z)
{
	//std::cout << "x:" << x << " y:" << y << " z:" << z << " :" << (x + y * max_x + z * max_x * max_y) << std::endl;
	if (mode == l2D)
		return (void *) (long) (x + y * max_x);
	if (mode == l3D)
		return (void *) (long) (x + y * max_x + z * max_x * max_y);
	return NULL;
}

void	Test_API::get_pos(void * state, int *x, int *y, int *z)
{
	long s = (long) state;
	//std::cout << "state : " << s;
	if (mode == l3D)
	{
		*z = s / (max_x * max_y);
		s = s % (max_x * max_y);
	}
	else
		*z = 0;
	*y = s / max_x;
	s = s % max_x;
	*x = s;
	//std::cout << " x : " << *x << " | y : " << *y << " | z : " << *z << std::endl;
}

float	Test_API::LeastCostEstimate(void * stateStart, void * stateEnd)
{
/*	//std::cout << "LeastCostEstimate in" << std::endl;
	int x1, y1, z1;
	get_pos(stateStart, &x1, &y1, &z1);
	int x2, y2, z2;
	get_pos(stateEnd, &x2, &y2, &z2);
	auto res = std::abs(x1 - x2);
	res += std::abs(y1 - y2);
	res += std::abs(z1 - z2) * max_x;
	//std::cout << "LeastCostEstimate out" << std::endl;
	return res;*/
	stateStart = stateEnd;
	stateEnd = NULL;
	return 10000;
}

void	Test_API::AdjacentCost(void * state, std::vector< micropather::StateCost > *adjacent)
{
	//std::cout << "AdjacentCost in" << std::endl;
	int x, y, z;
	get_pos(state, &x, &y, &z);
	//std::cout << "AdjacentCost if in" << std::endl;
	if (mode == l2D)
	{
		if (x - 1 >= 0 and (*maze.l2)[x - 1][y] == true) {micropather::StateCost s; s.state = get_state(x - 1, y, 0); s.cost = 1; adjacent->push_back(s);}
		if (x + 1 < max_x and (*maze.l2)[x + 1][y] == true) {micropather::StateCost s; s.state = get_state(x + 1, y, 0); s.cost = 1; adjacent->push_back(s);}
		if (y + 1 < max_y and (*maze.l2)[x][y + 1] == true) {micropather::StateCost s; s.state = get_state(x, y + 1, 0); s.cost = 1; adjacent->push_back(s);}
		if (y - 1 >= 0 and (*maze.l2)[x][y - 1] == true) {micropather::StateCost s; s.state = get_state(x, y - 1, 0); s.cost = 1; adjacent->push_back(s);}
	}
	else if (mode == l3D)
	{
		if (x - 1 >= 0		and ((*maze.l3)[z][y][x-1] == LIBRE or (*maze.l3)[z][y][x-1] == ESCALIER)) {adjacent->push_back(micropather::StateCost(get_state(x-1, y, z), 1));}
		if (x + 1 < max_x	and ((*maze.l3)[z][y][x+1] == LIBRE or (*maze.l3)[z][y][x+1] == ESCALIER)) {adjacent->push_back(micropather::StateCost(get_state(x+1, y, z), 1));}
		if (y + 1 < max_y	and ((*maze.l3)[z][y+1][x] == LIBRE or (*maze.l3)[z][y+1][x] == ESCALIER)) {adjacent->push_back(micropather::StateCost(get_state(x, y+1, z), 1));}
		if (y - 1 >= 0		and ((*maze.l3)[z][y-1][x] == LIBRE or (*maze.l3)[z][y-1][x] == ESCALIER)) {adjacent->push_back(micropather::StateCost(get_state(x, y-1, z), 1));}
		if (z + 1 < max_z	and (*maze.l3)[z+1][y][x] == ESCALIER and (*maze.l3)[z][y][x] == ESCALIER) {adjacent->push_back(micropather::StateCost(get_state(x, y, z+1), 1));}
		if (z - 1 >= 0		and (*maze.l3)[z-1][y][x] == ESCALIER and (*maze.l3)[z][y][x] == ESCALIER) {adjacent->push_back(micropather::StateCost(get_state(x, y, z-1), 1));}
	}
	//std::cout << "AdjacentCost if out " << adjacent->size() << std::endl;
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
