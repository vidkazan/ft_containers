/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_construction.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zangelis <zangelis@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:20:18 by kmilchev          #+#    #+#             */
/*   Updated: 2022/10/03 00:06:55 by zangelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vector.hpp"
#include <iostream>
#include "colours.h"
#include <vector>
#include "utils.hpp"


int main(void)
{
	test_name("Testing the default constructor");
	ft::vector<int> test;
	assert(0 == test.capacity());
	assert(0 == test.size());
	
	test_name("Testing the fill constructor");
	ft::vector<int> test1(4, 69);
	assert(4 == test1.capacity());
	assert(4 == test1.size());
	for (size_t i = 0; i < test1.size(); i++)
		assert(69 == *(test1.begin()));
	
	{
		test_name("Testing the range constructor");
        std::vector<int>::iterator itx;
        std::vector<int>::iterator itx2;
        std::vector<int> numbersx(6,33);
		ft::vector<int>::iterator it;
		ft::vector<int>::iterator it2;
		ft::vector<int> numbers(6, 33);
        numbersx[0] = 0;
        numbersx[1] = 1;
        numbersx[2] = 2;
        numbersx[3] = 3;
        numbersx[4] = 4;

		numbers[0] = 0;
		numbers[1] = 1;
		numbers[2] = 2;
        numbers[3] = 3;
        numbers[4] = 4;
        itx = numbersx.begin();
        itx2 = numbersx.end();
		it = numbers.begin();
		it2 = numbers.end();
		ft::vector<int> numbers2(it, it2);
		std::vector<int> numbersx2(itx,itx2);
        assert(numbersx2.capacity() == numbers2.capacity());
		assert(0 == *(numbers2.begin()));
		assert(1 == *(numbers2.begin() + 1));
		assert(2 == *(numbers2.begin() + 2));
		assert(3 == *(numbers2.begin() + 3));
		assert(4 == *(numbers2.begin() + 4));
		assert(33 == *(numbers2.begin() + 5));
	}

	{
		test_name("Testing the copy constructor");
		ft::vector<int> my_numbers(6, 33);
		std::vector<int> og_numbers(6, 33);
		og_numbers.reserve(17);
		my_numbers.reserve(17);
		ft::vector<int> new_vec(my_numbers);
		std::vector<int> new_vec_og(og_numbers);

		for (size_t i = 0; i < new_vec.size(); i++)
			assert((new_vec[i] == og_numbers[i]) == (my_numbers[i] == new_vec_og[i]));
		assert(my_numbers.size() == new_vec.capacity());
		assert(og_numbers.size() == new_vec_og.capacity());
		assert(my_numbers.size() == new_vec_og.capacity());
	}

	{
		test_name("Testing the assignment operator");
		ft::vector<int> my_numbers(6, 33);
		ft::vector<int> my_empty;
		my_empty = my_numbers;
		assert(my_empty == my_numbers);
		assert(33 == my_empty[0]);

		ft::vector<int> my_non_empty(7, 7);
		my_non_empty = my_numbers;
		assert(my_non_empty == my_numbers);
		assert(33 == my_non_empty[0]);
		ft::vector<int> my_new_empty;
		ft::vector<int> my_newer_empty;
		my_new_empty = my_newer_empty;
		assert(my_new_empty == my_newer_empty);
	}
//	std::cout << COLOUR_DEFAULT;

	return (0);
}