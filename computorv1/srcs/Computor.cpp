/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:46 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 09:53:08 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Computor.hpp"

Computor::Computor()
{
}

Computor::Computor(char *argv, int flag_bonus)
{
	Parse::parse_start(argv, flag_bonus);
}

Computor::Computor(const Computor& computor): Parse(computor)
{
	*this = computor;
}

Computor& Computor::operator=(const Computor& computor)
{
	if (this == &computor)
		return (*this);
	Parse::operator=(computor);
	return (*this);
}

Computor::~Computor()
{
}

void	Computor::print_info(void)
{
	std::cout << CYAN << "Reduced form: " << BLACK;
	std::cout << this->_equation_str << std::endl;

	std::cout << CYAN << "Polynomial degree: " << BLACK;
	if (this->_equation_type == TYPE_FRACTIONAL)
	{
		std::cout << "The equation is fractional equation." << std::endl;
		std::cout << YELLOW << "The equation is not a polynomial equation, I can't solve."
			<< BLACK << std::endl;
		return ;
	}
	std::cout << this->_max_degree << std::endl;
	if (this->_equation_type == TYPE_HIGH_DEGREE)
	{
		std::cout << YELLOW <<
			"The polynomial degree is strictly greater than 2, I can't solve."
			<< BLACK << std::endl;
		return ;
	}
}
