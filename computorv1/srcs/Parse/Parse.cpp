
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

#include "../../incs/Parse/Parse.hpp"

Parse::Parse()
{
	this->_info.variable = 0;
	this->_info.max_degree = 0;
	this->_info.equation_type = 0;
	this->_info.flag_bonus = 0;
	this->_info.equation_str = "";
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse& Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_info = parse._info;
	return (*this);
}

Parse::~Parse()
{
}

t_parse	Parse::get_info(void) const
{
	return (this->_info);
}

void	Parse::parse(char *argv, int flag_bonus)
{
	std::string	str(argv);

	this->_info.flag_bonus = flag_bonus;
	parse_start(str);
}

int	Parse::parse_start(std::string str)
{
	InputConvertor	input_convertor(str, this->_info);
	str = input_convertor.convert(str);
	this->_info = input_convertor.get_info();

	SyntaxChecker	syntax_checker(str, this->_info);
	str = syntax_checker.check(str);
	this->_info = syntax_checker.get_info();

	BracketRemover	bracket_remover(str, this->_info);
	str = bracket_remover.remove(str);

	EquationSimplifier	equation_simplifier(str, this->_info);
	str = equation_simplifier.simplify(str);
	this->_info = equation_simplifier.get_info();
	return (1);
}
