/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/14 22:55:09 by yhwang           ###   ########.fr       */
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
	
	std::string	left_term = str.substr(0, str.find("="));
	std::string	right_term = str.substr(str.find("=") + 1, std::string::npos);

	if (!get_term(left_term))
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

std::vector<std::string>	Parse::split_term(std::string str)
{
	std::vector<std::string>	term;
	size_t				i = 0;

	while (1)
	{
		i = str.find(this->_variable);
		while (!(str[i] == '+' || str[i] == '-'))
		{
			if (str[i] == '(')
			{
				while (str[i] != ')')
					i++;
			}
			i++;
		}
		term.push_back(str.substr(0, i));
		str = str.substr(i, std::string::npos);
		if (str.find(this->_variable) != std::string::npos)
			continue ;
		term.push_back(str);
		break ;
	}

	std::string	tmp;
	size_t		j;

	for (size_t i = 0; i < term.size(); i++)
	{
		j = 0;
		tmp = "";
		while (term[i][j] == ' ')
			j++;
		if (term[i][j] == '+')
			j++;

		while (j < term[i].size())
		{
			if (term[i][j] != ' ')
				tmp += term[i][j];
			j++;
		}
		term[i] = tmp;
	}
	return (term);
}

std::vector<int>	Parse::find_degree(std::vector<std::string> term)
{
	std::vector<int>	degree;
	size_t			i;
	int			tmp_degree;
	int			tmp_i;
	int			sign;
	
	for (std::vector<std::string>::iterator it = term.begin(); it != term.end(); it++)
	{
		i = (*it).find(this->_variable);
		tmp_degree = 0;
		tmp_i = 0;
		sign = 1;

		while (i < (*it).length())
		{
			if ((*it)[i] == this->_variable && (*it)[i + 1] && (*it)[i + 1] == '^')
			{
				i = i + 2;
				tmp_i = i;
				while ('0' <= (*it)[i] && (*it)[i] <= '9')
					i++;
				tmp_degree += sign * atoi((*it).substr(tmp_i, i - tmp_i + 1).c_str());
			}
			else if ((*it)[i] == this->_variable)
			{
				tmp_degree += sign * 1;
			}
			if ((*it)[i] == '(')
			{
				while ((*it)[i] != ')')
					i++;
			}
			if ((*it)[i] == '*')
				sign = 1;
			if ((*it)[i] == '/')
				sign = -1;
			i++;
		}
		degree.push_back(tmp_degree);
	}
	return (degree);
}

std::vector<std::string>	Parse::remove_variable(std::vector<std::string> term)
{
	size_t		i;
	size_t		start;
	size_t		end;
	std::string	tmp;

	for (std::vector<std::string>::iterator it = term.begin(); it != term.end(); it++)
	{
		i = 0;
		while (i < (*it).length())
		{
			tmp = "";
			if (((*it)[i] == this->_variable && (*it)[i + 1] && (*it)[i + 1] == '^')
				|| (*it)[i] == this->_variable)
			{
				start = i;
				i++;
				if ((*it)[i] == '^')
					i++;
				while ('0' <= (*it)[i] && (*it)[i] <= '9')
					i++;
				end = i - 1;
				if (!((*it)[start - 1] == '*' || (*it)[start - 1] == '/'))
					tmp += "*";
				tmp += "1";
				if ((*it)[end + 1] && !((*it)[end + 1] == '*' || (*it)[end + 1] == '/'))
					tmp += "*";
				term.at(std::distance(term.begin(), it))
					= (*it).substr(0, start) + tmp
						+ (*it).substr(end + 1, std::string::npos);
				i = (*it).substr(0, start).length() + tmp.length();
			}
			i++;
		}
	}
	return (term);
}

