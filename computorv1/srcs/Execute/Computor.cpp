/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:46 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 00:18:27 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Execute/Computor.hpp"

Computor::Computor()
{
}

Computor::Computor(t_parse info): _info(info)
{
	if (this->_info.equation_type >= 0)
	{
		this->_term_descending_order = this->_info.reduced_form;
		if (this->_term_descending_order[this->_term_descending_order.size() - 1] < 0)
		{
			for (size_t i = 0; i < this->_term_descending_order.size(); i++)
				this->_term_descending_order[i] *= -1;
		}
	}
	print_info();
}

Computor::Computor(const Computor& computor)
{
	*this = computor;
}

Computor& Computor::operator=(const Computor& computor)
{
	if (this == &computor)
		return (*this);
	this->_info = computor._info;
	this->_term_descending_order = computor._term_descending_order;
	this->_solution = computor._solution;
	this->_str_solution = computor._str_solution;
	return (*this);
}

Computor::~Computor()
{
}

void	Computor::print_info(void)
{
	std::cout << CYAN << "Reduced form\t\t: " << BLACK;
	std::cout << this->_info.equation_str << std::endl;
	if (this->_info.equation_type == TYPE_ZERO)
		return ;

	std::cout << CYAN << "Polynomial degree\t: " << BLACK;
	if (this->_info.equation_type == TYPE_FRACTIONAL)
	{
		std::cout << "The equation is fractional equation." << std::endl;
		std::cout << YELLOW << "The equation is not a polynomial equation, I can't solve."
			<< BLACK << std::endl;
		return ;
	}
	std::cout << this->_info.max_degree << std::endl;
	if (this->_info.equation_type == TYPE_HIGH_DEGREE)
	{
		std::cout << YELLOW <<
			"The polynomial degree is strictly greater than 2, I can't solve."
			<< BLACK << std::endl;
		return ;
	}
}

void	Computor::solve(void)
{
	solve_equation();
}

void	Computor::solve_equation(void)
{
	if (this->_info.equation_type == TYPE_ZERO)
	{
		if (this->_info.reduced_form[0] == 0)
		{
			std::cout << CYAN
				<< "The equation is an indeterminate equation:" << std::endl
				<< BLACK
				<< "It has infinitely many solutions(any real number is a solution)"
				<< std::endl;
		}
		else
		{
			std::cout << CYAN
				<< "The equation is an inconsistent equation:" << std::endl
				<< BLACK
				<< "It has no solution"
				<< std::endl;
		}
	}
	else if (this->_info.equation_type == TYPE_LINEAR)
	{
		LinerEquationSolver	solver(this->_info,
						this->_term_descending_order[1],
						this->_term_descending_order[0]);
		solver.solve();
		this->_solution = solver.get_solution();
		this->_str_solution = solver.get_str_solution();

		if (this->_info.flag_bonus)
			print_process_liner(this->_info.variable,
					this->_term_descending_order[1],
					this->_term_descending_order[0],
					*std::get_if<float>(&this->_solution[0]));
	}
	else if (this->_info.equation_type == TYPE_QUADRATIC)
	{
		QuadraticEquationSolver	solver(this->_info,
						this->_term_descending_order[2],
						this->_term_descending_order[1],
						this->_term_descending_order[0]);
		solver.solve();
		this->_solution = solver.get_solution();
		this->_str_solution = solver.get_str_solution();

		if (this->_info.flag_bonus)
			print_process_quadratic(this->_info.variable,
						this->_term_descending_order[2],
						this->_term_descending_order[1],
						this->_term_descending_order[0],
						this->_solution,
						this->_str_solution);
	}
}
