#include "API.hpp"
#include "lib.hpp"

Test_API::Test_API(labi2D maze) {maze[0][0] = false;}
Test_API::Test_API(labi3D maze) {maze[0][0][0] = Element::MUR;}
Test_API::~Test_API() {}

std::list<coordonnee>		Test_API::get_path(coordonnee depart, coordonnee objectif)
{
	std::list<coordonnee> v;
	v.push_back(depart);
	v.push_back(coordonnee(4,5));
	v.push_back(objectif);

	return v;
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
