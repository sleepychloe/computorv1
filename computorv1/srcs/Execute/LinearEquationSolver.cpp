/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinerEquationSolver.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:18:26 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:44:58 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Execute/LinearEquationSolver.hpp"

LinerEquationSolver::LinerEquationSolver()
{
}

LinerEquationSolver::LinerEquationSolver(t_parse info, float a, float b)
						: _info(info), _a(a), _b(b)
{
	make_smallest_int(this->_a, this->_b);
}

LinerEquationSolver::LinerEquationSolver(const LinerEquationSolver& solver)
{
	*this = solver;
}

LinerEquationSolver& LinerEquationSolver::operator=(const LinerEquationSolver& solver)
{
	if (this == &solver)
		return (*this);
	this->_info = solver._info;
	this->_a = solver._a;
	this->_b = solver._b;
	this->_solution = solver._solution;
	return (*this);
}

LinerEquationSolver::~LinerEquationSolver()
{
}

std::vector<ValueSet>	LinerEquationSolver::get_solution(void) const
{
	return (this->_solution);
}

std::vector<std::string>	LinerEquationSolver::get_str_solution(void) const
{
	return (this->_str_solution);
}

void	LinerEquationSolver::solve(void)
{
	float	solution = -1 * this->_b / this->_a;
	
	if (solution != 0)
		this->_solution.push_back(solution);
	else
		this->_solution.push_back(0);

	make_str_solution();

	std::cout << CYAN << "The solution is\t\t: " << BLACK;
	print_solution();
	std::cout << std::endl;
}

void	LinerEquationSolver::print_solution(void)
{
	std::cout << this->_info.variable << " = ";

	if (float_to_string(*std::get_if<float>(&this->_solution[0]))
		!= this->_str_solution[0])
		std::cout << this->_str_solution[0] << " = ";
	std::cout << *std::get_if<float>(&this->_solution[0]);
}

void	LinerEquationSolver::make_str_solution(void)
{
	std::string	str_solution = "";

	if (this->_b > 0)
		str_solution += "-";

	float		a = this->_a;
	float		b = this->_b;
	fraction_reduction(a, b);

	str_solution += float_to_string(ft_abs(b));
	if (a != 1)
		str_solution += "/" + float_to_string(a);
	this->_str_solution.push_back(str_solution);
}
