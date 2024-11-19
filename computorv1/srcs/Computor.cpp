/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:46 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/19 21:18:12 by yhwang           ###   ########.fr       */
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
	this->_discriminant = computor._discriminant;
	this->_solution = computor._solution;
	this->_term_descending_order = computor._term_descending_order;
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

void	Computor::print_descending_order(std::vector<float> num)
{
	std::string	tmp = "";

	if (num[A] != 1)
		tmp += float_to_string(num[A]) + " * ";
	tmp += std::string(1, this->_variable) + "²";
	if (num[B] != 0)
	{
		if (num[B] < 0)
			tmp += " - ";
		else
			tmp += " + ";

		if (num[B] != 1)
			tmp += float_to_string(std::abs(num[B])) + " * ";
		tmp += std::string(1, this->_variable);
	}
	if (num[C] != 0)
	{
		if (num[C] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += float_to_string(std::abs(num[C]));
	}
	tmp += " = 0";
	std::cout << "1\t" << tmp << std::endl;
}

int	Computor::is_int(float num)
{
	if (num == (int)num)
		return (1);
	return (0);
}

void	Computor::divide_by_quad_coefficient(std::vector<float> &num,
						std::vector<std::string> &str)
{	
	// set variable
	num[B_PRIME] = num[B] / num[A];
	num[C_PRIME] = num[C] / num[A];

	if (num[B_PRIME] == 1)
		str[B_PRIME] = std::string(1, this->_variable);
	else
	{
		if (!is_int(num[B_PRIME]))
			str[B_PRIME] = float_to_string(std::abs(num[B]))
				+ "/" + float_to_string(num[A])
				+ std::string(1, this->_variable);
		else
		{
			if (num[B_PRIME] != 1)
				str[B_PRIME] = float_to_string(std::abs(num[B_PRIME]))
					+ " * " + std::string(1, this->_variable);
			else
				str[B_PRIME] = std::string(1, this->_variable);
		}
			
	}
	if (!is_int(num[C_PRIME]))
		str[C_PRIME] = float_to_string(std::abs(num[C]))
			+ "/" + float_to_string(num[A]);
	else
		str[C_PRIME] = float_to_string(std::abs(num[C_PRIME]));

	// print
	std::string	tmp = "";

	if (num[A] != 1)
	{
		tmp += " → " + std::string(1, this->_variable) + "²";
		if (num[B_PRIME] != 0)
		{
			if (num[B_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[B_PRIME];
		}
		if (num[C_PRIME] != 0)
		{
			if (num[C_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[C_PRIME];
		}
		tmp += " = 0";
		std::cout << "2\t" << tmp << std::endl;
	}
}

void	Computor::find_perfect_square_coefficient(std::vector<float> &num,
						std::vector<std::string> &str)
{
	// set variable
	num[SQUARE_CONSTANT] = num[B] * num[B] / (4 * num[A] * num[A]);
	str[SQUARE_CONSTANT] = float_to_string(std::abs(num[B])) + "²/"
					+ "(2²*" + float_to_string(num[A]) + "²)";

	std::string	tmp = "";
	// print
	if (num[B_PRIME] != 0)
	{
		tmp += " → (" + std::string(1, this->_variable) + "²";
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME];

		tmp += " + " + str[SQUARE_CONSTANT] + ") - " + str[SQUARE_CONSTANT];

		if (num[C_PRIME] != 0)
		{
			if (num[C_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[C_PRIME];
		}
		tmp += " = 0";
		std::cout << "3\t" << tmp << std::endl;
	}
}

void	Computor::make_perfect_square_form(std::vector<float> &num,
						std::vector<std::string> &str)
{
	//set variable
	num[B_PRIME] /= 2;
	num[C_PRIME] *= -1;
	if (!is_int(num[B_PRIME]))
		str[B_PRIME] = float_to_string(std::abs(num[B]))
				+ "/" + float_to_string(2 * num[A]);
	else
		str[B_PRIME] = float_to_string(std::abs(num[B_PRIME]));
	
	if (!is_int(num[SQUARE_CONSTANT]))
		str[SQUARE_CONSTANT] = float_to_string(std::abs(num[B_PRIME] * num[B_PRIME]))
					+ "/" + float_to_string(4 * num[A]);
	else
		str[SQUARE_CONSTANT] = float_to_string(num[SQUARE_CONSTANT]);

	//print
	std::string	tmp = "";

	if (num[B_PRIME] != 0)
	{
		tmp += " → (" + std::string(1, this->_variable);
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME] + ")²";
		tmp += " = " + str[SQUARE_CONSTANT];
		if (num[C_PRIME])
		{
			if (num[C_PRIME] < 0)
				tmp += " - ";
			else
				tmp += " + ";
			tmp += str[C_PRIME];
		}
	}
	else
	{
		tmp += " → " + std::string(1, this->_variable) + "²";
		tmp += " = ";
		if (num[C_PRIME] < 0)
			tmp += "-";
		tmp += str[C_PRIME];
	}

	if (num[SQUARE_CONSTANT] && num[C_PRIME])
	{
		tmp += " = " + str[SQUARE_CONSTANT];
		if (num[C_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[C_PRIME];
	}

	// calculate right term, update it to new_c
	num[C_PRIME] = num[SQUARE_CONSTANT] + num[C_PRIME];
	if (!is_int(num[C_PRIME]))
		str[C_PRIME] = float_to_string(std::abs(num[B] * num[B] - 4 * num[A] * num[C]))
			+ "/" + float_to_string(4 * num[A]);
	else
		str[C_PRIME] = float_to_string(num[C_PRIME]);
	//print
	if (num[SQUARE_CONSTANT])
	{
		tmp += " = ";
		if (num[C_PRIME] < 0)
			tmp += "-";
		tmp += str[C_PRIME];
	}
	std::cout << "4\t" << tmp << std::endl;

}

void	Computor::remove_square(std::vector<float> &num,
						std::vector<std::string> &str)
{
	std::string	tmp = "";

	tmp += "↔ " + std::string(1, this->_variable);
	if (num[B_PRIME] != 0)
	{
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME];
	}
	tmp += " = ";
	if (num[C_PRIME] != 0)
		tmp += "± √(" + str[C_PRIME] + ")";
	else
		tmp += "0";
	std::cout << "5\t" << tmp << std::endl;
}

void	Computor::find_x(std::vector<float> &num,
						std::vector<std::string> &str)
{
	// set variable
	num[B_PRIME] *= -1;
	str[B_PRIME] = "-" + str[B_PRIME];

	// print
	std::string tmp = "";

	if (num[B_PRIME] != 0 && num[C_PRIME] != 0)
	{
		tmp = " → " + std::string(1, this->_variable);
		tmp += " = ";
		tmp += str[B_PRIME];
		tmp += " ± ";
		if (!is_int(sqrt(num[C_PRIME])))
			tmp += "√(" + str[C_PRIME] + ")";
		else
			tmp += float_to_string(sqrt(num[C_PRIME]));
		std::cout << "6\t" << tmp << std::endl;
	}
}

// void	Computor::calc_x(std::vector<float> num,
// 						std::vector<std::string> str)
// {
// 	float x1 = -1 * b;
// 	float x2_real = b * b - (4 * a * c);
// 	float x3 = 2 * a;
// 	std::vector<int>	nums;

// 	for (size_t i = 2; i < x2_real; i++)
// 	{
// 		if (x1 / i - (int)(x2_real / i) == 0)
// 			nums.push_back(i);
// 	}
// 	int	x2_int = 1;
// 	for (size_t i = 1; i < nums.size(); i++)
// 	{
// 		if (nums[i - 1] == nums[i])
// 		{
// 			x2_int *= nums[i];
// 			x2_real /= nums[i] * nums[i];
// 			nums.erase(nums.begin() + i - 1);
// 			nums.erase(nums.begin() + i);
// 			i--;
// 		}
// 	}
// 	x2_real = sqrt(x2_real);

// 	for (int i = 2; i <= x1 || i <= x2_int || i <= x3; i++)
// 	{
// 		if (x1 / i == (int)(x1 == i)
// 			&& x2_int / i == (int)(x2_int / i)
// 			&& x3 / i == (int)(x3 / i))
// 		{
// 			x1 /= i;
// 			x2_int /= i;
// 			x3 /= i;
// 			i = 2;
// 		}
// 	}

// 	std::string answer_1;
// 	if (x2_real - (int)(x2_real) == 0)
// 	{
// 		//reduce one more
// 		answer_1 = float_to_string(x1 - x2_int * x2_real);
// 		if (x3 != 1)
// 			answer_1 += "/" + float_to_string(x3);
// 	}
// 	else
// 	{
// 		answer_1 = float_to_string(x1) + " - ";
// 		if (x2_int != 1)
// 			answer_1 += float_to_string(x2_int);
// 		answer_1 += "√(" + float_to_string(x2_real) + ")";
// 		if (x3 != 1)
// 			answer_1 += "/" + float_to_string(x3);
// 	}

// 	std::string answer_2;
// 	if (x2_real - (int)(x2_real) == 0)
// 	{
// 		//reduce one more
// 		answer_2 = float_to_string(x1 + x2_int * x2_real);
// 		if (x3 != 1)
// 			answer_2 += "/" + float_to_string(x3);
// 	}
// 	else
// 	{
// 		answer_2 = float_to_string(x1) + " + ";
// 		if (x2_int != 1)
// 			answer_2 += float_to_string(x2_int);
// 		answer_2 += "√(" + float_to_string(x2_real) + ")";
// 		if (x3 != 1)
// 			answer_2 += "/" + float_to_string(x3);
// 	}

// 	tmp = " ∴ " + std::string(1, this->_variable);
// 	tmp += " = " + answer_1 + ",";
// 	tmp += "\n\t   " + std::string(1, this->_variable);
// 	tmp += " = " + answer_2;

// 	std::cout << "7\t" << tmp << std::endl;
// }

void	Computor::print_process(void)
{

	std::vector<float>		num(6, 0);
	std::vector<std::string>	str(6, "");

	num[A] = this->_term_descending_order[0];
	num[B] = this->_term_descending_order[1];
	num[C] = this->_term_descending_order[2];
	std::cout << MAGENTA
		<< "Intermediate steps:" << BLACK << std::endl;

	// ax² + bx + c = 0
	print_descending_order(num);

	// x² + b/ax + c/a = 0
	divide_by_quad_coefficient(num, str);

	// (x² + b/ax + b²/(2²*a²)) - b²/(2²*a²) + c/a = 0
	find_perfect_square_coefficient(num, str);

	// (x + b/(2a))² = b²/(2²*a²) - c/a
	make_perfect_square_form(num, str);

	// discriminant value >= 0
	if (this->_discriminant < 0)
	{
		std::cout << YELLOW
			<< "\tWithin the real number range, the square of any number cannot be less than 0"
			<< std::endl
			<< "\t∴ it has no solution" << BLACK << std::endl;
		return ;
	}

	// ↔ x + b/(2*a) = ± √((b²-4*a*c)/(2*a))
	remove_square(num, str);

	// x = - b/(2*a) ± √((b²-4*a*c)/(2*a))
	find_x(num, str);

	// ∴ x = value
	if (num[C_PRIME] == 0)
	{
		if (num[B_PRIME] == 0)
			return ;
		std::cout << "7\t ∴ " + std::string(1, this->_variable)
			+ " = " + str[B_PRIME] << std::endl;
	}
	// else
		// calc_x(num, str);
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
		this->_solution.push_back(-1 * b / (2 * a));

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
		print_process();
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