std::string	Parse::calculate(std::string str)
{
	std::string	res;
	size_t		cnt = 0;
	size_t		i = 0;

	i = 0;
	while (i < str.length())
	{
		if ((i == 0 && (str[i] == '+' || str[i] == '-'))
			|| (i != 0 && ((str[i - 1] == '*' || str[i - 1] == '/'))
					&& (str[i] == '+' || str[i] == '-')))
			i++;
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			cnt++;
		i++;
	}
	if (!cnt)
		return (str);

	std::vector<std::string>	nb_str;
	std::vector<float>		nb;
	std::vector<std::string>	op;
	
	i = 0;
	size_t		j = 0;
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
		if ((i != 0 && str[i - 1] && str[i - 1] != '*' && str[i - 1] != '/'
				&& (str[i] == '+' || str[i] == '-') )
			|| str[i] == '*' || str[i] == '/')
		{
			nb_str.push_back(tmp);
			tmp = "";
			op.push_back(std::string(1, str[i]));
			j++;
		}
		i++;
	}
	nb_str.push_back(tmp);

	i = 0;
	while (i < nb_str.size())
	{
		nb.push_back(atof(nb_str[i].c_str()));
		i++;
	}

	float		nb1;
	float		nb2;
	std::string	o;

	i = 0;
	while (i < op.size())
	{
		if (op[i] == "*" || op[i] == "/")
		{
			o = op[i];
			op.erase(op.begin() + i);

			nb1 = nb[i];
			nb2 = nb[i + 1];
			std::cout << "nb1: " << nb1 << ", nb2: " << nb2 << std::endl;
			nb.erase(nb.begin() + i + 1);
			if (o == "*")
				nb[i] = nb1 * nb2;
			else
			{
				if (nb2 == 0)
				{
					this->_err_msg = "cannot divided by 0";
					throw (this->_err_msg);
				}
				nb[i] = nb1 / nb2;
			}
			i--;
		}
		i++;
	}

	i = 0;
	while (i < op.size())
	{
		if (op[i] == "+" || op[i] == "-")
		{
			o = op[i];
			op.erase(op.begin() + i);

			nb1 = nb[i];
			nb2 = nb[i + 1];
			nb.erase(nb.begin() + i + 1);
			if (o == "+")
				nb[i] = nb1 + nb2;
			else
				nb[i] = nb1 - nb2;
			i--;
		}
		i++;
	}

	std::cout << "nb: " << nb[0] << std::endl;//
	res = std::to_string(nb[0]);
	std::cout << "res: " << res << std::endl;
	return (res);
}

std::vector<std::string>	Parse::remove_bracket(std::vector<std::string> term)
{
	size_t		i;
	size_t		open;
	size_t		close;
	std::string	substr;

	for (std::vector<std::string>::iterator it = term.begin(); it != term.end(); it++)
	{
		while ((*it).find(")") != std::string::npos)
		{
			i = (*it).find(")");
			while ((*it)[i] != ')')
				i++;
			close = i;
			while ((*it)[i] != '(')
				i--;
			open = i;
			substr = (*it).substr(open + 1, close - open - 1);
			substr = calculate(substr);
			term.at(std::distance(term.begin(), it))
				= (*it).substr(0, open) + substr + (*it).substr(close + 1, std::string::npos);
		}
	}
	return (term);
}

int	Parse::get_term(std::string str)
{
	//split term
	std::vector<std::string>	term = split_term(str);
	//find degree
	std::vector<int>		degree = find_degree(term);

	for (size_t i = 0; i < term.size(); i++)//
		std::cout << "term[" << i << "]: " << term[i] << std::endl;//

	for (size_t i = 0; i < degree.size(); i++)//
		std::cout << "degree[" << i << "]: " << degree[i] << std::endl;//

	//handle bracket
	term = remove_bracket(term);

	term = remove_variable(term);

	//simplify
	for (size_t i = 0; i < term.size(); i++)
		term[i] = calculate(term[i]);

	for (size_t i = 0; i < term.size(); i++)//
		std::cout << "term[" << i << "]: " << term[i] << std::endl;//
	return (1);
}
