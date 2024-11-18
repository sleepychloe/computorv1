/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Computor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:59:37 by yhwang            #+#    #+#             */
/*   Updated: 2024/11/18 01:22:25 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

#include "./Parse.hpp"

class Computor: public Parse
{
public:
	Computor();
	Computor(const Computor& computor);
	Computor& operator=(const Computor& computor);
	~Computor();

private:

};

# endif
