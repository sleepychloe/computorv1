/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:46 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/19 14:09:14 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Computor.hpp"

Computor::Computor(): _type_solution(""), _discriminant(0)
{
}

Computor::Computor(char *argv, int flag_bonus)
{
	Parse::parse_start(argv, flag_bonus);
	print_info();

	if (this->_equation_type >= 0)
	{
		for (size_t i = this->_reduced_form.size(); i > 0; i--)
			this->_term_descending_order.push_back(this->_reduced_form[i - 1]);
		if (this->_term_descending_order[0] < 0)
		{
			for (size_t i = 0; i < this->_term_descending_order.size(); i++)
				this->_term_descending_order[i] *= -1;
		}
		solve_equation();
	}
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
}

void	Computor::solve_constant(void)
{
	if (this->_reduced_form[0] == 0)
	{
		this->_type_solution = SOLUTION_INDETERMINATE;

		std::cout << CYAN
			<< "The equation is an indeterminate equation: "
			<< "It has infinitely many solutions"
			<< BLACK << std::endl;
	}
	else
	{
		this->_type_solution = SOLUTION_ZERO;

		std::cout << CYAN
			<< "The equation is an inconsistent equation: "
			<< "It has no solution"
			<< BLACK << std::endl;
	}
}

void	Computor::solve_linear(void)
{
	float	a = this->_term_descending_order[0];
	float	b = this->_term_descending_order[1];

	this->_type_solution = SOLUTION_ONE;
	this->_solution.push_back(-1 * b / a);

	if (this->_solution[0] == -0)
		this->_solution[0] = 0;

	std::cout << CYAN << "The solution is\t\t: " << BLACK;
	std::cout << this->_variable << " = " << this->_solution[0] << std::endl;

	if (this->_flag_bonus)
	{
		std::string	tmp;
		std::cout << MAGENTA
			<< "Intermediate steps:" << BLACK << std::endl;

		tmp = float_to_string(a) + " * " + std::string(1, this->_variable);
		if (b > 0)
			tmp += " + ";
		else if (b < 0)
			tmp += " - ";
		if (b != 0)
			tmp += float_to_string(std::abs(b));
		tmp += " = 0";
		std::cout << "\t" << tmp << std::endl;

		if (b != 0)
		{
			tmp = " → " + float_to_string(a) + " * "
				+ std::string(1, this->_variable) + " = ";
			if (-b < 0)
				tmp += "-";
			tmp += float_to_string(std::abs(-b));
			std::cout << "\t" << tmp << std::endl;
		}

		tmp = "∴ " + std::string(1, this->_variable) + " = ";
		if (b == 0)
			tmp += "0";
		else
		{
			if (-b < 0)
				tmp += "-";
			tmp += float_to_string(std::abs(-b)) + "/" + float_to_string(a)
				+ " = " + float_to_string(this->_solution[0]);
		}
		std::cout << "\t" << tmp << std::endl;
	}
}

