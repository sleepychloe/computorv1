/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TermAnalyzer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 06:06:07 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:36:52 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_ANALYZER_HPP
# define TERM_ANALYZER_HPP

#include <string>
#include <vector>
#include <sstream>
#include "./ParseError.hpp"
#include "../MathUtils.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"

class TermAnalyzer
{
public:
	TermAnalyzer();
	TermAnalyzer(std::string str, t_parse info);
	TermAnalyzer(const TermAnalyzer& analyzer);
	TermAnalyzer& operator=(const TermAnalyzer& analyzer);
	~TermAnalyzer();

	t_parse				get_info(void) const;

	std::vector<std::string>	split_term(std::string str);
	int				get_term(std::string str,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);

private:
	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	float				find_degree(std::string str);
	void				add_coefficient_of_variable(std::string &str);
	int				remove_variable(std::string &str);

	int				check_operation(std::string str);
	void				split_expression(std::string str,
						std::vector<float> &nb, std::vector<char> &op);
	float				calc(float nb1, float n2, char op);
	std::string			calculate(std::string str);

	std::string			_str;
	t_parse				_info;
	ParseError::t_error		_struct_error;
};

#endif
