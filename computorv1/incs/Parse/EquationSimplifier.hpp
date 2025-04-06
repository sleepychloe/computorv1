/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EquationSimplifier.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 07:07:42 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:39:12 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUATION_SIMPLIFIER_HPP
# define EQUATION_SIMPLIFIER_HPP

#include <string>
#include "./TermAnalyzer.hpp"
#include "./ParseError.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"

class EquationSimplifier
{
public:
	EquationSimplifier(std::string str, t_parse info);
	EquationSimplifier(const EquationSimplifier& simplifier);
	EquationSimplifier& operator=(const EquationSimplifier& simplifier);
	~EquationSimplifier();

	t_parse				get_info(void) const;

	std::string			simplify(std::string str);

private:
	EquationSimplifier();
	
	void				set_info_term_degree
						(std::pair<std::vector<std::string>, std::vector<float>> l_term_degree,
						std::pair<std::vector<std::string>, std::vector<float>> r_term_degree);

	void				set_equation_type(void);

	void				make_form_ascending_order(void);

	std::string			mandatory(void);
	std::string			bonus(void);
	std::string			set_equation_str(void);

	std::string			make_reduced_form(void);

	std::string			_str;
	t_parse				_info;
	ParseError::t_error		_struct_error;
	TermAnalyzer			_term_analyzer;
};

#endif
