/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgauci <bgauci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 13:40:18 by bgauci            #+#    #+#             */
/*   Updated: 2015/04/25 14:53:57 by bgauci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timestamp.hpp"
#include <sstream>

Timestamp::Timestamp(timeval actu)
{
	sec = actu.tv_sec;
	ms = actu.tv_usec / 1000;
	us = actu.tv_usec - ms * 1000;
}

std::string		Timestamp::to_string() const
{
	std::stringstream	ss;
	ss << sec << "s, " << ms << "ms, " << us << "us";
	return ss.str();
}

Timestamp &		Timestamp::operator+(Timestamp const &x) const
{
	Timestamp *	res = new Timestamp();

	res->us = this->us + x.us;
	res->ms += this->ms + x.ms;
	res->sec += this->sec + x.sec;
	while (res->us > 1000)	{res->us -= 1000;res->ms += 1;}
	while (res->ms > 1000)	{res->ms -= 1000;res->sec += 1;}

	return *res;
}

Timestamp &		Timestamp::operator+=(Timestamp const &x)
{
	us += x.us;
	ms += x.ms;
	sec += x.sec;
	while (us > 1000)	{us -= 1000;ms += 1;}
	while (ms > 1000)	{ms -= 1000;sec += 1;}

	return *this;
}

Timestamp &		Timestamp::operator-(Timestamp const &x) const
{
	Timestamp *	res = new Timestamp();

	res->sec = this->sec - x.sec;
	res->ms = this->ms - x.ms;
	res->us = this->us - x.us;
	while (res->us > 1000)						{res->us -= 1000;res->ms += 1;}
	while (res->ms > 1000)						{res->ms -= 1000;res->sec += 1;}
	while (res->ms < 0 and res->sec > 0)	{res->ms += 1000;res->sec -= 1;}
	while (res->ms > 0 and res->sec < 0)	{res->ms -= 1000;res->sec += 1;}
	while (res->us < 0 and res->ms > 0)		{res->us += 1000;res->ms -= 1;}
	while (res->us > 0 and res->ms < 0)		{res->us -= 1000;res->ms += 1;}

	return *res;
}

Timestamp &		Timestamp::operator/(int const &x) const
{
	Timestamp *	res = new Timestamp();

	res->sec = this->sec / x;
	res->ms = this->ms / x;
	res->us = this->us / x;
	if (this->sec % x != 0)
	{
		int tmp = (this->sec % x)* 1000;
		res->ms += tmp / x;
		if (tmp % x != 0)
		{
			int tmp2 = (tmp % x) * 1000;
			res->us += tmp2 / x;
		}
	}
	if (this->ms % x != 0)
		res->us += ((this->ms % x) * 1000) / x;

	return *res;
}

bool			Timestamp::operator<(Timestamp const &x) const
{
	if (this->sec < x.sec) {return true;}
	else if (this->sec > x.sec) {return false;}
	if (this->ms < x.ms) {return true;}
	else if (this->ms > x.ms) {return false;}
	if (this->us < x.us) {return true;}
	else if (this->us > x.us) {return false;}

	return false;
}

bool			Timestamp::operator>(Timestamp const &x) const
{
	if (this->sec > x.sec) {return true;}
	else if (this->sec < x.sec) {return false;}
	if (this->ms > x.ms) {return true;}
	else if (this->ms < x.ms) {return false;}
	if (this->us > x.us) {return true;}
	else if (this->us < x.us) {return false;}

	return false;
}

bool			Timestamp::operator==(Timestamp const &x) const
{
	if (this->sec != x.sec) {return false;}
	if (this->ms != x.ms) {return false;}
	if (this->us != x.us) {return false;}

	return true;
}

std::ostream &	operator<<( std::ostream & o, Timestamp const & rhs)
{
	o << rhs.to_string();
	return o;
}
