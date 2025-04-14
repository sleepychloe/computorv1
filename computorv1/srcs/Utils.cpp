/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 05:49:02 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:44:50 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Utils.hpp"

std::string	float_to_string(float num)
{
	std::stringstream	ss;

	ss << num;
	return (ss.str());
}

std::string	complex_to_string(Complex<float> num)
{
	std::string	res = "";

	if (num.real() == 0 && num.imag() == 0)
		res += "0";
	else if (num.real() && num.imag() == 0)
		res += float_to_string(num.real());
	else if (num.real() == 0 && num.imag())
	{
		if (num.imag() < 0)
			res += "- ";
		res += float_to_string(ft_abs(num.imag())) + "i";
	}
	else
	{
		res += float_to_string(num.real());
		if (num.imag() < 0)
			res += " - " + float_to_string(-1 * num.imag()) + "i";
		else
			res += " + " + float_to_string(num.imag()) + "i";
	}
	return (res);
}

int	is_int(float num)
{
	if (ft_abs(num - (int)num) <= 1e-6)
		return (1);
	return (0);
}

void	fraction_reduction(float &n1, float &n2)
{
	std::vector<int>	tmp;
	float			common = 1;

	for (size_t i = 2; i <= ft_abs(n1); i++)
	{
		if (is_int(n1 / i))
			tmp.push_back(i);
	}
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (is_int(n2 / tmp[i]))
			common = tmp[i];
	}
	n1 /= common;
	n2 /= common;
}

void	fraction_reduction(float &n1, float &n2, float &n3)
{
	std::vector<int>	tmp;
	float			common = 1;

	for (size_t i = 2; i <= ft_abs(n1); i++)
	{
		if (is_int(n1 / i))
			tmp.push_back(i);
	}
	for (size_t i = 0; i < tmp.size(); i++)
	{
		if (is_int(n2 / tmp[i]) && is_int(n3 / tmp[i]))
			common = tmp[i];
	}
	n1 /= common;
	n2 /= common;
	n3 /= common;
}

void	make_smallest_int(float &n1, float &n2)
{
	int	tmp = 1;
	std::function<void(float)>	multiply = [&](float num)
	{
		tmp = 1;
		while (!is_int(num * tmp))
			tmp *= 10;
		n1 *= tmp;
		n2 *= tmp;
		fraction_reduction(n1, n2);
	};

	while (!(is_int(n1) && is_int(n2)))
	{
		if (!is_int(n1))
			multiply(n1);
		else if (!is_int(n2))
			multiply(n2);
	}
}

void	make_smallest_int(float &n1, float &n2, float &n3)
{
	int	tmp = 1;
	std::function<void(float)>	multiply = [&](float num)
	{
		tmp = 1;
		while (!is_int(num * tmp))
			tmp *= 10;
		n1 *= tmp;
		n2 *= tmp;
		n3 *= tmp;
		fraction_reduction(n1, n2, n3);
	};

	while (!(is_int(n1) && is_int(n2) && is_int(n3)))
	{
		if (!is_int(n1))
			multiply(n1);
		else if (!is_int(n2))
			multiply(n2);
		else if (!is_int(n3))
			multiply(n3);
	}
}

void	split_square_num(float &num_int, float &num_real)
{
	float			copy_real = num_real;
	std::vector<int>	tmp;

	for (int i = 2; i <= copy_real; i++)
	{
		if (is_int(copy_real / i))
		{
			tmp.push_back(i);
			copy_real /= i;
			i = 1;
		}
	}

	for (size_t i = 1; i < tmp.size(); i++)
	{
		if (tmp[i - 1] == tmp[i])
		{
			num_int *= tmp[i];
			i = i + 2;
		}
	}
	num_real /= num_int * num_int;
}
