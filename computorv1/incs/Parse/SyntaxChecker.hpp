/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SyntaxChecker.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 03:49:28 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 06:33:50 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_CHECKER_HPP
# define SYNTAX_CHECKER_HPP

#include <string>
#include <stack>
#include "./ParseError.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"

class SyntaxChecker
{
public:
	SyntaxChecker(std::string str, t_parse info);
	SyntaxChecker(const SyntaxChecker& checker);
	SyntaxChecker& operator=(const SyntaxChecker& checker);
	~SyntaxChecker();

	t_parse				get_info(void) const;

	std::string			check(std::string str);

private:
	SyntaxChecker();

	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				check_brackets(int str_type, std::string str);

	int				check_operator_first_last(std::string str, int pos);
	int				check_operator_duplicate(std::string str, int pos);
	int				check_operator_operand(std::string str, int pos);
	int				check_operator_between_variable(std::string str, int pos);
	int				check_operator_between_brackets(std::string str, int pos);
	int				check_operator(int str_type, std::string str);

	int				check_each_str(int str_type, std::string str);

	int				check_point(std::string str);

	int				check_caret(std::string str);

	std::string			_str;
	t_parse				_info;
	ParseError::t_error		_struct_error;
};

#endif
