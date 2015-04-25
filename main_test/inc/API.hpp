/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:40:36 by bgauci            #+#    #+#             */
/*   Updated: 2015/04/25 13:40:40 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_HPP
#define API_HPP

#include <list>
#include <vector>
#include <iostream>

struct coordonnee
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int z = 0;

	coordonnee(unsigned int x = 0, unsigned int y = 0, unsigned int z = 0): x(x), y(y), z(z) {};
	bool	operator==(const coordonnee & val) {return (this->x == val.x && this->y == val.y) ? true : false;}
};

enum Element {LIBRE, MUR, ESCALIER};

typedef std::vector< std::vector< bool > > labi2D;
typedef std::vector< std::vector< std::vector< Element > > > labi3D;

/*
 * la liste de coordonnee retourner par get_path doit commencer par le point de depart et finir par le point d'objectif.
 */

class API
{
	public :
		virtual ~API() {};
		virtual std::list<coordonnee>		get_path(coordonnee depart, coordonnee objectif) = 0;
};

extern "C"
{
	API* create_pathfinder2D(labi2D maze);
	API* create_pathfinder3D(labi3D maze);
}

#endif
