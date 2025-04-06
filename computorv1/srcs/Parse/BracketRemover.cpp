/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BracketRemover.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 05:14:58 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:12:31 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Parse/BracketRemover.hpp"

BracketRemover::BracketRemover()
{
}

BracketRemover::BracketRemover(std::string str, t_parse info): _str(str), _info(info)
{
	TermAnalyzer	term_analyzer(str, info);

	this->_term_analyzer = term_analyzer;
}

BracketRemover::BracketRemover(const BracketRemover& remover)
{
	*this = remover;
}

BracketRemover& BracketRemover::operator=(const BracketRemover& remover)
{
	if (this == &remover)
		return (*this);
	this->_str = remover._str;
	this->_info = remover._info;
	this->_str_type = remover._str_type;
	this->_struct_error = remover._struct_error;
	this->_term_analyzer = remover._term_analyzer;
	return (*this);
}

BracketRemover::~BracketRemover()
{
}

std::string	BracketRemover::remove(std::string str)
{
	std::string	left_str = str.substr(0, str.find("="));
	std::string	right_str = str.substr(str.find("=") + 1, std::string::npos);

	if (!(remove_bracket(LEFT_STR, left_str) && remove_bracket(RIGHT_STR, right_str)))
		return (0);

	str = left_str + "=" + right_str;
	this->_str = str;
	return (this->_str);
}

void	BracketRemover::throw_err_msg(std::string function, std::string err_msg, int str_type)
{
	size_t	pos = 0;
	if (str_type == RIGHT_STR)
		pos = this->_str.substr(0, this->_str.find("=")).length() + 1;

	size_t	equal = this->_str.find('=');

	this->_struct_error.file_name = "BracketRemover.cpp";
	this->_struct_error.cat = "input error";
	this->_struct_error.function = function;
	this->_struct_error.msg = err_msg;
	this->_struct_error.pos = pos;

	this->_struct_error.pos_str = "\t\t  " + this->_str + "\n";
	this->_struct_error.pos_str += "\t\t  ";
	this->_struct_error.pos_str += RED;

	if (str_type == LEFT_STR)
	{
		for (size_t i = 0; i < equal; i++)
			this->_struct_error.pos_str += "~";
	}
	else
	{
		for (size_t i = 0; i <= equal + 1; i++)
			this->_struct_error.pos_str += " ";
		for (size_t i = equal + 2; i < this->_str.length(); i++)
			this->_struct_error.pos_str += "~";
	}
	this->_struct_error.pos_str += BLACK;
	throw (ParseError::ParseException(this->_struct_error));
}

void	BracketRemover::remove_bracket_without_calc(std::string &str,
				std::vector<std::string> &s)
{
	if (s[FRONT][s[FRONT].length() - 1] == '+')
	{
		if (s[BRACKET][0] == '+')
			s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
		else if (s[BRACKET][0] == '-')
			s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
	}
	else if (s[FRONT][s[FRONT].length() - 1] == '-')
	{
		if (s[BRACKET][0] == '+')
			s[BRACKET] = s[BRACKET].substr(1, std::string::npos);
		else if (s[BRACKET][0] == '-')
		{
			s[BRACKET] = s[BRACKET].substr(1, std::string::npos);
			s[FRONT][s[FRONT].length() - 1] = '+';
		}
	}
	str = s[FRONT] + s[BRACKET] + s[BACK];
}

int	BracketRemover::find_next_bracket(std::vector<size_t> &i,
				std::vector<std::string> &s)
{
	i[KEEP] = 0;
	if (s[BACK] == "")
		return (0);
	while (s[BACK][i[KEEP]] != ')' && s[BACK][i[KEEP]] != '\0')
		i[KEEP]++;
	if (s[BACK][i[KEEP]] == '\0')
		return (0);
	i[END] = s[FRONT].length() + s[BRACKET].length() + 2 + s[BACK].find(")");
	i[END]--;
	return (1);
}

