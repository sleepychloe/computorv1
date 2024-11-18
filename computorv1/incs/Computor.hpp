/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:37 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 12:49:12 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

#include "./Parse.hpp"

# define TYPE_CONSTANT			0
# define TYPE_LINEAR			1
# define TYPE_QUADRATIC			2

# define SOLUTION_INDETERMINATE		"INDETERMINATE"
# define SOLUTION_ZERO			"NO SOLUTION"
# define SOLUTION_ONE			"1"
# define SOLUTION_TWO			"2"

class Computor: public Parse
{
public:
	Computor(char *argv, int flag_bonus);
	Computor(const Computor& computor);
	Computor& operator=(const Computor& computor);
	~Computor();

	void				print_info(void);

	void				solve_quadratic(void);
	void				solve_equation(void);

private:
	Computor();

	std::string			_type_solution;
	float				_discriminant;
	std::vector<float>		_solution;
};

# endif
