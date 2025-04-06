/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Struct.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 02:38:20 by yhwang            #+#    #+#             */
/*   Updated: 2025/04/06 03:10:29 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_HPP
# define STRUCT_HPP

#include <string>
#include <vector>

typedef struct s_parse
{
	char				variable;
	std::vector<float>		reduced_form;
	std::vector<float>		degree;
	int				max_degree;
	int				equation_type;
	int				flag_bonus;
	std::string			equation_str;
	
}	t_parse;

# endif
