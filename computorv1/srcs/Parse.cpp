
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:12:16 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/20 11:34:55 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _variable(0), _max_degree(0), _equation_type(0),
		_flag_bonus(0), _equation_str(""), _err_msg("")
{
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
	this->_reduced_form = parse._reduced_form;
	this->_degree = parse._degree;
	this->_max_degree = parse._max_degree;
	this->_equation_type = parse._equation_type;
	this->_flag_bonus = parse._flag_bonus;
	this->_equation_str = parse._equation_str;
	this->_err_msg = parse._err_msg;
	return (*this);
}

Parse::~Parse()
{
}

char	Parse::get_variable(void)
{
	return (this->_variable);
}

std::vector<float>	Parse::get_reduced_form(void)
{
	return (this->_reduced_form);
}

std::vector<float>	Parse::get_degree(void)
{
	return (this->_degree);
}

int	Parse::get_equation_type(void)
{
	return (this->_equation_type);
}

int	Parse::get_flag_bonus(void)
{
	return (this->_flag_bonus);
}

std::string	Parse::get_equation_str(void)
{
	return (this->_equation_str);
}

void	Parse::parse_start(char *argv, int flag_bonus)
{
	std::string	str(argv);

	this->_flag_bonus = flag_bonus;
	check_str(str);
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

	while (i < str.length())
	{
		if (('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))
		{
			this->_variable = str[i];
			break ;
		}
		i++;
	}
	if (this->_variable == 0)
	{
		this->_err_msg = "cannot determine the variable";
		throw (this->_err_msg);
	}
	return (1);
}

int	Parse::check_invalid_character(std::string str)
{
	size_t	i = 0;

	while (i < str.length())
	{
		if (!(str[i] == this->_variable || ('0' <= str[i] && str[i] <= '9')
			|| str[i] == '.' || str[i] == '^' || str[i] == '(' || str[i] == ')'
			|| str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
			|| str[i] == '=' || str[i] == ' ' || str[i] == '\t'))
		{
			this->_err_msg = "cannot determine the variable";
			throw (this->_err_msg);
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
			{
				this->_err_msg = "invalid syntax: no operator between numbers";
				throw (this->_err_msg);
			}
		}
		i++;
	}
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
		}
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
			if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
			{
				this->_err_msg = "invalid syntax: operator";
				throw (this->_err_msg);
			}
		}
		i++;
	}

	i = 0;
	while (str[i] == '+' || str[i] == '-' || str[i] == '(')
		i++;
	while (i < str.length())
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			i++;
			while (str[i] == this->_variable || str[i] == '^'
				|| ('0' <= str[i] && str[i] <= '9') || str[i] == '.'
				|| str[i] == '+' || str[i] == '-'
				|| str[i] == '(' || str[i] == ')')
				i++;
			if (!(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'
				|| str[i] == '\0'))
			{
				this->_err_msg = "invalid syntax: operator";
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
			{
				this->_err_msg = "invalid syntax: float point";
				throw (this->_err_msg);
			}
			i++;

			if (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
			{
				while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
				{
					if (str[i] == '.')
						point++;
					else
						digit++;
					i++;
				}
				if (str[i - 1] == '.' || point >= 2 || digit > 5)
				{
					this->_err_msg = "invalid syntax: float point";
					if (digit > 2)
						this->_err_msg += ": supports up to the fifth decimal place";
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
			if (!((str[i - 1] && (str[i - 1] == this->_variable))
				&& (str[i + 1] && (str[i + 1] == '+' || str[i + 1] == '-'
						|| ('0' <= str[i + 1] && str[i + 1] <= '9')))))
			{
				this->_err_msg = "invalid syntax: caret(^)1";
				throw (this->_err_msg);
			}
			i++;
			if (str[i] == '+' || str[i] == '-'
				|| ('0' <= str[i + 1] && str[i + 1] <= '9'))
			{
				while (str[i] == '+' || str[i] == '-'
					|| ('0' <= str[i] && str[i] <= '9') || str[i] == '.')
					i++;
				if (!(str[i] == '+' || str[i] == '-'
					|| str[i] == '*' || str[i] == '/' || str[i] == '='))
				{
					this->_err_msg = "invalid syntax: caret(^)";
					throw (this->_err_msg);
				}
			}
		}
		i++;
	}
	return (1);
}

int	Parse::check_syntax(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(check_brackets(left_str) && check_brackets(right_str)
		&& check_sign(left_str) && check_brackets(right_str)
		&& check_point(str) && check_caret(str)))
		return (0);
	return (1);
}

