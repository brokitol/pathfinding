/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 21:29:30 by bgauci            #+#    #+#             */
/*   Updated: 2015/04/25 14:32:17 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include <sys/time.h>
#include <string>

class Timestamp
{
	private :
		int	sec = 0;
		int	ms = 0;
		int	us = 0;

	public :
		Timestamp() {};
		Timestamp(timeval actu);
		~Timestamp() {};

		Timestamp &		operator+(Timestamp const &x) const;
		Timestamp &		operator+=(Timestamp const &x);
		Timestamp &		operator-(Timestamp const &x) const;
		Timestamp &		operator/(int const &x) const;
		bool			operator<(Timestamp const &x) const;
		bool			operator>(Timestamp const &x) const;
		bool			operator==(Timestamp const &x) const;

		std::string		to_string() const;
};

std::ostream & operator<<( std::ostream & o, Timestamp const & rhs);

#endif
