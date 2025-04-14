/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EquationSimplifier.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 07:08:27 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:45:09 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/Parse/EquationSimplifier.hpp"

EquationSimplifier::EquationSimplifier()
{
}

EquationSimplifier::EquationSimplifier(std::string str, t_parse info): _str(str), _info(info)
{
	TermAnalyzer	term_analyzer(str, info);

	this->_term_analyzer = term_analyzer;
}

EquationSimplifier::EquationSimplifier(const EquationSimplifier& simplifier)
{
	*this = simplifier;
}

EquationSimplifier& EquationSimplifier::operator=(const EquationSimplifier& simplifier)
{
	if (this == &simplifier)
		return (*this);
	this->_str = simplifier._str;
	this->_struct_error = simplifier._struct_error;
	this->_term_analyzer = simplifier._term_analyzer;
	return (*this);
}

EquationSimplifier::~EquationSimplifier()
{
}

t_parse EquationSimplifier::get_info(void) const
{
	return (this->_info);
}

std::string	EquationSimplifier::simplify(std::string str)
{
	std::pair<std::vector<std::string>, std::vector<float>>	l_term_degree;
	std::pair<std::vector<std::string>, std::vector<float>>	r_term_degree;

	if (!(this->_term_analyzer.get_term(str.substr(0, str.find("=")), l_term_degree)
		&& this->_term_analyzer.get_term(str.substr(str.find("=") + 1, std::string::npos), r_term_degree)))
		return (0);

	set_info_term_degree(l_term_degree, r_term_degree);
	str = make_reduced_form();
	this->_str = str;
	return (this->_str);
}

void	EquationSimplifier::set_info_term_degree(std::pair<std::vector<std::string>, std::vector<float>> l_term_degree,
				std::pair<std::vector<std::string>, std::vector<float>> r_term_degree)
{
	for (size_t i = 0; i < l_term_degree.first.size(); i++)
	{
		this->_info.reduced_form.push_back(atof(l_term_degree.first[i].c_str()));
		this->_info.degree.push_back(l_term_degree.second[i]);
	}
	for (size_t i = 0; i < r_term_degree.first.size(); i++)
	{
		this->_info.reduced_form.push_back(-1 * atof(r_term_degree.first[i].c_str()));
		this->_info.degree.push_back(r_term_degree.second[i]);
	}
}

void	EquationSimplifier::set_equation_type(void)
{
	for (size_t i = 0; i < this->_info.degree.size(); i++)
	{
		if (this->_info.degree[i] < 0)
		{
			this->_info.equation_type = TYPE_FRACTIONAL;
			return ;
		}
	}

	int	max;

	if (this->_info.degree.size() == 0 && this->_info.reduced_form.size() == 0)
	{
		this->_info.equation_type = TYPE_ZERO;
		return ;
	}
	max = this->_info.degree[0];
	for (size_t i = 1; i < this->_info.degree.size(); i++)
	{
		if (max < this->_info.degree[i])
			max = this->_info.degree[i];
	}
	this->_info.max_degree = max;
	if (max > 2)
		this->_info.equation_type = TYPE_HIGH_DEGREE;
	else
		this->_info.equation_type = max;
}

void	EquationSimplifier::make_form_ascending_order(void)
{
	if (this->_info.equation_type == TYPE_ZERO)
	{
		std::vector<float>	form(1, 0);
		std::vector<float>	degree(1, 0);

		if (this->_info.reduced_form.size() != 0)
			form[0] = this->_info.reduced_form[0];
		this->_info.reduced_form = form;
		this->_info.degree = degree;
	}
	else if (this->_info.equation_type != TYPE_FRACTIONAL)
	{
		std::vector<float>	form(this->_info.max_degree + 1, 0);
		std::vector<float>	degree(this->_info.max_degree + 1, 0);

		for (size_t i = 0; i < form.size(); i++)
		{
			for (size_t j = 0; j < this->_info.degree.size(); j++)
			{
				if (this->_info.degree[j] == i)
					form[i] = this->_info.reduced_form[j];
			}
			degree[i] = i;
		}
		this->_info.reduced_form = form;
		this->_info.degree = degree;
	}
	else
	{
		for (size_t i = 0; i < this->_info.degree.size(); i++)
		{
			for (size_t j = i + 1; j < this->_info.degree.size(); j++)
			{
				if (this->_info.degree[i] > this->_info.degree[j])
				{
					std::swap(this->_info.degree[i], this->_info.degree[j]);
					std::swap(this->_info.reduced_form[i], this->_info.reduced_form[j]);
				}
			}
		}
	}
}

std::string	EquationSimplifier::mandatory(void)
{
	std::string	str  = "";

	for (size_t i = 0; i < this->_info.reduced_form.size(); i++)
	{
		if (this->_info.reduced_form[i] < 0)
			str += "- ";
		else
			str += "+ ";

		if (this->_info.reduced_form[i] != 0)
			str += float_to_string(ft_abs(this->_info.reduced_form[i]));
		else
			str += "0";
		str += " * " + std::string(1, this->_info.variable);
		str += "^";
		str += float_to_string(this->_info.degree[i]);
		str += " ";
	}
	str += "= 0";
	return (str);
}

std::string	EquationSimplifier::bonus(void)
{
	std::string	str  = "";

	for (size_t i = 0; i < this->_info.reduced_form.size(); i++)
	{
		if (this->_info.reduced_form[i] != 0)
		{
			if (this->_info.reduced_form[i] < 0)
				str += "- ";
			else
				str += "+ ";

			str += float_to_string(ft_abs(this->_info.reduced_form[i]));
			str += " ";
			if (this->_info.degree[i] != 0)
			{
				str += "* " + std::string(1, this->_info.variable);
				if  (this->_info.degree[i] != 1)
				{
					str += "^";
					str += float_to_string(this->_info.degree[i]);
				}
				str += " ";
			}
		}
	}
	str += "= 0";
	return (str);
}

std::string	EquationSimplifier::set_equation_str(void)
{
	std::string	str  = "";
	if (this->_info.equation_type == TYPE_ZERO)
	{
		if (!this->_info.flag_bonus)
			this->_info.equation_str
				= float_to_string(this->_info.reduced_form[0])
					+ " * " + std::string(1, this->_info.variable) + "^0"
					+ " = 0";
		else
			this->_info.equation_str
				= float_to_string(this->_info.reduced_form[0]) + " = 0";
		return (this->_info.equation_str);
	}

	if (!this->_info.flag_bonus)
		str = mandatory();
	else
		str = bonus();

	size_t	i = 0;
	while (!(('0' <= str[i] && str[i] <= '9') || str[i] == '-'))
		i++;
	str = str.substr(i, std::string::npos);

	this->_info.equation_str = str;
	return (str);
}

std::string	EquationSimplifier::make_reduced_form(void)
{
	for (size_t i = 0; i < this->_info.reduced_form.size(); i++)
	{
		for (size_t j = i + 1; j < this->_info.reduced_form.size(); j++)
		{
			if (this->_info.degree[i] == this->_info.degree[j])
			{
				this->_info.reduced_form[i]
					= this->_info.reduced_form[i] + this->_info.reduced_form[j];
				this->_info.reduced_form[j] = 0;
			}
		}
		if (this->_info.reduced_form[i] == 0)
		{
			this->_info.reduced_form.erase(this->_info.reduced_form.begin() + i);
			this->_info.degree.erase(this->_info.degree.begin() + i);
			i--;
		}
	}
	set_equation_type();
	make_form_ascending_order();
	return (set_equation_str());
}
