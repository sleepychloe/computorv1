/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputConvertor.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 02:54:18 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 06:33:41 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_CONVERTOR_HPP
# define INPUT_CONVERTOR_HPP

#include <string>
#include "./ParseError.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"

class InputConvertor
{
public:
	InputConvertor(std::string str, t_parse info);
	InputConvertor(const InputConvertor& convertor);
	InputConvertor& operator=(const InputConvertor& convertor);
	~InputConvertor();

	t_parse				get_info(void) const;

	std::string			convert(std::string str);

private:
	InputConvertor();

	void				throw_err_msg(std::string function, std::string err_msg, size_t pos);

	int				is_equation_form(std::string str);
	int				check_equal_sign(std::string str);
	int				check_each_term(std::string str);

	int				set_variable(std::string str);
	int				check_duplicate(std::string str);
	int				check_variable(std::string str);

	int				check_invalid_character(std::string str);

	int				check_number(std::string str);

	void				remove_space(std::string &str);

	std::string			_str;
	t_parse				_info;
	ParseError::t_error		_struct_error;
};

#endif
