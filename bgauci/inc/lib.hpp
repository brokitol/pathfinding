#include "API.hpp"

struct situ;

class Dijkstra_Simple : public API
{
	public :
		enum option {LIBRE, FAIT, BLOCK};
		std::vector< std::vector< option > > maze;

	public :
		Dijkstra_Simple(labi2D maze);
		~Dijkstra_Simple();
		std::list<coordonnee>		get_path(coordonnee depart, coordonnee objectif);

	private :
		void						decoupage(const situ *actu, coordonnee const objectif, coordonnee *tmp, std::list<situ> *res);
		std::list<situ> 			fonc(const situ actu, coordonnee const objectif);
		void						aff(std::vector< std::vector< Dijkstra_Simple::option > > map);
};

struct situ
{
	std::vector< std::vector< Dijkstra_Simple::option > > maze;
	std::list< coordonnee > path;
};
