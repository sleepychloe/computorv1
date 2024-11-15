/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/15 03:00:33 by yhwang           ###   ########.fr       */
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

	void				remove_space(std::string &str);
	std::vector<std::string>	split_term(std::string str);
	int				find_degree(std::string str);
	int				remove_variable(std::string &str);
	std::string			calculate(std::string str);
	int				remove_bracket(std::string &str);
	int				get_term(std::string str);

	int				_degree;
	char				_variable;
	std::vector<float>		_left_term;
	std::vector<float>		_right_term;
	std::vector<float>		_reduced_form;
	std::string			_err_msg;

};

#endif
