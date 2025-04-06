/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:07:38 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:58:05 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Struct.hpp"
#include "../incs/Parse/Parse.hpp"
#include "../incs/Execute/Computor.hpp"

void	print_help(void)
{
	std::cout << CYAN << "computorv1 by yhwang" << BLACK << std::endl;
	std::cout << std::endl;
	std::cout << "A program that solves a polynomial second or lower degree equation." << std::endl;
	std::cout << "This program always expect the argument entry to have right format:" << std::endl;
	std::cout << "every term respect the form a * xᵖ." << std::endl;
	std::cout << "Also the program does not support third degree or higher equation resolution" << std::endl;
	std::cout << "as subject requires." << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << YELLOW << "USAGE:" << BLACK << std::endl;
	std::cout << "\t./computer \"POLYNOMIAL_SECOND_OR_LOWER_DEGREE_EQUATION\"" << std::endl;
	std::cout << std::endl;
	std::cout << "\t./computer_bonus \"POLYNOMIAL_SECOND_OR_LOWER_DEGREE_EQUATION\"" << std::endl;
	std::cout << std::endl;
	std::cout << YELLOW << "EXAMPLES:" << BLACK << std::endl;
	std::cout << "\t./computer \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
	std::cout << std::endl;
	std::cout << "\t./computer_bonus \"5 * X^0 + 4 * X^1 = 4 * X^0\"" << std::endl;
	std::cout << std::endl;
	std::cout << YELLOW << "OPTIONS:" << BLACK << std::endl;
	std::cout << CYAN << "\t-h" << BLACK << ", " << CYAN << "--help" << BLACK << std::endl;
	std::cout << "\t\tPrint help information" << std::endl;
	std::cout << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << RED << "error: invalid number of argument" << BLACK << std::endl;
		return (1);
	}

	int	flag_bonus = 0;
	if ((strlen(argv[0]) == strlen("./computor_bonus")
		&& !strncmp(argv[0], "./computor_bonus", strlen("computor_bonus")))
		|| std::string(argv[0]).find("computor_bonus") != std::string::npos)
		flag_bonus = 1;

	if ((strlen(argv[1]) == strlen("-h") && !strncmp(argv[1], "-h", strlen("-h")))
		|| (strlen(argv[1]) == strlen("--help") && !strncmp(argv[1], "--help", strlen("--help"))))
	{
		print_help();
		return (0);
	}

	t_parse		parse_info;

	try
	{
		Parse		parse;

		parse.parse(argv[1], flag_bonus);
		parse_info = parse.get_info();
	}
	catch(const ParseError::ParseException& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	Computor	computor(parse_info);
	return (0);
}
