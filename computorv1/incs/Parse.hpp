/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/17 13:35:18 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "../incs/Color.hpp"

# define TYPE_RATIONAL			-1
# define TYPE_HIGH_DEGREE		-2
# define TYPE_INDETERMINATE		-3
# define TYPE_NO_SOLUTION		-4
# define TYPE_CONSTANT			0
# define TYPE_LINEAR			1
# define TYPE_QUADRATIC			2

class Parse
{
public:
	Parse(char *argv);
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	char				get_variable(void);
	std::vector<float>		get_reduced_form(void);
	std::vector<float>		get_degree(void);
	int				get_equation_type(void);
	std::string			get_reduced_term_str(int flag_bonus);
	void				print_info(int flag_bonus);

private:
	Parse();

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
	int				get_term(std::string str,
						std::vector<std::string> &term,
						std::vector<float> &degree);

	int				make_reduced_form(std::vector<std::string> l_term,
						std::vector<std::string> r_term,
						std::vector<float> l_degree,
						std::vector<float> r_degree);
	int				check_calculable(void);

	char				_variable;
	std::vector<float>		_reduced_form;
	std::vector<float>		_degree;
	int				_equation_type;
	std::string			_err_msg;

};

#endif
