/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 05:48:49 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/14 18:42:31 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include "../matrix/incs/Complex.hpp"
#include "./MathUtils.hpp"

std::string			float_to_string(float num);
std::string			complex_to_string(Complex<float> num);

int				is_int(float num);

void				fraction_reduction(float &n1, float &n2);
void				fraction_reduction(float &n1, float &n2, float &n3);

void				make_smallest_int(float &n1, float &n2);
void				make_smallest_int(float &n1, float &n2, float &n3);

void				split_square_num(float &num_int, float &num_real);

#endif
