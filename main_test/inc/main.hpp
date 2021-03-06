/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:40:44 by bgauci            #+#    #+#             */
/*   Updated: 2015/05/10 18:43:06 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <vector>

#include "API.hpp"
#include "timestamp.hpp"

int		main(int argc, char **argv);
void	init_maze2D(std::vector< std::vector< bool > > *maze, std::ifstream *f);
void	init_maze3D(std::vector< std::vector< std::vector< Element > > > *maze, std::ifstream *f);
void	stat(std::list<Timestamp> list_res);

#endif
