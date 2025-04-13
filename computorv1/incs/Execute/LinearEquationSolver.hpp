/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LinearEquationSolver.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:06:00 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/13 22:26:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINER_EQUATION_SOLER_HPP
# define LINER_EQUATION_SOLER_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <variant>
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

using	ValueSet = std::variant<float,
				Complex<float>>;

class LinerEquationSolver
{
public:
	LinerEquationSolver(t_parse info, float a, float b);
	LinerEquationSolver(const LinerEquationSolver& solver);
	LinerEquationSolver& operator=(const LinerEquationSolver& solver);
	~LinerEquationSolver();

	std::vector<ValueSet>		get_solution(void) const;
	std::vector<std::string>	get_str_solution(void) const;

	void				solve(void);

private:
	LinerEquationSolver();

	void				print_solution(void);
	void				make_str_solution(void);

	t_parse				_info;
	float				_a;
	float				_b;
	std::vector<ValueSet>		_solution;
	std::vector<std::string>	_str_solution;
};

#endif