int	BracketRemover::remove_bracket_one_term(std::string &str)
{
	std::vector<size_t>		i(3, 0);
	std::vector<std::string>	s(3, "");
	std::vector<std::string>	tmp_term;

	while (1)
	{
		if (str[i[END]] == '\0' || str.find(")") == std::string::npos)
			break ;
		while (str[i[END]] != ')' && str[i[END]] != '\0')
			i[END]++;
		if (str[i[END]] == '\0')
			break ;
		i[START] = i[END];
		while (str[i[START]] != '(')
			i[START]--;
		s[FRONT] = str.substr(0, i[START]);
		s[BRACKET] = str.substr(i[START] + 1, i[END] - i[START] - 1);
		s[BACK] = str.substr(i[END] + 1, std::string::npos);
		if (s[BRACKET] == "")
			throw_err_msg("BracketRemover::remove_bracket_one_term(int str_type, std::string &str)",
				"invalid syntax: brackets", this->_str_type);

		tmp_term = this->_term_analyzer.split_term(s[BRACKET]);
		if (tmp_term.size() == 1)
		{
			remove_bracket_without_calc(str, s);
			i[END] = 0;
		}
		else
		{
			if (!find_next_bracket(i, s))
				break ;
		}
		tmp_term.clear();
		i[END]++;
	}
	return (1);
}

void	BracketRemover::check_front_str(std::vector<size_t> &i, std::vector<std::string> &s)
{
	if (s[FRONT].length() >= 2 && s[FRONT][s[FRONT].length() - 1] == '('
		&& !(s[FRONT][s[FRONT].length() - 2] == '+'
			|| s[FRONT][s[FRONT].length() - 2] == '-'
			|| s[FRONT][s[FRONT].length() - 2] == '*'
			|| s[FRONT][s[FRONT].length() - 2] == '/'
			|| s[FRONT][s[FRONT].length() - 2] == '('))
		throw_err_msg("BracketRemover::check_front_str(std::vector<size_t> &i, std::vector<std::string> &s)",
			"invalid syntax: operator", this->_str_type);

	if (s[FRONT].length() >= 2 && ((s[FRONT][s[FRONT].length() - 1] == '('
		&& (s[FRONT][s[FRONT].length() - 2] == '-'
			|| s[FRONT][s[FRONT].length() - 2] == '+'))))
	{
		if (i[START] != 0)
			i[START]--;
		s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
		if (s[FRONT][s[FRONT].length() - 1] == '-'
			|| s[FRONT][s[FRONT].length() - 1] == '+')
		{
			s[FRONT] = s[FRONT] + "1*";
			i[START] = i[START] + 2;
		}
	}
	else
		s[FRONT] = s[FRONT].substr(0, s[FRONT].length() - 1);
}

void	BracketRemover::apply_operation_from_front(std::string &tmp,
				std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::string	nb = "0";
	std::pair<std::vector<std::string>, std::vector<float>>	tmp_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>> keep_term_degree = term_degree;

	if (!this->_term_analyzer.get_term(tmp, tmp_term_degree))
		throw_err_msg("BracketRemover::apply_operation_from_front(...)",
			"cannot seperate the terms", this->_str_type);
	if (s[FRONT][i[KEEP] + 1] == '*')
	{
		term_degree.first.clear();
		term_degree.second.clear();
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			for (size_t j = 0; j < keep_term_degree.first.size(); j++)
			{
				term_degree.first.push_back(float_to_string(atof(keep_term_degree.first[j].c_str())
										* atof(tmp_term_degree.first[k].c_str())));
				term_degree.second.push_back(tmp_term_degree.second[k]
								+ keep_term_degree.second[j]);
			}
		}
	}
	else
	{
		for (size_t k = 0; k < term_degree.second.size(); k++)
		{
			if (term_degree.second[k] > 0)
				throw_err_msg("BracketRemover::apply_operation_from_front(...)",
					"this program does not support to calculate expression containing variable in fraction",
					this->_str_type);
			nb = float_to_string(atof(nb.c_str()) + atof(term_degree.first[k].c_str()));
		}
		if (atof(nb.c_str()) == 0)
			throw_err_msg("BracketRemover::apply_operation_from_front(...)",
				"cannot divided by 0", this->_str_type);
		term_degree.first.clear();
		term_degree.second.clear();
		term_degree.second = tmp_term_degree.second;
		for (size_t j = 0; j < tmp_term_degree.first.size(); j++)
			term_degree.first.push_back(float_to_string(atof(tmp_term_degree.first[j].c_str()) / atof(nb.c_str())));
	}
}

