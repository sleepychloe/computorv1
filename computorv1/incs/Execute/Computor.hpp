/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:37 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 00:13:19 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <variant>
#include "../../matrix/incs/Complex.hpp"
#include "./LinearEquationSolver.hpp"
#include "./QuadraticEquationSolver.hpp"
#include "./ExecuteUtils.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

using	ValueSet = std::variant<float,
				Complex<float>>;

class Computor
{
public:
	Computor(t_parse info);
	Computor(const Computor& computor);
	Computor& operator=(const Computor& computor);
	~Computor();

	void				print_info(void);

	void				solve(void);

private:
	Computor();

	void				solve_equation(void);

	t_parse				_info;
	std::vector<float>		_term_descending_order;
	std::vector<ValueSet>		_solution;
	std::vector<std::string>	_str_solution;
};

# endif
