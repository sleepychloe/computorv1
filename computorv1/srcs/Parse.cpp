/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/13 22:47:31 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse()
{
}

Parse::Parse(char *argv): _degree(0), _variable(0), _err_msg("")
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
	this->_err_msg = parse._err_msg;
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
	int	flag = 0;
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '=')
			flag++;
		i++;
	}
	if (flag != 1)
	{
		this->_err_msg = "equal(=) sign is missing";
		if (flag != 0)
			this->_err_msg = "equal(=) sign used multiple time";
		throw (this->_err_msg);
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
			this->_err_msg = "invalid equation form";
			throw (this->_err_msg);
		}
	}
	return (1);
}

int	Parse::check_variable(std::string str)
{
	size_t	i = 0;

	while (('0' <= str[i] && str[i] <= '9') || str[i] == ' '
		|| str[i] == '=' || str[i] == '(' || str[i] == ')'
		|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' )
		i++;
	this->_variable = str[i];
	std::cout << "variable: " << this->_variable << std::endl;//
	i++;
	while (1)
	{
		if (str[i] == ' ' || str[i] == '^' || str[i] == '='
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
			|| str[i] == '(' || str[i] == ')' || str[i] == '\0')
			break ;
		else
		{
			this->_err_msg = "cannot determine the variable";
			throw (this->_err_msg);
		}
	}
	return (1);
}

int	Parse::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(('0' <= str[i] && str[i] <= '9') || str[i] == this->_variable
			|| str[i] == '^' || str[i] == '(' || str[i] == ')'
			|| str[i] == ' ' || str[i] == '='
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'))
		{
			this->_err_msg = "invalid character exists";
			throw (this->_err_msg);
		}
		i++;
	}
	return (1);
}

int	Parse::check_brackets(std::string str)
{
	int	open = 0;
	int	close = 0;
	size_t	i = 0;
	size_t	j = 0;

	while (i < str.length())
	{
		if (str[i] == ')')
		{
			close++;
			while (j < i)
			{
				if (str[j] == '(')
				{
					open++;
					j++;
					break ;
				}
				j++;
			}
			if (close != open)
			{
				this->_err_msg = "invalid syntax: brackets";
				throw (this->_err_msg);
			}
		}
		i++;
	}

	i = 0;
	open = 0;
	while (i < str.length())
	{
		if (str[i] == '(')
			open++;
		i++;
	}
	if (close != open)
	{
		this->_err_msg = "invalid syntax: brackets";
		throw (this->_err_msg);
	}
	return (1);
}

int	Parse::check_sign(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_number(std::string str)
{
	size_t	i = 0;
	int	space = 0;

	while (i < str.length())
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			i++;
			while (str[i] == ' ')
			{
				space++;
				i++;
			}
			if (space && ('0' <= str[i] && str[i] <= '9'))
			{
				this->_err_msg = "invalid syntax: no operator between numbers";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_caret(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '^')
		{
			if (!((str[i - 1] && (str[i - 1] == this->_variable || str[i - 1] == ')'))
				&& (str[i + 1] && ('0' <= str[i + 1] && str[i + 1] <= '9'))))
			{
				this->_err_msg = "invalid syntax: cardet(^)";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_syntax(std::string str)
{
	if (!(check_invalid_character(str) && check_brackets(str)
		&& check_sign(str) && check_number(str) && check_caret(str)))
		return (0);
	return (1);
}