void	BracketRemover::find_mul_dev_front_str(std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::string	tmp = "";
	std::pair<std::vector<std::string>, std::vector<float>>	tmp_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>> keep_term_degree = term_degree;

	check_front_str(i, s);

	i[START] = s[FRONT].length() - 1;
	while (s[FRONT].length() >= 1 && s[FRONT][i[START]] != '\0'
		&& (s[FRONT][i[START]] == '*' || s[FRONT][i[START]] == '/'))
	{
		i[START]--;
		i[KEEP] = i[START];
		while ((s[FRONT][i[START]] != '\0'
			&& '0' <= s[FRONT][i[START]] && s[FRONT][i[START]] <= '9')
				|| s[FRONT][i[START]] == '.'
				|| s[FRONT][i[START]] == this->_info.variable
				|| s[FRONT][i[START]] == '^')
			i[START]--;
		if (s[FRONT][i[START]] != '\0'
			&& (s[FRONT][i[START]] == '+' || s[FRONT][i[START]] == '-'))
			i[START]--;
		tmp = s[FRONT].substr(i[START] + 1, i[KEEP] - i[START]);
		apply_operation_from_front(tmp, i, s, term_degree);
		s[FRONT] = s[FRONT].substr(0, i[START] + 1);
		i[START] = s[FRONT].length() - 1;
	}
}

void	BracketRemover::apply_operation_from_back(std::string &tmp,
				std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::pair<std::vector<std::string>, std::vector<float>>	tmp_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>> keep_term_degree = term_degree;

	if (!this->_term_analyzer.get_term(tmp, tmp_term_degree))
		throw_err_msg("BracketRemover::apply_operation_from_back(...)",
			"cannot seperate the terms", this->_str_type);
	if (s[BACK][i[KEEP] - 1] == '*')
	{
		term_degree.first.clear();
		term_degree.second.clear();
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			for (size_t j = 0; j < keep_term_degree.first.size(); j++)
			{
				term_degree.first.push_back(float_to_string(atof(keep_term_degree.first[j].c_str())
										* atof(tmp_term_degree.first[k].c_str())));
				term_degree.second.push_back(tmp_term_degree.second[k]
								+ keep_term_degree.second[j]);
			}
		}
	}
	else
	{
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			if (tmp_term_degree.second[k] > 0)
				throw_err_msg("BracketRemover::apply_operation_from_back(...)",
					"this program does not support to calculate expression containing variable in fraction", this->_str_type);
			if (k > 0)
				tmp_term_degree.first[0] = float_to_string(atof(tmp_term_degree.first[0].c_str())
								+ atof(tmp_term_degree.first[k].c_str()));
		}
		for (size_t k = 0; k < tmp_term_degree.first.size(); k++)
		{
			for (size_t j = 0; j < term_degree.first.size(); j++)
			{
				if (atof(tmp_term_degree.first[0].c_str()) == 0)
					throw_err_msg("BracketRemover::apply_operation_from_back(...)",
						"cannot divided by 0", this->_str_type);
				term_degree.first[j] = float_to_string(atof(term_degree.first[j].c_str())
								/ atof(tmp_term_degree.first[0].c_str()));
			}
		}
	}
}

