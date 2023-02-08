#include <iostream>
#include <cassert>
#include <string.h>
#include "../utils.hpp"
#include "../map.hpp"
#include "../vector.hpp"
#include "colours.h"
#include "utils.hpp"
#include <map>
#include <typeinfo>

int main(void)
{
	ft::map<int, std::string> my_map;
	std::map<int, std::string> og_map;
	
	std::cout << COLOUR_GREEN <<typeid(my_map.value_comp()).name() << "\n\n";
	std::cout << typeid(og_map.value_comp()).name() << COLOUR_DEFAULT << std::endl;
	assert(typeid(my_map.key_comp()).name() == typeid(og_map.key_comp()).name());
	std::cout << COLOUR_DEFAULT;
	return (0);
}