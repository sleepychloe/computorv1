/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/12 22:56:26 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse()
{
}

Parse::Parse(char *argv): _degree(0), _variable(0)
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

int	Parse::check_str(std::string str)
{
	if (!(is_equation_form(str) && check_variable(str) && check_syntax(str)))
		return (0);
	
	return (1);
}

int	Parse::is_equation_form(std::string str)
{
	std::string	err_msg;
	int		flag = 0;
	size_t		i = 0;

	while (i < str.length())
	{
		if (str[i] == '=')
			flag++;
		i++;
	}
	if (flag != 1)
	{
		err_msg = "equal(=) sign is missing";
		if (flag != 0)
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

int	Parse::check_variable(std::string str)
{
	std::string	err_msg;
	size_t		i = 0;

	while (('0' <= str[i] && str[i] <= '9') || str[i] == ' '
		|| str[i] == '=' || str[i] == '('
		|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' )
		i++;
	this->_variable = str[i];
	i++;

	while (1)
	{
		if (str[i] == ' ' || str[i] == '^' || str[i] == '='
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
			|| str[i] == '(' || str[i] == '\0')
			break ;
		else
		{
			err_msg = "cannot determine the variable";
			throw (err_msg);
		}
	}
	return (1);
}

int	Parse::check_syntax(std::string str)
{
	std::string	err_msg;
	size_t		i = 0;

	while (i < str.length())
	{
		if (!(('0' <= str[i] && str[i] <= '9') || str[i] == this->_variable
			|| str[i] == '^' || str[i] == '(' || str[i] == ')'
			|| str[i] == ' ' || str[i] == '='
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'))
		{
			err_msg = "invalid character exists";
			throw (err_msg);
		}
		i++;
	}
	//syntax check
	return (1);
}
