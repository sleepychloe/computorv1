/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:17:31 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/13 23:23:23 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Execute/ExecuteUtils.hpp"

void	print_process_liner(char variable,
				float a, float b, float solution)
{
	float		tmp_a = a;
	float		tmp_b = b;
	std::string	tmp;

	std::cout << MAGENTA
		<< "Intermediate steps:" << BLACK << std::endl;

	/* a * x + b = 0 */
	tmp = float_to_string(a) + " * " + std::string(1, variable);
	if (b > 0)
		tmp += " + ";
	else if (b < 0)
		tmp += " - ";

	if (b != 0)
		tmp += float_to_string(std::abs(b));
	tmp += " = 0";
	std::cout << "\t" << tmp << std::endl;

	/* → a * x = -b */
	if (b != 0)
	{
		tmp = " → " + float_to_string(a) + " * "
			+ std::string(1, variable) + " = ";
		if (b > 0)
			tmp += "-";
		tmp += float_to_string(std::abs(-b));
		std::cout << "\t" << tmp << std::endl;
	}

	/* ∴ x = -b/a(str) = -b/a(str, reduction) = -b/a(float) */
	tmp = "∴ " + std::string(1, variable) + " = ";
	if (b == 0)
		tmp += "0";
	else
	{
		if (-b < 0)
			tmp += "-";
		tmp += float_to_string(std::abs(-b)) + "/" + float_to_string(a) + " = ";
		fraction_reduction(tmp_a, tmp_b);
		if (a != tmp_a)
		{
			if (b > 0)
				tmp += "-";
			tmp += float_to_string(std::abs(tmp_b)) + "/" + float_to_string(tmp_a) + " = ";
		}
		tmp += float_to_string(solution);
	}
	std::cout << "\t" << tmp << std::endl;
}

