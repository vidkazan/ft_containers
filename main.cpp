#include "vector.hpp"
#include <iostream>
#include "./map.hpp"
#include <map>
#include <sstream>

int main(int argc, char** argv)
{
	std::ostringstream	ss;

	ft::map<char, char>	A;
	A['a'] = 'A';
	A['b'] = 'B';
	A['c'] = A['b'];
	ss << " " << A['a'];
	ss << " " << A['b'];
	ss << " " << A['c'];
	ss << " " << A['d'];
	A.at('a') = 'a';
	A.at('b') = 'b';
	A.at('c') = 'c';
	ss << " " << A.at('a');
	ss << " " << A.at('b');
	ss << " " << A.at('c');
	try
	{
		A.at('t');
	}
	catch (const std::out_of_range &e)
	{
		ss << " " << 1;
	}
}
