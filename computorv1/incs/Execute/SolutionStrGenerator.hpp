/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SolutionStrGenerator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:06:20 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:41:21 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLUTION_STR_GENERATOR_HPP
# define SOLUTION_STR_GENERATOR_HPP

#include <iostream>
#include <vector>
#include "../../matrix/incs/Complex.hpp"
#include "../MathUtils.hpp"
#include "../Utils.hpp"
#include "../Struct.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

typedef struct s_term
{
	/* numerator first term(-1*b) */
	float		first_term;

	/* numerator second term(b*b-4*a*c) */
	float		second_term_int;
	float		second_term_real;

	/* denominator(2*a) */
	float		denominator;
}	t_term;

class SolutionStrGenerator
{
public:
	SolutionStrGenerator();
	SolutionStrGenerator(float a, float b, float c, float discriminant);
	SolutionStrGenerator(const SolutionStrGenerator& generator);
	SolutionStrGenerator& operator=(const SolutionStrGenerator& generator);
	~SolutionStrGenerator();

	std::vector<std::string>	get_str_solution(void) const;

	void				generate(void);
	
private:
	void				double_solution(void);
	void				real_solution_square_num(void);
	void				general_solution_square_num(std::string &str_1, std::string &str_2);
	void				general_solution_general(std::string &str_1, std::string &str_2);
	void				general_solution(void);

	t_term				_term;
	float				_a;
	float				_b;
	float				_c;
	float				_discriminant;
	std::vector<std::string>	_str_solution;
};

#endif
