/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TermAnalyzer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 06:06:22 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:13:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Parse/TermAnalyzer.hpp"

TermAnalyzer::TermAnalyzer()
{
}

TermAnalyzer::TermAnalyzer(std::string str, t_parse info): _str(str), _info(info)
{
}

TermAnalyzer::TermAnalyzer(const TermAnalyzer& analyzer)
{
	*this = analyzer;
}

TermAnalyzer& TermAnalyzer::operator=(const TermAnalyzer& analyzer)
{
	if (this == &analyzer)
		return (*this);
	this->_str = analyzer._str;
	this->_info = analyzer._info;
	this->_struct_error = analyzer._struct_error;
	return (*this);
}

TermAnalyzer::~TermAnalyzer()
{
}

t_parse TermAnalyzer::get_info(void) const
{
	return (this->_info);
}

void	TermAnalyzer::throw_err_msg(std::string function, std::string err_msg, size_t pos)
{
	pos++;
	this->_struct_error.file_name = "TermAnalyzer.cpp";
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

std::vector<std::string>	TermAnalyzer::split_term(std::string str)
{
	std::vector<std::string>	term;
	size_t				i = 0;
	std::string			tmp;

	while (1)
	{
		i = 0;
		if (str[0] == '+' || str[0] == '-')
			i++;
		while (str[i] != '+' && str[i] != '-' && str[i] != '\0')
		{
			if ((str[i] == '*' || str[i] == '/')
				&& (str[i + 1]) && (str[i + 1] == '+' || str[i + 1] == '-'))
				i = i + 2;
			if (str[i] == '^')
			{
				if (str[i + 1] && (str[i + 1] == '+' || str[i + 1] == '-'))
					i = i + 2;
			}
			tmp = "";
			i++;
		}
		term.push_back(str.substr(0, i));
		if (i == str.length())
			break ;
		str = str.substr(i, std::string::npos);
	}
	return (term);
}

float	TermAnalyzer::find_degree(std::string str)
{
	float	degree = 0;
	int	sign = 1;
	size_t	i = 0;
	size_t	tmp;

	while (i < str.length())
	{
		if (str[i] == '*')
			sign = 1;
		else if (str[i] == '/')
			sign = -1;

		if (str[i] == this->_info.variable
			&& str[i + 1] && str[i + 1] == '^')
		{
			i = i + 2;
			tmp = i;
			while ('0' <= str[i] && str[i] <= '9')
				i++;
			degree += sign * atof(str.substr(tmp, i - tmp).c_str());
		}
		else if (str[i] == this->_info.variable)
			degree += sign * 1;
		i++;
	}
	return (degree);
}

void	TermAnalyzer::add_coefficient_of_variable(std::string &str)
{
	size_t		i = 0;
	std::string	tmp;

	while (i < str.length())
	{
		if (str[i] == this->_info.variable)
		{
			if (i == 0)
			{
				str = "1*" + str;
				i = i + 2;
			}
			if (i != 0 && (str[i - 1] == '+' || str[i - 1] == '-'))
			{
				tmp = "1*" + std::string(1, this->_info.variable);
				if (str[i - 1] == '-')
					tmp = "-1*" + std::string(1, this->_info.variable);
				str = str.substr(0, i - 1) + tmp + str.substr(i + 1, std::string::npos);
				i = str.substr(0, i).length() + tmp.length();
			}
		}
		i++;
	}
}

int	TermAnalyzer::remove_variable(std::string &str)
{
	size_t		i = 0;
	size_t		start;
	size_t		end;
	std::string	tmp;

	add_coefficient_of_variable(str);

	while (i < str.length())
	{
		tmp = "";
		if ((str[i] == this->_info.variable)
			|| (str[i] == this->_info.variable && str[i + 1] && str[i + 1] == '^'))
		{
			start = i;
			i++;
			if (str[i] == '^')
				i++;
			while ('0' <= str[i] && str[i] <= '9')
				i++;
			end = i - 1;
			if (!(str[start - 1] == '*' || str[start - 1] == '/'))
				tmp += "*";
			tmp += "1";
			if (str[end + 1] && !(str[end + 1] == '*' || str[end + 1] == '/'))
				tmp += "*";
			str = str.substr(0, start) + tmp + str.substr(end + 1, std::string::npos);
			i = str.substr(0, start).length() + tmp.length();
		}
		i++;
	}
	return (1);
}

int	TermAnalyzer::check_operation(std::string str)
{
	size_t	i = 0;
	size_t	cnt = 0;

	if (str[i] == '+' || str[i] == '-')
		i++;

	while (i < str.length())
	{
		if (i != 0 && (str[i - 1] == '*' || str[i - 1] == '/')
			&& (str[i] == '+' || str[i] == '-'))
			i++;
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			cnt++;
		i++;
	}
	if (!cnt)
		return (0);
	return (1);
}

void	TermAnalyzer::split_expression(std::string str,
				std::vector<float> &nb, std::vector<char> &op)
{
	size_t		i = 0;
	std::string	tmp = "";

	while (i < str.length())
	{
		if ((str[i] == '+' || str[i] == '-'))
			tmp += str[i];
		while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
		{
			tmp += str[i];
			i++;
		}
		if ((i > 0 && str[i - 1] != '*' && str[i - 1] != '/'
			&& (str[i] == '+' || str[i] == '-'))
			|| str[i] == '*' || str[i] == '/')
		{
			nb.push_back(atof(tmp.c_str()));
			op.push_back(str[i]);
			tmp = "";
		}
		i++;
	}
	nb.push_back(atof(tmp.c_str()));
}

float	TermAnalyzer::calc(float nb1, float nb2, char op)
{
	float	res;

	if (op == '+')
		res = nb1 + nb2;
	else if (op == '-')
		res = nb1 - nb2;
	else if (op == '*')
		res = nb1 * nb2;
	else
	{
		if (nb2 == 0)
			throw_err_msg("InputConvertor::check_equal_sign(std::string str)",
				"equal(=) sign used multiple times", this->_str.find("/0"));
		res = nb1 / nb2;
	}
	return (res);
}

std::string	TermAnalyzer::calculate(std::string str)
{
	if (!check_operation(str))
	{
		if (str[0] == '+')
			str = str.substr(1, std::string::npos);
		return (str);
	}

	std::vector<float>	nb;
	std::vector<char>	op;

	split_expression(str, nb, op);

	size_t		i = 0;

	while (i < op.size())
	{
		if (op[i] == '*' || op[i] == '/')
		{
			nb[i] = calc(nb[i], nb[i + 1], op[i]);
			op.erase(op.begin() + i);
			nb.erase(nb.begin() + i + 1);
			i--;
		}
		i++;
	}

	i = 0;
	while (i < op.size())
	{
		if (op[i] == '+' || op[i] == '-')
		{
			nb[i] = calc(nb[i], nb[i + 1], op[i]);
			op.erase(op.begin() + i);
			nb.erase(nb.begin() + i + 1);
			i--;
		}
		i++;
	}
	return (float_to_string(nb[0]));
}

int	TermAnalyzer::get_term(std::string str,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	term_degree.first = split_term(str);
	for (size_t i = 0; i < term_degree.first.size(); i++)
		term_degree.second.push_back(find_degree(term_degree.first[i]));
	for (std::vector<std::string>::iterator it = term_degree.first.begin();
		it != term_degree.first.end(); it++)
	{
		if (!remove_variable(*it))
			return (0);
	}
	for (size_t i = 0; i < term_degree.first.size(); i++)
		term_degree.first[i] = calculate(term_degree.first[i]);

	for (size_t i = 0; i < term_degree.first.size(); i++)
	{
		for (size_t start = i + 1; start < term_degree.first.size(); start++)
		{
			if (term_degree.second[i] == term_degree.second[start])
			{
				term_degree.first[i]
					= float_to_string(atof(term_degree.first[i].c_str())
							+ atof(term_degree.first[start].c_str()));
				term_degree.first.erase(term_degree.first.begin() + start);
				term_degree.second.erase(term_degree.second.begin() + start);
				start--;
			}
		}
	}
	return (1);
}
