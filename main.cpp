#include "vector.hpp"
#include <iostream>
#include "./map.hpp"
#include <map>
#include <sstream>

int main(int argc, char** argv) {
	std::ostringstream	ss;

	ft::map<int, int>	A;
	A.insert(ft::make_pair(4, 0));
	A.insert(ft::make_pair(2, -2));
	A.insert(ft::make_pair(6, 2));
	A.insert(ft::make_pair(3, -1));
	A.insert(ft::make_pair(5, 1));
	A.insert(ft::make_pair(1, -3));
	ss << " " << A.size();
	ft::pair<ft::map<int, int>::iterator, bool>	res;
	res = A.insert(ft::make_pair(7, 3));
	ss << " " << res.second;
	ss << " " << res.first->second;
	ss << " " << A.size();
	res = A.insert(ft::pair<int, int>(6, 8));
	ss << " " << res.second;
	ss << " " << res.first->second;
	ss << " " << A.size();
	ft::map<int, int>	B;
	B.insert(ft::pair<int, int>(1, 100));
	B.insert(ft::pair<int, int>(-1, -100));
	B.insert(ft::pair<int, int>(2, 200));
	ft::map<int, int>::iterator	it5;
	it5 = B.insert(B.begin(), ft::pair<int, int>(3, 300));
	ss << " " << it5->first;
	it5 = B.insert(B.begin(), ft::pair<int, int>(3, 300));
	ss << " " << it5->first;
	it5 = B.insert(B.end(), ft::pair<int, int>(-30, -3000));
	ss << " " << it5->first;
	it5 = B.insert(B.end(), ft::pair<int, int>(-30, -3000));
	ss << " " << it5->first;
	it5 = B.insert(--B.end(), ft::pair<int, int>(-2, -200));
	ss << " " << it5->first;
	it5 = B.insert(--B.end(), ft::pair<int, int>(-2, -200));
	ss << " " << it5->first;
	it5 = B.insert(++(++B.begin()), ft::pair<int, int>(-8, -800));
	ss << " " << it5->first;
	it5 = B.insert(++(++B.begin()), ft::pair<int, int>(-8, -800));
	ss << " " << it5->first;
	it5 = B.insert(--(--(--B.end())), ft::pair<int, int>(1000, 100000));
	ss << " " << it5->first;
	it5 = B.insert(--(--(--B.end())), ft::pair<int, int>(1000, 100000));
	ss << " " << it5->first;
	it5 = B.insert(--(--(--B.end())), ft::pair<int, int>(1000, 100000));
	ss << " " << it5->first << ",";
	for (ft::map<int, int>::iterator it = B.begin(); it != B.end(); ++it)
		ss << " " << it->second;
	ss << " " << B.size();
	ft::map<int, int>::iterator it10 = A.begin();
	ft::map<int, int>::iterator it11 = A.end();
	B.insert(it10, it11);
	for (ft::map<int, int>::iterator it = B.begin(); it != B.end(); ++it)
		ss << " " << it->second;
	ss << " " << B.size();
	B.clear();
	ss << " " << B.size();
}
