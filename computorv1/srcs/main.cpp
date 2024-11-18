/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:07:38 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 01:41:38 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"
#include "../incs/Computor.hpp"

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
	std::cout << "\t./computer \"POLYNOMIAL_SECOND_OR_LOWER_DEGREE_EQUATION" << std::endl;
	std::cout << std::endl;
	std::cout << YELLOW << "EXAMPLES:" << BLACK << std::endl;
	std::cout << "\t./computer \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
	std::cout << std::endl;
	std::cout << "\t./computer \"5 * X^0 + 4 * X^1 = 4 * X^0\"" << std::endl;
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
	if (strlen(argv[0]) == strlen("./computor_bonus")
		&& !strncmp(argv[0], "./computor_bonus", strlen("computor_bonus")))
		flag_bonus = 1;
	if ((strlen(argv[1]) == strlen("-h") && !strncmp(argv[1], "-h", strlen("-h")))
		|| (strlen(argv[1]) == strlen("--help") && !strncmp(argv[1], "--help", strlen("--help"))))
	{
		print_help();
		return (0);
	}

	Parse		*p = new Computor();
	try
	{
		p->parse_start(argv[1]);
		p->print_info(flag_bonus);
	}
	catch(std::string err_msg)
	{
		std::cerr << RED << "error: invalid input: " << err_msg << BLACK << std::endl;
		delete p;
		return (1);
	}
	delete p;
	return (0);
}
