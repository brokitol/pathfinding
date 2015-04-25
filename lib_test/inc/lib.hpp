#include "API.hpp"

class Test_API : public API
{
	public :
		Test_API(labi2D maze);
		Test_API(labi3D maze);
		~Test_API();
		std::list<coordonnee>		get_path(coordonnee depart, coordonnee objectif);
};
