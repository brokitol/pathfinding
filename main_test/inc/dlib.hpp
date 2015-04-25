/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlib.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:40:42 by bgauci            #+#    #+#             */
/*   Updated: 2015/04/25 13:40:43 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIB_HPP
#define DLIB_HPP

#include <string>
#include "API.hpp"

typedef API *(*pointeurToCreate2D)(labi2D);
typedef API *(*pointeurToCreate3D)(labi3D);

class Dlib
{
	private :
		void *	hndl = NULL;

	public :
		Dlib(char * path);
		~Dlib();
		pointeurToCreate2D get_create_pathfinder2D();
		pointeurToCreate3D get_create_pathfinder3D();
};

class Exception : public std::exception
{
	private :
		std::string s;

	public :
		Exception(std::string s) {this->s = s;};
		~Exception() {};
		virtual const char *	what() const throw() {return s.c_str();};
};

#endif
