/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/12 09:40:04 by yhwang           ###   ########.fr       */
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
	void			check_str(std::string str);
	int			is_equation_form(std::string str);
	void			check_variable(std::string str);

	int			_equal_sign;
	int			_degree;
	char			_variable;
	std::vector<int>	_left_term;
	std::vector<int>	_right_term;
	std::vector<int>	_reduced_form;

};

#endif
