/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuadraticEquationSolver.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:18:39 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 00:27:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Execute/QuadraticEquationSolver.hpp"

QuadraticEquationSolver::QuadraticEquationSolver()
{
}

QuadraticEquationSolver::QuadraticEquationSolver(t_parse info, float a, float b, float c)
						: _info(info), _a(a), _b(b), _c(c)
{
	make_smallest_int(this->_a, this->_b, this->_c);
	this->_discriminant = this->_b * this->_b - 4 * this->_a * this->_c;

	SolutionStrGenerator	generator(this->_a, this->_b, this->_c, this->_discriminant);
	this->_generator = generator;
}

QuadraticEquationSolver::QuadraticEquationSolver(const QuadraticEquationSolver& solver)
{
	*this = solver;
}

QuadraticEquationSolver& QuadraticEquationSolver::operator=(const QuadraticEquationSolver& solver)
{
	if (this == &solver)
		return (*this);
	this->_info = solver._info;
	this->_a = solver._a;
	this->_b = solver._b;
	this->_c = solver._c;
	this->_discriminant = solver._discriminant;
	this->_solution = solver._solution;
	this->_str_solution = solver._str_solution;
	this->_generator = solver._generator;
	return (*this);
}

QuadraticEquationSolver::~QuadraticEquationSolver()
{
}

std::vector<ValueSet>	QuadraticEquationSolver::get_solution(void) const
{
	return (this->_solution);
}

std::vector<std::string>	QuadraticEquationSolver::get_str_solution(void) const
{
	return (this->_str_solution);
}

void	QuadraticEquationSolver::solve(void)
{
	if (this->_discriminant > 0)
		is_positive_disriminant();
	else if (this ->_discriminant == 0)
		is_zero_discriminant();
	else
		is_negative_discriminant();
}

void	QuadraticEquationSolver::print_variant_value(ValueSet value)
{
	if (std::get_if<float>(&value))
		std::cout << *std::get_if<float>(&value);
	else
		std::cout << complex_to_string(*std::get_if<Complex<float>>(&value));
}

void	QuadraticEquationSolver::print_solution(std::string type, int idx)
{
	std::cout << this->_info.variable << " = ";

	if (type == "float")
	{
		if (float_to_string(*std::get_if<float>(&this->_solution[idx]))
			!= this->_str_solution[idx])
			std::cout << this->_str_solution[idx] << " = ";
	}
	else if (type == "complex")
	{
		if (complex_to_string(*std::get_if<Complex<float>>(&this->_solution[idx]))
			!= this->_str_solution[idx])
			std::cout << this->_str_solution[idx] << " = ";
	}
	print_variant_value(this->_solution[idx]);
}

void	QuadraticEquationSolver::is_positive_disriminant(void)
{
	float	solution_1 = (-1 * this->_b - std::sqrt(this->_discriminant)) / (2 * this->_a);
	float	solution_2 = (-1 * this->_b + std::sqrt(this->_discriminant)) / (2 * this->_a);

	this->_solution.push_back(solution_1);
	this->_solution.push_back(solution_2);

	this->_generator.generate();
	this->_str_solution = this->_generator.get_str_solution();

	std::cout << CYAN << "Discriminant is strictly positive." << std::endl
		<< "The two solutions are\t: " << BLACK;

	print_solution("float", 0);
	std::cout << "," << std::endl;

	std::cout << "\t\t\t  ";
	print_solution("float", 1);
	std::cout << std::endl;
}

void	QuadraticEquationSolver::is_zero_discriminant(void)
{
	float	solution = (-1 * this->_b) / (2 * this->_a);

	this->_solution.push_back(solution);

	this->_generator.generate();
	this->_str_solution = this->_generator.get_str_solution();

	std::cout << CYAN << "Discriminant is zero." << std::endl
		<< "The solution is\t\t: " << BLACK;

	print_solution("float", 0);
	std::cout << std::endl;
}

void	QuadraticEquationSolver::is_negative_discriminant(void)
{
	Complex<float>	solution_1(-1 * this->_b, -1 * sqrt(-1 * this->_discriminant));
	solution_1 /= (2 * this->_a);
	Complex<float>	solution_2(-1 * this->_b, sqrt(-1 * this->_discriminant));
	solution_2 /= (2 * this->_a);

	this->_solution.push_back(solution_1);
	this->_solution.push_back(solution_2);
	
	std::cout << CYAN << "Discriminant is strictly negative." << std::endl
		<< "The two complex solutions are: " << BLACK;

	this->_generator.generate();
	this->_str_solution = this->_generator.get_str_solution();

	print_solution("complex", 0);
	std::cout << "," << std::endl;

	std::cout << "\t\t\t       ";
	print_solution("complex", 1);
	std::cout << std::endl;
}
