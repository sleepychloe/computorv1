/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/14 22:22:20 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Parse
{
public:
	Parse(char *argv);
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

private:
	Parse();
	int				check_str(std::string str);

	int				is_equation_form(std::string str);
	int				check_variable(std::string str);

	int				check_invalid_character(std::string str);
	int				check_brackets(std::string str);
	int				check_sign(std::string str);
	int				check_number(std::string str);
	int				check_caret(std::string str);
	int				check_syntax(std::string str);

	std::vector<std::string>	split_term(std::string str);
	std::vector<int>		find_degree(std::vector<std::string> term);
	std::vector<std::string>	remove_variable(std::vector<std::string> term);
	std::string			calculate(std::string str);
	std::vector<std::string>	remove_bracket(std::vector<std::string> term);
	int				get_term(std::string str);

	int				_degree;
	char				_variable;
	std::vector<float>		_left_term;
	std::vector<float>		_right_term;
	std::vector<float>		_reduced_form;
	std::string			_err_msg;

};

#endif
