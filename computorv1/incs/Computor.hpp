/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:37 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 05:14:50 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

#include "./Parse.hpp"

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