void	BracketRemover::find_mul_dev_back_str(std::vector<size_t> &i, std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::string	tmp = "";

	i[END] = 0;
	if (s[BACK][i[END]] != '\0'
		&& !(s[BACK][i[END]] == '+' || s[BACK][i[END]] == '-'
			|| s[BACK][i[END]] == '*' || s[BACK][i[END]] == '/'
			|| s[BACK][i[END]] == ')'))
		throw_err_msg("BracketRemover::find_mul_dev_back_str(...)",
			"invalid syntax: operator", this->_str_type);

	while (s[BACK][i[END]] != '\0'
		&& (s[BACK][i[END]] == '*' || s[BACK][i[END]] == '/'))
	{
		if (s[BACK][i[END] + 1] != '\0' && s[BACK][i[END] + 1] == '(')
		{
			i[END]++;
			i[KEEP] = i[END];
			tmp = s[BACK].substr(2, s[BACK].find(")") - 2);
			apply_operation_from_back(tmp, i, s, term_degree);
			s[BACK] = s[BACK].substr(s[BACK].find(")") + 1, std::string::npos);
			i[END] = 0;
		}
		else
		{
			i[END]++;
			i[KEEP] = i[END];
			if (s[BACK][i[END]] == '+' || s[BACK][i[END]] == '-')
				i[END]++;
			while ((s[BACK][i[END]] != '\0'
				&& '0' <= s[BACK][i[END]] && s[BACK][i[END]] <= '9')
					|| s[BACK][i[END]] == '.'
					|| s[BACK][i[END]] == this->_info.variable
					|| s[BACK][i[END]] == '^')
				i[END]++;
			tmp = s[BACK].substr(i[KEEP], i[END] - i[KEEP]);
			apply_operation_from_back(tmp, i, s, term_degree);
			s[BACK] = s[BACK].substr(i[END] - i[KEEP] + 1, std::string::npos);
			i[END] = 0;
		}
	}
}

void	BracketRemover::get_bracket_str(std::vector<std::string> &s,
				std::pair<std::vector<std::string>, std::vector<float>> &term_degree)
{
	std::vector<float>	term_float;

	for (size_t i = 0; i < term_degree.first.size();i++)
		term_float.push_back(atof(term_degree.first[i].c_str()));
	s[BRACKET] = "";
	for (size_t i = 0; i < term_float.size(); i++)
	{
		if (term_float[i] >= 0)
			s[BRACKET] += "+";
		s[BRACKET] += float_to_string(term_float[i]);
		if (term_degree.second[i] > 0)
		{
			s[BRACKET] += "*" + std::string(1, this->_info.variable) + "^";
			s[BRACKET] += float_to_string(term_degree.second[i]);
		}
	}
}

int	BracketRemover::remove_bracket_multiple_term(std::string &str)
{
	std::vector<size_t>		i(3, 0);
	std::vector<std::string>	s(3, "");

	std::pair<std::vector<std::string>, std::vector<float>>	term_degree;

	while (1)
	{
		if (str[i[END]] == '\0' || str.find(")") == std::string::npos)
			break ;
		while (str[i[END]] != ')' && str[i[END]] != '\0')
			i[END]++;
		if (str[i[END]] == '\0')
			break ;
		i[START] = i[END];
		while (str[i[START]] != '(')
			i[START]--;
		s[FRONT] = str.substr(0, i[START] + 1);
		s[BRACKET] = str.substr(i[START] + 1, i[END] - i[START] - 1);
		s[BACK] = str.substr(i[END] + 1, std::string::npos);
		if (s[BRACKET] == "")
			throw_err_msg("BracketRemover::remove_bracket_multiple_term(int str_type, std::string &str)",
				"invalid syntax: brackets", this->_str_type);
		if (!(this->_term_analyzer.get_term(s[BRACKET], term_degree)))
			throw_err_msg("BracketRemover::remove_bracket_multiple_term(int str_type, std::string &str)",
				"cannot seperate the terms", this->_str_type);

		find_mul_dev_front_str(i, s, term_degree);
		find_mul_dev_back_str(i, s, term_degree);
		get_bracket_str(s, term_degree);

		term_degree.first.clear();
		term_degree.second.clear();
		str = s[FRONT] + s[BRACKET] + s[BACK];
	}
	return (1);
}

int	BracketRemover::remove_bracket(int str_type, std::string &str)
{
	this->_str_type = str_type;
	return (remove_bracket_one_term(str)
		&& remove_bracket_multiple_term(str));
}
