/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputConvertor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 02:55:23 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:58:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Parse/InputConvertor.hpp"

InputConvertor::InputConvertor()
{
}

InputConvertor::InputConvertor(std::string str, t_parse info): _str(str), _info(info)
{
}

InputConvertor::InputConvertor(const InputConvertor& convertor)
{
	*this = convertor;
}

InputConvertor& InputConvertor::operator=(const InputConvertor& convertor)
{
	if (this == &convertor)
		return (*this);
	this->_str = convertor._str;
	this->_info = convertor._info;
	this->_struct_error = convertor._struct_error;
	return (*this);
}

InputConvertor::~InputConvertor()
{
}

t_parse InputConvertor::get_info(void) const
{
	return (this->_info);
}

std::string	InputConvertor::convert(std::string str)
{
	if (!(is_equation_form(str) && check_variable(str)
		&& check_invalid_character(str) && check_number(str)))
		return ("");
	remove_space(str);
	return (this->_str);
}

void	InputConvertor::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "InputConvertor.cpp";
	this->_struct_error.cat = "input error";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;
	this->_struct_error.pos = pos;

	this->_struct_error.pos_str = "\t\t  " + this->_str + "\n";
	this->_struct_error.pos_str += "\t\t  ";
	this->_struct_error.pos_str += RED;
	if (pos != std::string::npos && pos >= 1)
	{
		for (size_t i = 0; i < pos - 1; i++)
			this->_struct_error.pos_str += "~";
	}
	this->_struct_error.pos_str += "^";
	this->_struct_error.pos_str += BLACK;
	throw (ParseError::ParseException(this->_struct_error));
}

int	InputConvertor::check_equal_sign(std::string str)
{
	int	flag = 0;
	size_t	i = 0;
	
	while (i < str.length())
	{
		if (str[i] == '=')
			flag++;
		if (flag > 1)
			throw_err_msg("InputConvertor::check_equal_sign(std::string str)",
				"equal(=) sign used multiple times", i);
		i++;
	}
	if (!flag)
		throw_err_msg("InputConvertor::check_equal_sign(std::string str)",
			"equal(=) sign is missing", i);
	return (1);
}

int 	InputConvertor::check_each_term(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '=')
			throw_err_msg("InputConvertor::check_each_term(std::string str)",
				"invalid equation form: left term does not exist", i);

		while (str[i] != '=')
			i++;
		i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] != '\0')
			break ;
		else
			throw_err_msg("InputConvertor::check_each_term(std::string str)",
				"invalid equation form: right term does not exist", i);
	}
	return (1);
}

int	InputConvertor::is_equation_form(std::string str)
{
	return (check_equal_sign(str) && check_each_term(str));
}

int	InputConvertor::set_variable(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))
		{
			this->_info.variable = str[i];
			break ;
		}
		i++;
	}

	if (this->_info.variable == 0)
		throw_err_msg("InputConvertor::set_variable(std::string str)",
				"cannot determine a variable", str.length());
	return (1);
}

int	InputConvertor::check_duplicate(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == this->_info.variable)
		{
			i++;
			if (str[i] == this->_info.variable)
				throw_err_msg("InputConvertor::check_duplicate(std::string str)",
					"inappropriate variable form", i);
		}
		i++;
	}
	return (1);
}

int	InputConvertor::check_variable(std::string str)
{
	return (set_variable(str) && check_duplicate(str));
}

int	InputConvertor::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(str[i] == this->_info.variable || ('0' <= str[i] && str[i] <= '9')
			|| str[i] == '.' || str[i] == '^' || str[i] == '(' || str[i] == ')'
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
			|| str[i] == '=' || str[i] == ' ' || str[i] == '\t'))
			throw_err_msg("InputConvertor::check_invalid_character(std::string str)",
					"cannot determine the variable", i);
		i++;
	}
	return (1);
}

int	InputConvertor::check_number(std::string str)
{
	size_t	i = 0;
	int	space = 0;

	while (i < str.length())
	{
		space = 0;
		if ('0' <= str[i] && str[i] <= '9')
		{
			i++;
			while (str[i] == ' ' || str[i] == '\t')
			{
				space++;
				i++;
			}
			if (space && ('0' <= str[i] && str[i] <= '9'))
				throw_err_msg("InputConvertor::check_number(std::string str)",
					"invalid syntax: no operator between numbers", i - 1);
		}
		i++;
	}
	return (1);
}

void	InputConvertor::remove_space(std::string &str)
{
	size_t		i = 0;
	std::string	new_str = "";

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (i < str.size())
	{
		if (str[i] != ' ' && str[i] != '\t')
			new_str += str[i];
		i++;
	}
	str = new_str;
	this->_str = str;
}
