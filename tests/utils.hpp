/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmilchev <kmilchev@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:32:14 by kmilchev          #+#    #+#             */
/*   Updated: 2022/09/21 11:08:41 by kmilchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS
# define UTILS
# include <iostream>
# include "colours.h"
# include <assert.h>

void	test_name(std::string name){
    std::cout << COLOUR_YELLOW << name << COLOUR_DEFAULT << "\n";
};

#endif //UTILS_HPP