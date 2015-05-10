#include "API.hpp"
#include "micropather.h"

union lab {
	labi2D *l2;
	labi3D *l3;

	lab(labi2D maze) {l2 = new labi2D(maze);}
	lab(labi3D maze) {l3 = new labi3D(maze);}
	~lab() {}
};

enum type_laby {l2D, l3D};

class Test_API : public API, public micropather::Graph
{
	private :
		enum type_laby	mode;
		lab maze;
		int	max_x; // nombre de case en x
		int	max_y; // nombre de case en y
		int	max_z; // nombre de case en z

	public :
		Test_API(labi2D maze);
		Test_API(labi3D maze);
		~Test_API();
		std::list<coordonnee>		get_path(coordonnee depart, coordonnee objectif);

		/**
			Return the least possible cost between 2 states. For example, if your pathfinding is based on distance, this is simply the straight distance between 2 points on the 
			map. If you pathfinding is based on minimum time, it is the minimal travel time between 2 points given the best possible terrain.
		*/
		float LeastCostEstimate( void* stateStart, void* stateEnd );

		/** 
			Return the exact cost from the given state to all its neighboring states. This may be called multiple times, or cached by the solver. It *must* return the same
			exact values for every call to MicroPather::Solve(). It should generally be a simple, fast function with no callbacks into the pather.
		*/	
		void AdjacentCost( void* state, std::vector< micropather::StateCost > *adjacent );

		/**
			This function is only used in DEBUG mode - it dumps output to stdout. Since void* aren't really human readable,
			normally you print out some concise info (like "(1,2)") without an ending newline.
		*/
		void  PrintStateInfo( void* state );

	private :
		void *	get_state(int x, int y, int z);
		void	get_pos(void * state, int *x, int *y, int *z);
};
