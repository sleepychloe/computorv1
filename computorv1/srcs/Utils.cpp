/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 05:49:02 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 06:31:41 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Utils.hpp"

std::string	float_to_string(float num)
{
	std::stringstream	ss;

	ss << num;
	return (ss.str());
}
