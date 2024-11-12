/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/12 10:49:14 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse()
{
}

Parse::Parse(char *argv): _equal_sign(0), _degree(0), _variable(0)
{
	std::string	str(argv);

	check_str(str);
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse& Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_equal_sign = parse._equal_sign;
	this->_degree = parse._degree;
	this->_variable = parse._variable;
	this->_left_term = parse._left_term;
	this->_right_term = parse._right_term;
	this->_reduced_form = parse._reduced_form;
	return (*this);
}

Parse::~Parse()
{
}

void	Parse::check_str(std::string str)
{
	if (is_equation_form(str))
		check_variable(str);
}

int	Parse::is_equation_form(std::string str)
{
	std::string	err_msg;
	size_t		i = 0;

	while (i < str.length())
	{
		if (str[i] == '=')
			this->_equal_sign++;
		i++;
	}
	if (this->_equal_sign != 1)
	{
		err_msg = "equal(=) sign is missing";
		if (this->_equal_sign != 0)
			err_msg = "equal(=) sign used multiple time";
		throw (err_msg);
	}

	i = 0;
	while (i < str.length())
	{
		while (str[i] != '=')
			i++;
		i++;
		while (str[i] == ' ')
			i++;
		if (str[i] != '\0')
			break ;
		else
		{
			err_msg = "invalid equation form";
			throw (err_msg);
		}
	}
	return (1);
}

// a * X^0 + b * X^1 + c * X^2 = d * X^0 + e * X^1 + f * X^2
// a + b * X + c * X^2 = 0
// a + b * X + c * X * X = 0
// a + b * X + a * X = 0
// 0 = a + b * X + c * X^2

void	Parse::check_variable(std::string str)
{
	std::string	err_msg;
	size_t		i = 0;

	while (('0' <= str[i] && str[i] <= '9') || str[i] == ' '
			|| str[i] == '*' || str[i] == '+' || str[i] == '-' || str[i] == '=')
		i++;
	this->_variable = str[i];
	i++;
	std::cout << "variable: " << this->_variable << std::endl;

	while (1)
	{
		if (str[i] == ' ' || str[i] == '^' || str[i] == '='
			|| str[i] == '+' || str[i] == '-' || str[i] == '\0')
			break ;
		else
		{
			err_msg = "cannot determine the variable";
			throw (err_msg);
		}
	}
}

//todo: check if invalid letter is in the str(only allow 0 to 9, space, +, -, *, =, variable)

//how to handle 3/x = 1