/* ax² + bx + c = 0 */
static void	print_descending_order(char variable, std::vector<float> num)
{
	std::string	tmp = "";

	if (num[A] != 1)
		tmp += float_to_string(num[A]) + " * ";
	tmp += std::string(1, variable) + "²";
	if (num[B] != 0)
	{
		if (num[B] < 0)
			tmp += " - ";
		else
			tmp += " + ";

		if (num[B] != 1)
			tmp += float_to_string(std::abs(num[B])) + " * ";
		tmp += std::string(1, variable);
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
	std::cout << "\t" << tmp << std::endl;
}

/* x² + b/ax + c/a = 0 */
static void	divide_by_quad_coefficient(char variable,
				std::vector<float> &num,
				std::vector<std::string> &str)
{	
	// set variable
	num[B_PRIME] = num[B] / num[A];
	num[C_PRIME] = num[C] / num[A];

	if (num[B_PRIME] == 1)
		str[B_PRIME] = std::string(1, variable);
	else
	{
		if (!is_int(num[B_PRIME]))
			str[B_PRIME] = float_to_string(std::abs(num[B]))
				+ "/" + float_to_string(num[A])
				+ std::string(1, variable);
		else
		{
			if (num[B_PRIME] != 1)
				str[B_PRIME] = float_to_string(std::abs(num[B_PRIME]))
					+ " * " + std::string(1, variable);
			else
				str[B_PRIME] = std::string(1, variable);
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
		tmp += " → " + std::string(1, variable) + "²";
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
		std::cout << "\t" << tmp << std::endl;
	}
}

/* (x² + b/ax + b²/(2²*a²)) - b²/(2²*a²) + c/a = 0 */
static void	find_perfect_square_coefficient(char variable,
				std::vector<float> &num,
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
		tmp += " → (" + std::string(1, variable) + "²";
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
		std::cout << "\t" << tmp << std::endl;
	}
}

/* (x + b/(2a))² = b²/(2²*a²) - c/a */
static void	make_perfect_square_form(char variable,
				float discriminant,
				std::vector<float> &num,
				std::vector<std::string> &str)
{
	//set variable
	num[B_PRIME] /= 2;
	num[C_PRIME] *= -1;

	float	tmp1 = std::abs(num[B]);
	float	tmp2 = 2 * num[A];
	fraction_reduction(tmp1, tmp2);
	if (!is_int(num[B_PRIME]))
		str[B_PRIME] = float_to_string(tmp1)
				+ "/" + float_to_string(tmp2);
	else
		str[B_PRIME] = float_to_string(std::abs(num[B_PRIME]));

	//print
	std::string	tmp = "";

	if (num[B_PRIME] != 0)
	{
		tmp += " → (" + std::string(1, variable);
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
		tmp += " → " + std::string(1, variable) + "²";
		tmp += " = ";
		if (num[C_PRIME] < 0)
			tmp += "-";
		tmp += str[C_PRIME];
	}

	tmp1 = num[B] * num[B];
	tmp2 = 4 * num[A] * num[A];
	fraction_reduction(tmp1, tmp2);
	if (!is_int(num[SQUARE_CONSTANT]))
		str[SQUARE_CONSTANT] = float_to_string(tmp1)
					+ "/" + float_to_string(tmp2);
	else
		str[SQUARE_CONSTANT] = float_to_string(num[SQUARE_CONSTANT]);

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
	tmp1 = std::abs(num[B] * num[B] - 4 * num[A] * num[C]);
	tmp2 = 4 * num[A] * num[A];
	fraction_reduction(tmp1, tmp2);
	if (!is_int(num[C_PRIME]))
		str[C_PRIME] = float_to_string(tmp1)
			+ "/" + float_to_string(tmp2);
	else
		str[C_PRIME] = float_to_string(num[C_PRIME]);

	//print
	if (num[SQUARE_CONSTANT])
	{
		tmp += " = ";
		if (discriminant < 0)
			tmp += "-";
		if (str[C_PRIME][0] == '-')
			tmp += str[C_PRIME].substr(1, std::string::npos);
		else
			tmp += str[C_PRIME];
	}
	std::cout << "\t" << tmp << std::endl;
}

/* ↔ x + b/(2*a) = ± √((b²-4*a*c)/(2*a)) */
static void	remove_square(char variable,
				std::vector<float> &num,
				std::vector<std::string> &str)
{
	std::string	tmp = "";

	tmp += "↔ " + std::string(1, variable);
	if (num[B_PRIME] != 0)
	{
		if (num[B_PRIME] < 0)
			tmp += " - ";
		else
			tmp += " + ";
		tmp += str[B_PRIME];
	}
	tmp += " = ";
	if (num[C_PRIME] > 0)
		tmp += "± √(" + str[C_PRIME] + ")";
	else if (num[C_PRIME] == 0)
		tmp += "0";
	else
	{
		if (str[C_PRIME][0] == '-')
			str[C_PRIME] = str[C_PRIME].substr(1, std::string::npos);
		tmp += "± √(" + str[C_PRIME] + ")" + "i";
	}
	std::cout << "\t" << tmp << std::endl;
}

/* x = - b/(2*a) ± √((b²-4*a*c)/(2*a)) */
static void	find_x(char variable,
				std::vector<float> &num,
				std::vector<std::string> &str)
{
	// set variable
	num[B_PRIME] *= -1;
	if (str[B_PRIME][0] == '-')
		str[B_PRIME] = str[B_PRIME].substr(1, std::string::npos);
	if (num[B_PRIME] < 0)
		str[B_PRIME] = "-" + str[B_PRIME];

	// print
	std::string tmp = "";

	if (num[B_PRIME] != 0 && num[C_PRIME] != 0)
	{
		tmp = " → " + std::string(1, variable);
		tmp += " = ";
		tmp += str[B_PRIME];
		tmp += " ± ";
		if (num[C_PRIME] > 0)
		{
			if (!is_int(sqrt(num[C_PRIME])))
				tmp += "√(" + str[C_PRIME] + ")";
			else
				tmp += float_to_string(sqrt(num[C_PRIME]));
		}
		else
		{
			if (!is_int(sqrt(num[C_PRIME])))
				tmp += "√(" + str[C_PRIME] + ")" + "i";
			else
				tmp += float_to_string(sqrt(num[C_PRIME])) + "i";
		}
		std::cout << "\t" << tmp << std::endl;
	}
}

/* ∴ x = value(str) = value(float) */
static void	print_solution(char variable,
				std::vector<ValueSet> solution,
				std::vector<std::string> str_solution)
{
	std::cout << "\n\t ∴ " << variable << " = ";
	if (std::get_if<float>(&solution[0]))
	{
		if (float_to_string(*std::get_if<float>(&solution[0]))
			!= str_solution[0])
			std::cout << str_solution[0] << " = ";
		std::cout << *std::get_if<float>(&solution[0]);
	}
	else
	{
		if (complex_to_string(*std::get_if<Complex<float>>(&solution[0]))
			!= str_solution[0])
			std::cout << str_solution[0] << " = ";
		std::cout << complex_to_string(*std::get_if<Complex<float>>(&solution[0]));
	}
	
	if (solution.size() == 1)
		std::cout << std::endl;
	else
	{
		std::cout << ",\n\t   " << variable << " = ";
		if (std::get_if<float>(&solution[1]))
		{
			if (float_to_string(*std::get_if<float>(&solution[1]))
				!= str_solution[1])
				std::cout << str_solution[1] << " = ";
			std::cout << *std::get_if<float>(&solution[1]);
		}
		else
		{
			if (complex_to_string(*std::get_if<Complex<float>>(&solution[1]))
				!= str_solution[1])
				std::cout << str_solution[1] << " = ";
			std::cout << complex_to_string(*std::get_if<Complex<float>>(&solution[1]));
		}
		std::cout << std::endl;
	}
}

void	print_process_quadratic(char variable,
				float a, float b, float c,
				std::vector<ValueSet> solution,
				std::vector<std::string> str_solution)
{

	std::vector<float>		num(6, 0);
	std::vector<std::string>	str(6, "");

	num[A] = a;
	num[B] = b;
	num[C] = c;

	make_smallest_int(a, b, c);

	float discriminant = b * b - 4 * a * c;

	std::cout << MAGENTA
		<< "Intermediate steps:" << BLACK << std::endl;

	/* ax² + bx + c = 0 */
	print_descending_order(variable, num);

	/* x² + b/ax + c/a = 0 */
	divide_by_quad_coefficient(variable, num, str);

	/* (x² + b/ax + b²/(2²*a²)) - b²/(2²*a²) + c/a = 0 */
	find_perfect_square_coefficient(variable, num, str);

	/* (x + b/(2a))² = b²/(2²*a²) - c/a */
	make_perfect_square_form(variable, discriminant, num, str);

	/* ↔ x + b/(2*a) = ± √((b²-4*a*c)/(2*a)) */
	remove_square(variable, num, str);

	/* x = - b/(2*a) ± √((b²-4*a*c)/(2*a)) */
	find_x(variable, num, str);

	/* ∴ x = value(str) = value(float) */
	print_solution(variable, solution, str_solution);
}