int	Parse::reduce_bracket(std::string &str)
{
	size_t		start = 0;
	size_t		end = 0;

	std::string	tmp = "";
	std::string	front = "";
	std::string	back = "";
	std::vector<float>		term;
	std::vector<float>		degree;
	std::vector<std::string>	tmp_term;
	std::vector<float>		tmp_degree;
	std::vector<float>		tmp_term_float;

	std::vector<char>		op;
	std::vector<float>		nb;
	int				keep;

	
	end = str.find(")");
	//no need to calculate in the bracket
	while (1)
	{
		if (str[end] == '\0' || str.find(")") == std::string::npos)
			break ;
		while (str[end] != ')' && str[end] != '\0')
			end++;
		if (str[end] == '\0')
			break ;
		start = end;
		while (str[start] != '(')
			start--;
		front = str.substr(0, start);
		tmp = str.substr(start + 1, end - start - 1);
		back = str.substr(end + 1, std::string::npos);

		if (tmp == "")
		{
			this->_err_msg = "invalid syntax: brackets";
			throw (this->_err_msg);
		}

		tmp_term = split_term(tmp);
		if (tmp_term.size() == 1)
		{
			if (front[front.length() - 1] == '+')
			{
				if (tmp[0] == '+')
					tmp = tmp.substr(1, std::string::npos);
				else
					front = front.substr(0, front.length() - 1);
			}
			else if (front[front.length() - 1] == '-')
			{
				tmp = tmp.substr(1, std::string::npos);
				if (tmp[0] == '-')
				{
					front = front.substr(0, front.length() - 1);
					front = front + "+";
				}
			}
			str = front + tmp + back;
			tmp_term.clear();
		}
		else
		{
			tmp_term.clear();
			keep = 0;
			if (back == "")
				break ;
			while (back[keep] != ')' && back[keep] != '\0')
				keep++;
			if (back[keep] == '\0')
				break ;
			end = front.length() + tmp.length() + 2 + back.find(")");
			end--;
		}
		end++;
	}

	start = 0;
	end = 0;
	keep = 0;
	//need to calculate in the bracket
	while (1)
	{
		if (str.find(")") == std::string::npos)
			break;

		end = str.find(")");
		start = end;
		while (str[start] != '(')
			start--;

		front = str.substr(0, start + 1);
		tmp = str.substr(start + 1, end - start - 1);
		back = str.substr(end + 1, std::string::npos);
		if (tmp == "")
		{
			this->_err_msg = "invalid syntax: brackets";
			throw (this->_err_msg);
		}


		split_expression(tmp, nb, op);
		nb.clear();
		op.clear();
		if (!(get_term(tmp, tmp_term, tmp_degree)))
		{
			std::cout << "error1" << std::endl;
			return (0);
		}

		

		//to handle front string
		if ((front[front.length() - 1] == '('
				&& (front[front.length() - 2] == '-' || front[front.length() - 2] == '+'))
			|| (front[front.length() - 1] == '('
				&& ('0' <= front[front.length() - 2] && front[front.length() - 2] <= '9')))
		{
			if (start != 0)
				start--;
			front = front.substr(0, front.length() - 1);

			if (front[front.length() - 1] == '-' || front[front.length() - 1] == '+')
			{
				front = front + "1*";
				start = start + 2;
			}
			else
			{
				front = front + "*";
				start = start + 1;
			}
			
		}
		else
			front = front.substr(0, front.length() - 1);
		start = front.length() - 1;
		while (front[start] == '*')
		{
			op.push_back(front[start]);
			start--;
			keep = start;
			while (('0' <= front[start] && front[start] <= '9') || front[start] == '.')
				start--;
			if (front[start] == '+' || front[start] == '-')
				start--;
			nb.push_back(atof(front.substr(start + 1, keep - start).c_str()));
			front = front.substr(0, start + 1);
		}



		end = 0;
		//to handle back string ->fix here
		while ((back[end] == '*' || back[end] == '/') && back[end] != '\0')
		{
			op.push_back(back[end]);
			std::cout << "op: " << back[end] << std::endl;
			end++;
			keep = end;
			if (back[end] == '+' || back[end] == '-')
				end++;
			while (('0' <= back[end] && back[end] <= '9') || back[end] == '.')
				end++;
			nb.push_back(atof(back.substr(keep, end - keep).c_str()));
			back = back.substr(end - keep + 1, std::string::npos);
			end = 0;
		}



		for (size_t i = 0; i < tmp_term.size();i++)
		{
			std::cout << "term: " << tmp_term[i] << ", degree: " << tmp_degree[i] << std::endl;
			tmp_term_float.push_back(atof(tmp_term[i].c_str()));
			degree.push_back(tmp_degree[i]);
		}

		for (size_t i = 0; i < op.size(); i++)
		{
			for (size_t j = 0; j < tmp_term_float.size(); j++)
				tmp_term_float[j] = calc(tmp_term_float[j], nb[i], op[i]);
		}

		tmp = "";
		for (size_t i = 0; i < tmp_term_float.size(); i++)
		{
			term.push_back(tmp_term_float[i]);
			if (tmp_term_float[i] >= 0)
				tmp += "+";
			tmp += float_to_string(tmp_term_float[i]);
			tmp += "*" + std::string(1, this->_variable) + "^";
			tmp += float_to_string(tmp_degree[i]);
		}
		tmp_term.clear();
		op.clear();
		nb.clear();
		tmp_degree.clear();
		tmp_term_float.clear();
		str = front + tmp + back;
	}
	return (1);
}

