#include "API.hpp"
#include "lib.hpp"

Mdarty_API::Mdarty_API() {}
Mdarty_API::~Mdarty_API()
{
	// appel a la fonction qui free tout les mallocs fait pour le pathfinding.
	// apres cette fonction, le pathfinding est inutilisable.
	// fonctionFree();
}

std::list<coordonnee>		Mdarty_API::get_path(coordonnee depart, coordonnee objectif)
{
	// appel a la fonction qui trouvent le chemin et retourne la list de coordonnee
	// return fonctionPathFinding();
}

extern "C"
{
	API* create_pathfinder2D(labi2D maze)
	{
		// appel a la fonction d'initialisation pour un laby 2D
		// fonction2D(maze);
		return new Mdarty_API();
	}

	API* create_pathfinder3D(labi3D maze)
	{
		// appel a la fonction d'initialisation pour un laby 2D
		// fonction3D(maze);
		return new Mdarty_API();
	}
}
