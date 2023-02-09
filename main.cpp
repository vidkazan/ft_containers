#include "vector.hpp"
#include <iostream>
#include "./map.hpp"
#include <map>
#include <sstream>

int main(int argc, char** argv)
{
	std::ostringstream	ss;

	ft::map<int, int>	A;
	A.insert(ft::make_pair(0, 0));
	A.insert(ft::make_pair(-2, -2));
	A.insert(ft::make_pair(2, 2));
	A.insert(ft::make_pair(-1, -1));
	A.insert(ft::make_pair(1, 1));
	A.insert(ft::make_pair(-3, -3));
	A.insert(ft::make_pair(3, 3));
	A.insert(ft::make_pair(-4, -4));
	A.insert(ft::make_pair(4, 4));
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator>	p;
	p = A.equal_range(-1);
	ss << " " << p.first->first;
	ss << " " << p.second->first;
	p = A.equal_range(-4);
	ss << " " << p.first->first;
	ss << " " << p.second->first;
	ft::map<int, int>	B;
	B.insert(ft::pair<int, int>(100, 10000));
	B.insert(ft::pair<int, int>(-100, -10000));
	B.insert(ft::pair<int, int>(200, 20000));
	ft::map<int, int>::iterator	it5;
	it5 = B.insert(B.begin(), ft::pair<int, int>(30, 3000));
	it5 = B.insert(B.end(), ft::pair<int, int>(-300, -30000));
	for (ft::map<int, int>::iterator f = A.begin(); f != A.end(); ++f)
		ss << " " << f->second;
	for (ft::map<int, int>::iterator f = B.begin(); f != B.end(); ++f)
		ss << " " << f->second;
	A = B;
	for (ft::map<int, int>::iterator f = A.begin(); f != A.end(); ++f)
		ss << " " << f->second;
	ft::map<int, int>	C;
	C.insert(ft::make_pair(0, 0));
	C.insert(ft::make_pair(-2, -2));
	A = C;
	for (ft::map<int, int>::iterator f = A.begin(); f != A.end(); ++f)
		ss << " " << f->second;
	ft::map<int, int>	D(B.begin(), B.end());
	for (ft::map<int, int>::iterator f = D.begin(); f != D.end(); ++f)
		ss << " " << f->second;
}
