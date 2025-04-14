/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:25:33 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 19:01:27 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/MathUtils.hpp"

float	ft_abs(float n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

float	ft_sqrt(float n)
{
	if (n < 0)
		return (-1);
	if (n == 0 || n == 1)
		return (n);

	double	current = n;
	double	next;
	while (1)
	{
		next = 0.5 * (current + n / current);
		if (ft_abs(current - next) < EPSILON)
			break ;
		current = next;
	}
	return (next);
}
