#ifndef MDARTY_API
#define MDARTY_API

#include "API.hpp"

class Mdarty_API : public API
{
	public :
		Mdarty_API();
		~Mdarty_API();
		std::list<coordonnee>		get_path(coordonnee depart, coordonnee objectif);
};

#endif
