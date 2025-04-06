/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:09:58 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 07:47:10 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <cstring>

#include "./InputConvertor.hpp"
#include "./SyntaxChecker.hpp"
#include "./BracketRemover.hpp"
#include "./EquationSimplifier.hpp"
#include "./ParseError.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

class Parse
{
public:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	virtual ~Parse();

	t_parse				get_info(void) const;

	void				parse(char *argv, int flag_bonus);

private:
	int				parse_start(std::string str);

	t_parse				_info;
};

#endif
