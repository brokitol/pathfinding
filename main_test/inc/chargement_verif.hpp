/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chargement_verif.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 18:44:08 by bgauci            #+#    #+#             */
/*   Updated: 2015/05/10 19:50:07 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARGEMENT_VERIF_HPP
#define CHARGEMENT_VERIF_HPP

#include <string>
#include <vector>

#include "API.hpp"
#include "timestamp.hpp"

extern std::string error_path;

void	init_maze2D(labi2D *maze, std::string s);
void	init_maze3D(labi3D *maze, char ** argv, int argc);
bool	verif_path2D(std::list<coordonnee> const path, coordonnee const debut, coordonnee const fin, labi2D const maze);
bool	verif_path3D(std::list<coordonnee> const path, coordonnee const debut, coordonnee const fin, labi3D const maze);
void	stat(std::list<Timestamp> list_res);

#endif
