/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:25:33 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/16 03:57:41 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/MathUtils.hpp"

float	ft_abs(float n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

/*
	calculate square root using the newton-raphson method

	let y = √(x), t ≈ √x (so t² ≈ x)

	The goal is to find t
	such that the error (t² - x) approaches 0 as t converges

	f(t) = t² - x, f'(t) = 2t
	equation of tangent line at (t₀, f(t₀)) is y = f'(t₀)(t - t₀) + f(t₀)

	we want to know the value at the interception of x-axis and f(t),
	so that error(t² - x) = 0
	let the point is (t₁, 0)
	0 = f'(t₁)(t - t₁) + f(t₁)
	∴ t = t₁ - f(t₁) / f'(t₁) = (x + t₁²) / 2t₁

	so the iterative formula is
	: xₙ₊₁ = xₙ - f(xₙ) / f'(xₙ) = (n + xₙ²) / 2xₙ
	(n is input value whose square root value we want to approximate)
*/

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
		next = (n + current * current) / (2 * current);
		if (ft_abs(current - next) < EPSILON)
			break ;
		current = next;
	}
	return (next);
}
