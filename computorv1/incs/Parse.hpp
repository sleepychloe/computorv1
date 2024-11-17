/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/17 01:52:40 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

# define TYPE_RATIONAL			-1
# define TYPE_HIGH_DEGREE		-1
# define TYPE_INDETERMINATE		-1
# define TYPE_NO_SOLUTION		-1
# define TYPE_LINEAR			1
# define TYPE_QUADRATIC			2

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
	int				check_point(std::string str);
	int				check_caret(std::string str);
	int				check_syntax(std::string str);

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

	int				make_reduced_form(void);
	int				check_calculable(void);

	char				_variable;

	std::vector<std::string>	_l_term;
	std::vector<std::string>	_r_term;
	std::vector<float>		_l_degree;
	std::vector<float>		_r_degree;
	std::vector<std::string>	_reduced_form;
	std::vector<float>		_degree;
	int				_equation_type;
	std::string			_err_msg;

};

#endif
