/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlib.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:40:53 by bgauci            #+#    #+#             */
/*   Updated: 2015/04/25 13:40:55 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlib.hpp"
#include <dlfcn.h>

Dlib::Dlib(char * path)
{
	if((hndl = dlopen(path, RTLD_LOCAL)) == NULL)
		throw new Exception(std::string("constructeur Dlib : ") + dlerror());
}
Dlib::~Dlib() {dlclose(hndl);}

pointeurToCreate2D	Dlib::get_create_pathfinder2D()
{
	void *	mkr = NULL;
	pointeurToCreate2D pmaker = NULL;

	if ((mkr = dlsym(hndl, "create_pathfinder2D")) == NULL)
		throw new Exception(std::string("Dlib::get_create_pathfinder2D : ") + dlerror());
	if ((pmaker = reinterpret_cast<API *(*)(labi2D)>(mkr)) == NULL)
		throw new Exception("Dlib::get_create_pathfinder2D : erreur de cast, librairie invalide");

	return pmaker;
}

pointeurToCreate3D	Dlib::get_create_pathfinder3D()
{
	void *	mkr = NULL;
	pointeurToCreate3D pmaker = NULL;

	if ((mkr = dlsym(hndl, "create_pathfinder3D")) == NULL)
		throw new Exception(std::string("Dlib::get_create_pathfinder2D : ") + dlerror());
	if ((pmaker = reinterpret_cast<API *(*)(labi3D)>(mkr)) == NULL)
		throw new Exception("Dlib::get_create_pathfinder2D : erreur de cast, librairie invalide");

	return pmaker;
}
