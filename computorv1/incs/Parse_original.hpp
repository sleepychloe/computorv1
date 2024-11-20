/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/20 11:34:58 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iomanip>
#include "../incs/Color.hpp"

# define TYPE_FRACTIONAL		-1
# define TYPE_HIGH_DEGREE		-2
# define TYPE_ZERO			0

class Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	virtual ~Parse();

	char				get_variable(void);
	std::vector<float>		get_reduced_form(void);
	std::vector<float>		get_degree(void);
	int				get_equation_type(void);
	int				get_flag_bonus(void);
	std::string			get_equation_str(void);

	void				parse_start(char *argv, int flag_bonus);

protected:
	int				is_equation_form(std::string str);
	int				check_variable(std::string str);
	int				check_invalid_character(std::string str);
	int				check_brackets(std::string str);
	int				check_sign(std::string str);
	int				check_number(std::string str);
	int				check_point(std::string str);
	int				check_caret(std::string str);
	int				check_syntax(std::string str);
	int				check_str(std::string str);

	void				remove_space(std::string &str);
	std::vector<std::string>	split_term(std::string str);
	float				find_degree(std::string str);
	int				remove_variable(std::string &str);
	int				check_operation(std::string str);
	void				split_expression(std::string str,
						std::vector<float> &nb, std::vector<char> &op);
	float				calc(float nb1, float n2, char op);
	std::string			calculate(std::string str);
	int				remove_bracket(std::string &str);
	std::string			float_to_string(float num);
	int				get_term(std::string str,
						std::vector<std::string> &term,
						std::vector<float> &degree);

	void				set_equation_type(void);
	void				make_form_ascending_order(void);
	void				set_equation_str(void);
	void				make_reduced_form(void);

	char				_variable;
	std::vector<float>		_reduced_form;
	std::vector<float>		_degree;
	int				_max_degree;
	int				_equation_type;
	int				_flag_bonus;
	std::string			_equation_str;
	std::string			_err_msg;
};

#endif