int	Parse::check_str(std::string str)
{
	if (!(is_equation_form(str) && check_variable(str)
		&& check_invalid_character(str) && check_number(str)))
		return (0);

	remove_space(str);

	if (!check_syntax(str))
		return (0);

	//remove bracket using get_term
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(reduce_bracket(left_str) && reduce_bracket(right_str)))
		return (0);

	std::vector<std::string>	l_term;
	std::vector<std::string>	r_term;
	std::vector<float>		l_degree;
	std::vector<float>		r_degree;

	if (!(get_term(str.substr(0, str.find("=")), l_term, l_degree)
		&& get_term(str.substr(str.find("=") + 1, std::string::npos), r_term, r_degree)))
		return (0);
	for (size_t i = 0; i < l_term.size(); i++)
	{
		this->_reduced_form.push_back(atof(l_term[i].c_str()));
		this->_degree.push_back(l_degree[i]);
	}
	for (size_t i = 0; i < r_term.size(); i++)
	{
		this->_reduced_form.push_back(-1 * atof(r_term[i].c_str()));
		this->_degree.push_back(r_degree[i]);
	}
	make_reduced_form();
	return (1);
}

std::vector<std::string>	Parse::split_term(std::string str)
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
			if (str[i] == '+' || str[i] == '-')
				i++;
			while (('0' <= str[i] && str[i] <= '9') || str[i] == '.')
				i++;
			degree += sign * atof(str.substr(tmp, i - tmp).c_str());
		}
		else if (str[i] == this->_variable)
			degree += sign * 1;
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
				if (str[i - 1] == '-')
					tmp = "-1*" + std::string(1, this->_variable);
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
			while (str[i] == '+' || str[i] == '-'
				|| ('0' <= str[i] && str[i] <= '9') || str[i] == '.')
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
	return (float_to_string(nb[0]));
}

std::string	Parse::float_to_string(float num)
{
	std::stringstream	ss;

	ss << num;
	return (ss.str());
}

int	Parse::get_term(std::string str,
			std::vector<std::string> &term, std::vector<float> &degree)
{
	term = split_term(str);
	for (size_t i = 0; i < term.size(); i++)
		degree.push_back(find_degree(term[i]));
	for (std::vector<std::string>::iterator it = term.begin(); it != term.end(); it++)
	{
		if (!remove_variable(*it))
			return (0);
	}
	for (size_t i = 0; i < term.size(); i++)
		term[i] = calculate(term[i]);

	for (size_t i = 0; i < term.size(); i++)
	{
		for (size_t start = i + 1; start < term.size(); start++)
		{
			if (degree[i] == degree[start])
			{
				term[i] = float_to_string(atof(term[i].c_str())
								+ atof(term[start].c_str()));
				term.erase(term.begin() + start);
				degree.erase(degree.begin() + start);
				start--;
			}
		}
	}
	return (1);
}

