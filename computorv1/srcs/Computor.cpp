/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:46 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 13:18:22 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Computor.hpp"

Computor::Computor(): _type_solution(""), _discriminant(0)
{
}

Computor::Computor(char *argv, int flag_bonus)
{
	Parse::parse_start(argv, flag_bonus);
	if (this->_equation_type >= 0)
		solve_equation();
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
	this->_type_solution = computor._type_solution;
	return (*this);
}

Computor::~Computor()
{
}

void	Computor::print_info(void)
{
	std::cout << CYAN << "Reduced form\t\t: " << BLACK;
	std::cout << this->_equation_str << std::endl;

	std::cout << CYAN << "Polynomial degree\t: " << BLACK;
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
	if (this->_equation_type == TYPE_CONSTANT)
	{
		if (this->_type_solution == SOLUTION_INDETERMINATE)
			std::cout << "The equation is an indeterminate equation: "
				<< "It has infinitely many solutions" << std::endl;
		else
			std::cout << "The equation is an inconsistent equation: "
				<< "It has no solution" << std::endl;
			
	}
	else if (this->_equation_type == TYPE_LINEAR)
	{
		std::cout << CYAN << "The solution is\t\t: " << BLACK;
		std::cout << this->_variable << " = " << this->_solution[0] << std::endl;
	}
	else
	{
		if (this->_type_solution == SOLUTION_TWO)
		{
			std::cout << CYAN << "Discriminant is strictly positive." << std::endl
				<< "The two solutions are\t: " << BLACK;
			std::cout << this->_variable << " = " << this->_solution[0]
				<< ", or " << this->_variable << " = " << this->_solution[1]
				<< std::endl;
		}
		else if (this->_type_solution == SOLUTION_ONE)
		{
			std::cout << CYAN << "Discriminant is zero." << std::endl
				<< "The solution is\t\t: " << BLACK;
			std::cout << this->_variable << " = " << this->_solution[0]
				<< std::endl;
		}
		else
		{
			std::cout << CYAN << "Discriminant is strictly negative." << std::endl
				<< "It has no solution\t: " << BLACK << std::endl;
		}
	}
}

void	Computor::solve_quadratic(void)
{
	float	a = this->_reduced_form[2];
	float	b = this->_reduced_form[1];
	float	c = this->_reduced_form[0];

	this->_discriminant = b * b - 4 * a * c;
	if (this->_discriminant > 0)
	{
		this->_type_solution = SOLUTION_TWO;
		this->_solution.push_back((-1 * b + std::sqrt(this->_discriminant)) / (2 * a));
		this->_solution.push_back((-1 * b - std::sqrt(this->_discriminant)) / (2 * a));
	}
	else if (this->_discriminant == 0)
	{
		this->_type_solution = SOLUTION_ONE;
		this->_solution.push_back(-1 * b / 2 * a);
	}
	else
		this->_type_solution = SOLUTION_ZERO;
}

void	Computor::solve_equation(void)
{
	if (this->_equation_type == TYPE_CONSTANT)
	{
		if (this->_reduced_form[0] == 0)
			this->_type_solution = SOLUTION_INDETERMINATE;
		else
			this->_type_solution = SOLUTION_ZERO;
	}
	else if (this->_equation_type == TYPE_LINEAR)
	{
		float	a = this->_reduced_form[1];
		float	b = this->_reduced_form[0];
		this->_type_solution = SOLUTION_ONE;
		this->_solution.push_back(-1 * b / a);
	}
	else
		solve_quadratic();
}
