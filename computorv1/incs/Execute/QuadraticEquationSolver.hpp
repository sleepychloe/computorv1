/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuadraticEquationSolver.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:12:22 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:40:08 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATIC_EQUATION_SOLVER
# define QUADRATIC_EQUATION_SOLVER

#include <iostream>
#include <vector>
#include <variant>
#include "../../matrix/incs/Complex.hpp"
#include "./SolutionStrGenerator.hpp"
#include "../MathUtils.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

using	ValueSet = std::variant<float,
				Complex<float>>;

class QuadraticEquationSolver
{
public:
	QuadraticEquationSolver(t_parse info, float a, float b, float c);
	QuadraticEquationSolver(const QuadraticEquationSolver& solver);
	QuadraticEquationSolver& operator=(const QuadraticEquationSolver& solver);
	~QuadraticEquationSolver();

	std::vector<ValueSet>		get_solution(void) const;
	std::vector<std::string>	get_str_solution(void) const;

	void				solve(void);
	
private:
	QuadraticEquationSolver();

	void				print_variant_value(ValueSet value);

	void				print_solution(std::string type, int idx);

	void				is_positive_disriminant(void);
	void				is_zero_discriminant(void);
	void				is_negative_discriminant(void);

	t_parse				_info;
	float				_a;
	float				_b;
	float				_c;
	float				_discriminant;
	std::vector<ValueSet>		_solution;
	std::vector<std::string>	_str_solution;
	SolutionStrGenerator		_generator;
};

#endif
