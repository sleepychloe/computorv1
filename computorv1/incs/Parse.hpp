/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/12 22:40:21 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <vector>

class Parse
{
public:
	Parse(char *argv);
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

private:
	Parse();
	int			check_str(std::string str);
	int			is_equation_form(std::string str);
	int			check_variable(std::string str);
	int			check_syntax(std::string str);

	int			_degree;
	char			_variable;
	std::vector<int>	_left_term;
	std::vector<int>	_right_term;
	std::vector<int>	_reduced_form;

};

#endif
