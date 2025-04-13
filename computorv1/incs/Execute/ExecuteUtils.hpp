/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecuteUtils.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:14:56 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/13 23:24:54 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_UTILS_HPP
# define EXECUTE_UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <variant>
#include "../Utils.hpp"
#include "../Define.hpp"
#include "../Color.hpp"

using	ValueSet = std::variant<float,
				Complex<float>>;

void				print_process_liner(char variable,
						float a, float b, float solution);

void				print_process_quadratic(char variable,
						float a, float b, float c,
						std::vector<ValueSet> solution,
						std::vector<std::string> str_solution);

#endif
