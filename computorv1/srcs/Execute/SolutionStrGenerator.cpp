/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SolutionStrGenerator.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:06:41 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 19:20:41 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Execute/SolutionStrGenerator.hpp"

SolutionStrGenerator::SolutionStrGenerator()
{
}

SolutionStrGenerator::SolutionStrGenerator(float a, float b, float c, float discriminant)
						: _a(a), _b(b), _c(c), _discriminant(discriminant)
{
	this->_term.first_term = -1 * this->_b;
	this->_term.second_term_int = 1;
	this->_term.second_term_real = ft_abs(this->_b * this->_b - 4 * this->_a * this->_c);
	split_square_num(this->_term.second_term_int, this->_term.second_term_real);
	this->_term.denominator = 2 * this->_a;
}

SolutionStrGenerator::SolutionStrGenerator(const SolutionStrGenerator& generator)
{
	*this = generator;
}

SolutionStrGenerator& SolutionStrGenerator::operator=(const SolutionStrGenerator& generator)
{
	if (this == &generator)
		return (*this);
	this->_term = generator._term;
	this->_a = generator._a;
	this->_b = generator._b;
	this->_c = generator._c;
	this->_discriminant = generator._discriminant;
	this->_str_solution = generator._str_solution;
	return (*this);
}

SolutionStrGenerator::~SolutionStrGenerator()
{
}

std::vector<std::string>	SolutionStrGenerator::get_str_solution(void) const
{
	return (this->_str_solution);
}

void	SolutionStrGenerator::generate(void)
{
	if (this->_discriminant == 0)
		double_solution();
	else if (this->_discriminant > 0 && is_int(ft_sqrt(this->_term.second_term_real)))
		real_solution_square_num();
	else
		general_solution();
}

void	SolutionStrGenerator::double_solution(void)
{
	std::string	str_solution = "";

	if (this->_term.first_term < 0)
	{
		this->_term.first_term *= -1;
		str_solution += "-";
	}
	fraction_reduction(this->_term.first_term, this->_term.denominator);
	str_solution += float_to_string(this->_term.first_term);
	if (this->_term.denominator != 1)
		str_solution += "/" + float_to_string(this->_term.denominator);
	this->_str_solution.push_back(str_solution);
}

void	SolutionStrGenerator::real_solution_square_num(void)
{
	std::string	str_solution_1 = "";
	std::string	str_solution_2 = "";

	this->_term.second_term_int *= ft_sqrt(this->_term.second_term_real);

	float	solution_1 = this->_term.first_term - this->_term.second_term_int;
	float	solution_2 = this->_term.first_term + this->_term.second_term_int;

	if (solution_1 < 0)
	{
		solution_1 *= -1;
		str_solution_1 += "-";
	}
	fraction_reduction(solution_1, this->_term.denominator);
	str_solution_1 += float_to_string(solution_1);
	if (this->_term.denominator != 1)
		str_solution_1 += "/" + float_to_string(this->_term.denominator);

	this->_term.denominator = 2 * this->_a;

	if (solution_2 < 0)
	{
		solution_2 *= -1;
		str_solution_2 += "-";
	}
	fraction_reduction(solution_2, this->_term.denominator);
	str_solution_2 += float_to_string(solution_2);
	if (this->_term.denominator != 1)
		str_solution_2 += "/" + float_to_string(this->_term.denominator);

	this->_str_solution.push_back(str_solution_1);
	this->_str_solution.push_back(str_solution_2);
}

void	SolutionStrGenerator::general_solution_square_num(std::string &str_1, std::string &str_2)
{
	this->_term.second_term_int *= ft_sqrt(this->_term.second_term_real);
	fraction_reduction(this->_term.second_term_int, this->_term.denominator);

	str_1 += float_to_string(this->_term.second_term_int);
	str_2 += float_to_string(this->_term.second_term_int);
	if (this->_term.denominator != 1)
	{
		str_1 += "/" + float_to_string(this->_term.denominator);
		str_2 += "/" + float_to_string(this->_term.denominator);
	}
	if (this->_discriminant < 0)
	{
		str_1 += "i";
		str_2 += "i";
	}
}

void	SolutionStrGenerator::general_solution_general(std::string &str_1, std::string &str_2)
{
	fraction_reduction(this->_term.second_term_int, this->_term.denominator);
	if (this->_term.second_term_int != 1)
	{
		str_1 += float_to_string(this->_term.second_term_int);
		str_2 += float_to_string(this->_term.second_term_int);
	}
	str_1 += "√(" + float_to_string(this->_term.second_term_real) + ")";
	str_2 += "√(" + float_to_string(this->_term.second_term_real) + ")";
	if (this->_discriminant < 0)
	{
		str_1 += "i";
		str_2 += "i";
	}

	if (this->_term.denominator != 1)
	{
		str_1 += "/" + float_to_string(this->_term.denominator);
		str_2 += "/" + float_to_string(this->_term.denominator);
	}
}

void	SolutionStrGenerator::general_solution(void)
{
	std::string	str_solution_1 = "";
	std::string	str_solution_2 = "";

	if (this->_term.first_term < 0)
	{
		str_solution_1 += "-";
		str_solution_2 += "-";
		this->_term.first_term *= -1;
	}

	/* first term: -b/2a */
	fraction_reduction(this->_term.first_term, this->_term.denominator);
	str_solution_1 += float_to_string(this->_term.first_term);
	str_solution_2 += float_to_string(this->_term.first_term);
	if (this->_term.denominator != 1)
	{
		str_solution_1 += "/" + float_to_string(this->_term.denominator);
		str_solution_2 += "/" + float_to_string(this->_term.denominator);
	}
	str_solution_1 += " - ";
	str_solution_2 += " + ";

	this->_term.denominator = 2 * this->_a;

	/* second term: sqrt(b*b-4ac)/2a */	
	if (is_int(ft_sqrt(this->_term.second_term_real)))
		general_solution_square_num(str_solution_1, str_solution_2);
	else
		general_solution_general(str_solution_1, str_solution_2);

	this->_str_solution.push_back(str_solution_1);
	this->_str_solution.push_back(str_solution_2);
}