void	Parse::set_equation_type(void)
{
	for (size_t i = 0; i < this->_degree.size(); i++)
	{
		if (this->_degree[i] < 0
			|| this->_degree[i] - (int)(this->_degree[i]) != 0)
		{
			this->_equation_type = TYPE_FRACTIONAL;
			return ;
		}
	}

	int	max;

	if (this->_degree.size() == 0 && this->_reduced_form.size() == 0)
	{
		this->_equation_type = TYPE_ZERO;
		return ;
	}
	max = this->_degree[0];
	for (size_t i = 1; i < this->_degree.size(); i++)
	{
		if (max < this->_degree[i])
			max = this->_degree[i];
	}
	this->_max_degree = max;
	if (max < 0)
		this->_equation_type = TYPE_FRACTIONAL;
	else if (max > 2)
		this->_equation_type = TYPE_HIGH_DEGREE;
	else
		this->_equation_type = max;
}

void	Parse::make_form_ascending_order(void)
{
	if (this->_equation_type == TYPE_ZERO)
	{
		std::vector<float>	form(1, 0);
		std::vector<float>	degree(1, 0);

		if (this->_reduced_form.size() != 0)
			form[0] = this->_reduced_form[0];
		this->_reduced_form = form;
		this->_degree = degree;
	}
	else if (this->_equation_type != TYPE_FRACTIONAL)
	{
		std::vector<float>	form(this->_max_degree + 1, 0);
		std::vector<float>	degree(this->_max_degree + 1, 0);

		for (size_t i = 0; i < form.size(); i++)
		{
			for (size_t j = 0; j < this->_degree.size(); j++)
			{
				if (this->_degree[j] == i)
					form[i] = this->_reduced_form[j];
			}
			degree[i] = i;
		}
		this->_reduced_form = form;
		this->_degree = degree;
	}
	else
	{
		for (size_t i = 0; i < this->_degree.size(); i++)
		{
			for (size_t j = i + 1; j < this->_degree.size(); j++)
			{
				if (this->_degree[i] > this->_degree[j])
				{
					std::swap(this->_degree[i], this->_degree[j]);
					std::swap(this->_reduced_form[i], this->_reduced_form[j]);
				}
			}
		}
	}
}

void	Parse::set_equation_str(void)
{
	std::string	str  = "";
	if (this->_equation_type == TYPE_ZERO)
	{
		this->_equation_str = float_to_string(this->_reduced_form[0]) + " = 0";
		return ;
	}
	if (!this->_flag_bonus)
	{
		for (size_t i = 0; i < this->_reduced_form.size(); i++)
		{
			if (this->_reduced_form[i] < 0)
				str += "- ";
			else
				str += "+ ";

			if (this->_reduced_form[i] != 0)
				str += float_to_string(std::abs(this->_reduced_form[i]));
			else
				str += "0";
			str += " * " + std::string(1, this->_variable);
			str += "^";
			str += float_to_string(this->_degree[i]);
			str += " ";
		}
		str += "= 0";
	}
	else
	{
		for (size_t i = 0; i < this->_reduced_form.size(); i++)
		{
			if (this->_reduced_form[i] != 0)
			{
				if (this->_reduced_form[i] < 0)
					str += "- ";
				else
					str += "+ ";

				str += float_to_string(std::abs(this->_reduced_form[i]));
				str += " ";
				if (this->_degree[i] != 0)
				{
					str += "* " + std::string(1, this->_variable);
					if  (this->_degree[i] != 1)
					{
						str += "^";
						str += float_to_string(this->_degree[i]);
					}
					str += " ";
				}
			}
		}
		str += "= 0";
	}

	size_t	i = 0;

	while (!(('0' <= str[i] && str[i] <= '9') || str[i] == '-'))
		i++;
	str = str.substr(i, std::string::npos);
	this->_equation_str = str;
}

void	Parse::make_reduced_form(void)
{
	for (size_t i = 0; i < this->_reduced_form.size(); i++)
	{
		for (size_t j = i + 1; j < this->_reduced_form.size(); j++)
		{
			if (this->_degree[i] == this->_degree[j])
			{
				this->_reduced_form[i]
					= this->_reduced_form[i] + this->_reduced_form[j];
				this->_reduced_form[j] = 0;
			}
		}
		if (this->_reduced_form[i] == 0)
		{
			this->_reduced_form.erase(this->_reduced_form.begin() + i);
			this->_degree.erase(this->_degree.begin() + i);
			i--;
		}
	}
	set_equation_type();
	make_form_ascending_order();
	set_equation_str();
}
