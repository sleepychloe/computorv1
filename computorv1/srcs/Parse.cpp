/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/17 01:16:18 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse()
{
}

Parse::Parse(char *argv): _variable(0), _err_msg("")
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
	this->_variable = parse._variable;
	this->_l_term = parse._l_term;
	this->_r_term = parse._r_term;
	this->_l_degree = parse._l_degree;
	this->_r_degree = parse._r_degree;
	this->_reduced_form = parse._reduced_form;
	this->_degree = parse._degree;
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

	if (!(get_term(str.substr(0, str.find("=")),
			this->_l_term, this->_l_degree)
		&& get_term(str.substr(str.find("=") + 1, std::string::npos),
			this->_r_term, this->_r_degree)
		&& make_reduced_form()))
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
		while (str[i] == ' ' || str[i] == '\t')
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

	while (('0' <= str[i] && str[i] <= '9') || str[i] == '.'
		|| str[i] == ' ' || str[i] == '\t'
		|| str[i] == '=' || str[i] == '(' || str[i] == ')' 
		|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' )
		i++;
	this->_variable = str[i];
	i++;
	while (1)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '^' || str[i] == '.'
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
			|| str[i] == '=' || str[i] == '(' || str[i] == ')' || str[i] == '\0')
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
		if (!(('0' <= str[i] && str[i] <= '9')
			|| str[i] == this->_variable || str[i] == '.'
			|| str[i] == '^' || str[i] == '(' || str[i] == ')'
			|| str[i] == ' ' || str[i] == '\t' || str[i] == '='
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'))
		{
			this->_err_msg = "invalid syntax: invalid character";
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
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}

	i = str.find("=") - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
	{
		this->_err_msg = "invalid syntax: operator";
		throw (this->_err_msg);
	}

	i = str.length() - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
	{
		this->_err_msg = "invalid syntax: operator";
		throw (this->_err_msg);
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
			while (str[i] == ' ' || str[i] == '\t')
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

int	Parse::check_point(std::string str)
{
	size_t	i = 0;
	int	point;

	while (i < str.length())
	{
		point = 0;
		if (str[i] == '.')
		{
			point++;
			if (!((str[i - 1] && ('0' <= str[i - 1] && str[i - 1] <= '9'))
				&& (str[i + 1] && ('0' <= str[i + 1] && str[i + 1] <= '9'))))
			{
				this->_err_msg = "invalid syntax: float point";
				throw (this->_err_msg);
			}
			i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
			{
				while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
				{
					if (str[i] == '.')
						point++;
					i++;
				}
				if (str[i - 1] == '.' || point >= 2)
				{
					this->_err_msg = "invalid syntax: float point";
					throw (this->_err_msg);
				}
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
				this->_err_msg = "invalid syntax: caret(^)";
				throw (this->_err_msg);
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_syntax(std::string str)
{
	if (!(check_invalid_character(str) && check_brackets(str) && check_sign(str)
		&& check_number(str) && check_point(str) && check_caret(str)))
		return (0);
	return (1);
}

void	Parse::remove_space(std::string	&str)
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
}

std::vector<std::string>	Parse::split_term(std::string str)
{
	std::vector<std::string>	term;
	size_t				i = 0;
	size_t				open = 0;
	std::string tmp;
	remove_space(str);

	while (1)
	{
		i = 0;
		if (str[0] == '+' || str[0] == '-')
			i++;
		while (str[i] != '+' && str[i] != '-' && str[i] != '\0')
		{
			if (str[i] == '(')
			{
				tmp = str;
				while (tmp.find("(") < tmp.find(")"))
				{
					open++;
					i += tmp.find("(");
					tmp = tmp.substr(i + 1, std::string::npos);
				}
				while (open)
				{
					i += tmp.find(")");
					tmp = tmp.substr(i + 1, std::string::npos);
					open--;
				}
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

float	Parse::find_degree(std::string str)
{
	float	degree = 0;
	int	sign = 1;
	size_t	i;
	size_t	tmp;

	i = str.find(this->_variable);
	while (i < str.length())
	{
		if (str[i] == this->_variable
			&& str[i + 1] && str[i + 1] == '^')
		{
			i = i + 2;
			tmp = i;
			while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
				i++;
			degree += sign * atof(str.substr(tmp, i - tmp + 1).c_str());
		}
		else if (str[i] == this->_variable)
			degree += sign * 1;

		if (str[i] == '(')
		{
			while (str[i] != ')')
				i++;
		}
		if (str[i] == '*')
			sign = 1;
		if (str[i] == '/')
			sign = -1;
		i++;
	}
	return (degree);
}

int	Parse::remove_variable(std::string &str)
{
	size_t		i = 0;
	size_t		start;
	size_t		end;
	std::string	tmp;

	while (i < str.length())
	{
		if (str[i] == this->_variable)
		{
			if (i == 0)
			{
				str = "1*" + str;
				i = i + 2;
			}
			if (i != 0 && (str[i - 1] == '+' || str[i - 1] == '-'))
			{
				tmp = "1*" + std::string(1, this->_variable);
				str = str.substr(0, i - 1) + tmp + str.substr(i + 1, std::string::npos);
				i = str.substr(0, i).length() + tmp.length();
			}
		}
		i++;
	}

	i = 0;
	while (i < str.length())
	{
		tmp = "";
		if ((str[i] == this->_variable)
			|| (str[i] == this->_variable && str[i + 1] && str[i + 1] == '^'))
		{
			start = i;
			i++;
			if (str[i] == '^')
				i++;
			while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
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

int	Parse::check_operation(std::string str)
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

void	Parse::split_expression(std::string str,
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
		if (((str[i] == '+' || str[i] == '-') &&
				str[i - 1] && str[i - 1] != '*' && str[i - 1] != '/')
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

float	Parse::calc(float nb1, float nb2, char op)
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
		{
			this->_err_msg = "cannot divided by 0";
			throw (this->_err_msg);
		}
		res = nb1 / nb2;
	}
	return (res);
}

std::string	Parse::calculate(std::string str)
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
	return (std::to_string(nb[0]));
}

int	Parse::remove_bracket(std::string &str)
{
	size_t		i = 0;
	size_t		open;
	size_t		close;
	std::string	tmp;

	while (str.find(")") != std::string::npos)
	{
		i = str.find(")");
		close = i;
		while (str[i] != '(')
			i--;
		open = i;

		tmp = str.substr(open + 1, close - open - 1);
		tmp = calculate(tmp);
		str = str.substr(0, open) + tmp + str.substr(close + 1, std::string::npos);
	}
	return (1);
}

int	Parse::get_term(std::string str,
			std::vector<std::string> &term, std::vector<float> &degree)
{
	term = split_term(str);
	for (size_t i = 0; i < term.size(); i++)
		degree.push_back(find_degree(term[i]));
	for (std::vector<std::string>::iterator it = term.begin(); it != term.end(); it++)
	{
		if (!(remove_variable(*it) && remove_bracket(*it)))
			return (0);
	}
	for (size_t i = 0; i < term.size(); i++)
		term[i] = calculate(term[i]);

	for (size_t i = 0; i < term.size(); i++)
	{
		for (size_t j = i + 1; j < term.size(); j++)
		{
			if (degree[i] == degree[j])
			{
				term[i] = std::to_string(atof(term[i].c_str())
						+ atof(term[j].c_str()));
				term.erase(term.begin() + j);
				degree.erase(degree.begin() + j);
				j--;
			}
		}
	}
	return (1);
}

int	Parse::make_reduced_form(void)
{
	for (size_t i = 0; i < this->_l_term.size(); i++)
	{
		this->_reduced_form.push_back(this->_l_term[i]);
		this->_degree.push_back(this->_l_degree[i]);
	}
	for (size_t i = 0; i < this->_r_term.size(); i++)
	{
		if (this->_r_term[i][0] == '-')
			this->_reduced_form.push_back("+" + this->_r_term[i].substr(1, std::string::npos));
		else
			this->_reduced_form.push_back("-" + this->_r_term[i]);
		this->_degree.push_back(this->_r_degree[i]);
	}
	for (size_t i = 0; i < this->_reduced_form.size(); i++)
	{
		for (size_t j = i + 1; j < this->_reduced_form.size(); j++)
		{
			if (this->_degree[i] == this->_degree[j])
			{
				this->_reduced_form[i]
					= std::to_string(atof(this->_reduced_form[i].c_str())
						+ atof(this->_reduced_form[j].c_str()));
				this->_reduced_form.erase(this->_reduced_form.begin() + j);
				this->_degree.erase(this->_degree.begin() + j);
				j--;
			}
		}
	}
	for (size_t i = 0; i < this->_reduced_form.size(); i++)//
		std::cout << "term[" << i << "]: " << this->_reduced_form[i] << std::endl;//
	for (size_t i = 0; i < this->_degree.size(); i++)//
		std::cout << "degree[" << i << "]: " << this->_degree[i] << std::endl;//
	return (1);
}
