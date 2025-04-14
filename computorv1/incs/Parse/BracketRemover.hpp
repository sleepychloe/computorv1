/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BracketRemover.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 05:14:44 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:36:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRACKET_REMOVER_HPP
# define BRACKET_REMOVER_HPP

#include <string>
#include "./TermAnalyzer.hpp"
#include "./ParseError.hpp"
#include "../MathUtils.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"

class BracketRemover
{
public:
	BracketRemover(std::string str, t_parse info);
	BracketRemover(const BracketRemover& remover);
	BracketRemover& operator=(const BracketRemover& remover);
	~BracketRemover();

	std::string			remove(std::string str);

private:
	BracketRemover();

	void				throw_err_msg(std::string function, std::string err_msg, int str_type);

	// remove brackets: term == 1
	void				remove_bracket_without_calc(std::string &str,
						std::vector<std::string> &s);
	int				find_next_bracket(std::vector<size_t> &i,
						std::vector<std::string> &s);
	int				remove_bracket_one_term(std::string &str);

	// remove brackets: term > 1
	void				check_front_str(std::vector<size_t> &i,
						std::vector<std::string> &s);
	void				apply_operation_from_front(std::string &tmp,
						std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				find_mul_dev_front_str(std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				apply_operation_from_back(std::string &tmp,
						std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				find_mul_dev_back_str(std::vector<size_t> &i,
						std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	void				get_bracket_str(std::vector<std::string> &s,
						std::pair<std::vector<std::string>, std::vector<float>> &term_degree);
	int				remove_bracket_multiple_term(std::string &str);

	int				remove_bracket(int str_type, std::string &str);

	std::string			_str;
	t_parse				_info;
	int				_str_type;
	ParseError::t_error		_struct_error;
	TermAnalyzer			_term_analyzer;
};

#endif