void	Computor::solve_quadratic(void)
{
	float	a = this->_term_descending_order[0];
	float	b = this->_term_descending_order[1];
	float	c = this->_term_descending_order[2];

	this->_discriminant = b * b - 4 * a * c;
	if (this->_discriminant > 0)
	{
		this->_type_solution = SOLUTION_TWO;
		this->_solution.push_back((-1 * b - std::sqrt(this->_discriminant)) / (2 * a));
		this->_solution.push_back((-1 * b + std::sqrt(this->_discriminant)) / (2 * a));

		std::cout << CYAN << "Discriminant is strictly positive." << std::endl
			<< "The two solutions are\t: " << BLACK;
		std::cout << this->_variable << " = " << this->_solution[0] << "," << std::endl
			<< "\t\t\t  " << this->_variable << " = " << this->_solution[1]
			<< std::endl;
	}
	else if (this->_discriminant == 0)
	{
		this->_type_solution = SOLUTION_ONE;
		this->_solution.push_back(-1 * b / 2 * a);

		std::cout << CYAN << "Discriminant is zero." << std::endl
			<< "The solution is\t\t: " << BLACK;
		std::cout << this->_variable << " = " << this->_solution[0]
			<< std::endl;
	}
	else
	{
		this->_type_solution = SOLUTION_ZERO;

		std::cout << CYAN << "Discriminant is strictly negative." << std::endl
			<< "It has no solution" << BLACK << std::endl;
	}

	if (this->_flag_bonus)
	{
		std::string	tmp;
		std::cout << MAGENTA
			<< "Intermediate steps:" << BLACK << std::endl;

		// ax² + bx + c = 0
		tmp = "";
		if (a != 1)
			tmp += float_to_string(a) + " * ";
		tmp += std::string(1, this->_variable) + "²";
		if (b != 0)
		{
			if (b < 0)
				tmp += " - ";
			else
				tmp += " + ";

			if (b != 1)
				tmp += float_to_string(std::abs(b)) + " * ";
			tmp += std::string(1, this->_variable);
		}
		if (c != 0)
		{
			if (c < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += float_to_string(std::abs(c));
		}
		tmp += " = 0";
		std::cout << "1\t" << tmp << std::endl;

		// x² + b/ax + c/a = 0
		float	new_b = b / a;
		float	new_c = c / a;

		std::string	new_b_str;
		std::string	new_c_str;
		if (new_b == 1)
			new_b_str = std::string(1, this->_variable);
		else
		{
			if (new_b - (int)(new_b) != 0)
				new_b_str = float_to_string(std::abs(b)) + "/" + float_to_string(a)
							+ std::string(1, this->_variable);
			else
			{
				if (new_b != 1)
				{
					new_b_str = float_to_string(std::abs(new_b))
						+ " * " + std::string(1, this->_variable);
				}
				else
					new_b_str = std::string(1, this->_variable);
			}
				
		}
		if (new_c - (int)(new_c) != 0)
			new_c_str = float_to_string(std::abs(c)) + "/" + float_to_string(a);
		else
			new_c_str = float_to_string(std::abs(new_c));

		if (a != 1)
		{
			tmp = " → " + std::string(1, this->_variable) + "²";
			if (new_b != 0)
			{
				if (new_b < 0)
					tmp += " - ";
				else
					tmp += " + ";
				tmp += new_b_str;
			}
			if (new_c != 0)
			{
				if (new_c < 0)
					tmp += " - ";
				else
					tmp += " + ";
				tmp += new_c_str;
			}
			tmp += " = 0";
			std::cout << "2\t" << tmp << std::endl;
		}

		// (x² + b/ax + b²/(2²*a²)) - b²/(2²*a²) + c/a = 0
		float		square_constant = b * b / (4 * a * a);
		std::string	square_constant_str = float_to_string(std::abs(b)) + "²/"
						+ "(2²*" + float_to_string(a) + "²)";
		if (new_b != 0)
		{
			tmp = " → (" + std::string(1, this->_variable) + "²";
			if (new_b < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += new_b_str;

			tmp += " + " + square_constant_str + ") - " + square_constant_str;

			if (new_c != 0)
			{
				if (new_c < 0)
					tmp += " - ";
				else
					tmp += " + ";
				tmp += new_c_str;
			}
			tmp += " = 0";
			std::cout << "3\t" << tmp << std::endl;
		}
		
		// (x + b/(2a))² = b²/(2²*a²) - c/a = num
		new_b /= 2;
		new_c *= -1;


		if (new_b - (int)new_b != 0)
			new_b_str = float_to_string(std::abs(b)) + "/" + float_to_string(2 * a);
		else
			new_b_str = float_to_string(std::abs(new_b));

		if (b != 0)
		{
			tmp = " → (" + std::string(1, this->_variable);
			if (new_b < 0)
				tmp += " + ";
			else
				tmp += " - ";
			tmp += new_b_str + ")²";
			tmp += " = " + square_constant_str;
			if (new_c)
			{
				if (new_c < 0)
					tmp += " - ";
				else
					tmp += " + ";
				tmp += new_c_str;
			}
		}
		else
		{
			tmp = " → " + std::string(1, this->_variable) + "²";
			tmp += " = ";
			if (new_c < 0)
				tmp += "-";
			tmp += new_c_str;
		}

		if (square_constant - (int)(square_constant) != 0)
			square_constant_str = float_to_string(std::abs(b * b)) + "/" + float_to_string(4 * a);
		else
			square_constant_str = float_to_string(square_constant);
		if (square_constant && new_c)
		{
			tmp += " = " + square_constant_str;
			if (new_c < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += new_c_str;
		}

		// new_c = square_constant + new_c;
		// if (new_c - (int)(new_c) != 0)
		// 	new_c_str = float_to_string(std::abs(b * b - 4 * a * c)) + "/" + float_to_string(4 * a);
		// else
		// 	new_c_str = float_to_string(new_c);
		// if (square_constant && new_c)
		// {
		// 	tmp += " = " + new_c_str;
		// }
		std::cout << "4\t" << tmp << std::endl;
		
		

		// if (b != 0)
		// {
		// 	tmp = " → (" + std::string(1, this->_variable);
		// 	if (b > 0)
		// 		tmp += " + ";
		// 	else if (b < 0)
		// 		tmp += " - ";
		// 	tmp += float_to_string(std::abs(b)) + "/(2*" + float_to_string(a) + "))² = ";
		// 	tmp += float_to_string(std::abs(b))  + "²" + "/(2²*" + float_to_string(a) + "²) ";
		// 	if (-c > 0)
		// 		tmp += " + ";
		// }
		// else
		// 	tmp = " → " + std::string(1, this->_variable) + "² = ";
		// if (c != 0)
		// {
		// 	if (-c < 0)
		// 	{
		// 		if (b != 0)
		// 			tmp += "- ";
		// 		else
		// 			tmp += "-";
		// 	}
		// 	tmp += float_to_string(std::abs(c)) + "/" + float_to_string(a);
		// }

		// tmp += " = ";
		// if (b != 0)
		// {
		// 	tmp += float_to_string(b * b) += "/" + float_to_string(4 * a * a) + " ";
		// 	if (-c > 0)
		// 		tmp += "+ ";
		// }
		// if (c != 0)
		// {
		// 	if (-c < 0)
		// 		tmp += "-";
		// 	if (b != 0)
		// 		tmp += " ";
		// 	if (a == 1)
		// 		tmp += float_to_string(std::abs(c));
		// 	else
		// 		tmp += float_to_string(std::abs(c)) + "/" + float_to_string(a);
		// }
		// else 
		// 	tmp += "0";

		// if (b != 0 && c != 0)
		// {
		// 	tmp += " = ";
		// 	if ((b * b / (4 * a) - c / a) - (int)(b * b / (4 * a) - c / a) != 0)
		// 	{
		// 		if (b * b / (4 * a) - c / a < 0)
		// 			tmp += "-";
		// 		tmp += float_to_string(std::abs(b * b - 4 * c));
		// 		tmp += "/" + float_to_string(4*a);
		// 		std::string fraction = tmp;
		// 	}
		// 	else
		// 		tmp += float_to_string(b * b / (4 * a) - c / a);
		// }
		// std::cout << "4\t" << tmp << std::endl;

		// discriminant value >= 0
		if (this->_discriminant < 0)
		{
			std::cout << YELLOW
				<< "\tWithin the real number range, the square of any number cannot be less than 0"
				<< std::endl
				<< "\t∴ it has no solution" << BLACK << std::endl;
			return ;
		}
std::cout << "-------------------------------------" << std::endl;

		// ↔ x + b/(2*a) = ± √((b²-4*a*c)/(2*a))
		tmp =  "↔ " + std::string(1, this->_variable);
		if (b != 0)
		{
			if (b > 0)
				tmp += " + ";
			else if (b < 0)
				tmp += " - ";
			tmp += float_to_string(std::abs(b)) + "/(2*" + float_to_string(a) + ") = ";
			tmp += "± √((" + float_to_string(std::abs(b)) + "²";
			if (c != 0)
				tmp += "-4*" + float_to_string(a) + "*" + float_to_string(c) + ")";
			tmp += "/(2*" + float_to_string(a);
			tmp += "))";
		}
		else
		{
			tmp += " = ± √((";
			if (c != 0)
			{
				tmp += "-4*" + float_to_string(a) + "*" + float_to_string(c) + ")";
				tmp += "/(2*" + float_to_string(a);
			}
			else
				tmp += "0";
			tmp += "))";
		}
		std::cout << "5\t" << tmp << std::endl;

		// → x = -b/(2*a) ± √((b²-4*a*c)/(2*a))
		tmp = " → " + std::string(1, this->_variable) + " = ";
		if (b != 0)
			tmp += float_to_string(-b) + "/(2*" + float_to_string(a) + ")";
		else
			tmp += "0";
		if (this->_discriminant != 0)
		{
			if (b != 0)
			{
				tmp += " ± √((" + float_to_string(std::abs(b)) + "²";
				if (c != 0)
					tmp += "-4*" + float_to_string(a) + "*" + float_to_string(c) + ")";
				tmp += "/(2*" + float_to_string(a);
				tmp += "))";
			}
			else
			{
				tmp += " = ± √((";
				if (c != 0)
				{
					tmp += "-4*" + float_to_string(a) + "*" + float_to_string(c) + ")";
					tmp += "/(2*" + float_to_string(a);
				}
				else
					tmp += "0";
				tmp += "))";
			}
			std::cout << "6\t" << tmp << std::endl;
		}

		//∴x = 
	}
}

void	Computor::solve_equation(void)
{
	if (this->_equation_type == TYPE_CONSTANT)
		solve_constant();
	else if (this->_equation_type == TYPE_LINEAR)
		solve_linear();
	else
		solve_quadratic();
}
