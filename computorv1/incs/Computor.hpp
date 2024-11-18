/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:37 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 07:12:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

#include "./Parse.hpp"

# define TYPE_CONSTANT			0
# define TYPE_LINEAR			1
# define TYPE_QUADRATIC			2
# define TYPE_INDETERMINATE		-10
# define TYPE_NO_SOLUTION		-11

class Computor: public Parse
{
public:
	Computor(char *argv, int flag_bonus);
	Computor(const Computor& computor);
	Computor& operator=(const Computor& computor);
	~Computor();

	void			print_info(void);

private:
	Computor();

};

# endif
