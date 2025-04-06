/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxChecker.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 03:49:40 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:13:11 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Parse/SyntaxChecker.hpp"

SyntaxChecker::SyntaxChecker()
{
}

SyntaxChecker::SyntaxChecker(std::string str, t_parse info): _str(str), _info(info)
{
}

SyntaxChecker::SyntaxChecker(const SyntaxChecker& checker)
{
	*this = checker;
}

SyntaxChecker& SyntaxChecker::operator=(const SyntaxChecker& checker)
{
	if (this == &checker)
		return (*this);
	this->_str = checker._str;
	this->_info = checker._info;
	this->_struct_error = checker._struct_error;
	return (*this);
}

SyntaxChecker::~SyntaxChecker()
{
}

t_parse SyntaxChecker::get_info(void) const
{
	return (this->_info);
}

std::string	SyntaxChecker::check(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_each_str(LEFT_STR, left_str)
		&& check_each_str(RIGHT_STR, right_str)))
		return ("");

	if (!(check_point(str) && check_caret(str)))
		return ("");
	return (this->_str);
}

void	SyntaxChecker::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "SyntaxChecker.cpp";
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

int	SyntaxChecker::check_brackets(int str_type, std::string str)
{
	std::stack<char>	stack;
	size_t			pos = 0;
	size_t			i = 0;

	if (str.find(std::string(1, ')')) == std::string::npos
		&& str.find(std::string(1, '(')) == std::string::npos)
		return (1);

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;
	while (i < str.length())
	{
		if (str[i] == '(')
			stack.push(str[i]);
		if (str[i] == ')')
		{
			
			if (str[i - 1] && str[i - 1] == '(')
				throw_err_msg("SyntaxChecker::check_brackets(int str_type, std::string str)",
					"incorrect use of brackets: no character in the brackets", pos + i);
			if (stack.empty())
				throw_err_msg("SyntaxChecker::check_brackets(int str_type, std::string str)",
					"incorrect use of brackets: bracket(s) not pair", pos + i);
			stack.pop();
		}
		i++;
	}
	if (!stack.empty())
		throw_err_msg("SyntaxChecker::check_brackets(int str_type, std::string str)",
			"incorrect use of brackets: bracket(s) not pair", pos + i - 1);
	return (1);
}

int	SyntaxChecker::check_operator_first_last(std::string str, int pos)
{
	if (str[0] == '*' || str[0] == '/')
		throw_err_msg("check_operator_first_last(std::string str, int pos)",
			"incorrect use of operator", pos);

	if (str[str.length() - 1] == '+' || str[str.length() - 1] == '-'
		|| str[str.length() - 1] == '*' || str[str.length() - 1] == '/')
		throw_err_msg("check_operator_first_last(std::string str, int pos)",
			"incorrect use of operator", pos + str.length() - 1);
	return (1);
}

int	SyntaxChecker::check_operator_duplicate(std::string str, int pos)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			i++;
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
				throw_err_msg("SyntaxChecker::check_operator_duplicate(std::string str, int pos)",
					"incorrect use of operator", pos + i);
		}
		i++;
	}
	return (1);
}

int	SyntaxChecker::check_operator_operand(std::string str, int pos)
{
	size_t	i = 0;

	while (str[i] == '+' || str[i] == '-' || str[i] == '(')
		i++;
	while (i < str.length())
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			i++;
			while (str[i] == this->_info.variable || str[i] == '^'
				|| ('0' <= str[i] && str[i] <= '9') || str[i] == '.'
				|| str[i] == '+' || str[i] == '-'
				|| str[i] == '(' || str[i] == ')')
				i++;
			if (!(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
				|| str[i] == '\0'))
				throw_err_msg("SyntaxChecker::check_operator_operand(std::string str, int pos)",
					"incorrect use of operator", pos + i);
		}
		i++;
	}
	return (1);
}

int	SyntaxChecker::check_operator_between_variable(std::string str, int pos)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == this->_info.variable)
		{
			i++;
			if (str[i] == this->_info.variable)
				throw_err_msg("SyntaxChecker::check_operator_between_variable(std::string str, int pos)",
					"incorrect use of operator", pos + i);
		}
		i++;
	}
	return (1);
}

int	SyntaxChecker::check_operator_between_brackets(std::string str, int pos)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == ')' && str[i + 1] && str[i + 1] == '(')
			throw_err_msg("SyntaxChecker::check_operator_between_brackets(std::string str, int pos)",
				"incorrect use of operator", pos + i);
		i++;
	}
	return (1);
}

int	SyntaxChecker::check_operator(int str_type, std::string str)
{
	size_t	pos = 0;
	

	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	return (check_operator_first_last(str, pos) && check_operator_duplicate(str, pos)
		&& check_operator_operand(str, pos) && check_operator_between_variable(str, pos)
		&& check_operator_between_brackets(str, pos));
}

int	SyntaxChecker::check_each_str(int str_type, std::string str)
{
	if (!(check_brackets(str_type, str)
		&& check_operator(str_type, str)))
		return (0);
	return (1);
}

int	SyntaxChecker::check_point(std::string str)
{
	size_t	i = 0;
	int	point;
	int	digit;

	while (i < str.length())
	{
		point = 0;
		digit = 0;
		if (str[i] == '.')
		{
			point++;
			if (!((str[i - 1] && ('0' <= str[i - 1] && str[i - 1] <= '9'))
				&& (str[i + 1] && ('0' <= str[i + 1] && str[i + 1] <= '9'))))
				throw_err_msg("SyntaxChecker::check_point(std::string str)",
					"incorrect use of float point", i);
			i++;

			if (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
			{
				while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
				{
					if (str[i] == '.')
					{
						point++;
						if (point > 1)
							throw_err_msg("SyntaxChecker::check_point(std::string str)",
								"incorrect use of float point", i);
					}
					else
					{
						digit++;
						if (digit > 5)
							throw_err_msg("SyntaxChecker::check_point(std::string str)",
								"incorrect use of float point: supports up to the fifth decimal place",
								i);
					}
					i++;
				}
			}
		}
		i++;
	}
	return (1);
}

int	SyntaxChecker::check_caret(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (str[i] == '^')
		{
			if (!(str[i - 1] && (str[i - 1] == this->_info.variable)
				&& (str[i + 1] && '0' <= str[i + 1] && str[i + 1] <= '9')))
				throw_err_msg("SyntaxChecker::check_caret(std::string str)",
					"incorrect use of caret(^)", i);

			i++;
			if ('0' <= str[i] && str[i] <= '9')
			{
				while ('0' <= str[i] && str[i] <= '9')
					i++;
				if (!(str[i] == '+' || str[i] == '-'
					|| str[i] == '*' || str[i] == '/' || str[i] == '=' || str[i] == '\0'))
					throw_err_msg("SyntaxChecker::check_caret(std::string str)",
						"incorrect use of caret(^)", i);
				i++;
			}
		}
		i++;
	}
	return (1);
}
