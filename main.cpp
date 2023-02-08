#include "vector.hpp"
#include <iostream>
#include "./map.hpp"
#include <map>
#include <sstream>

int main(int argc, char** argv) {
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
	ss << " " << A.size() << " ";
	for (ft::map<int, int>::iterator first = A.begin(); first != A.end(); ++first)
		ss << " " << first->second;
	ft::map<int, int>::iterator	it1;
	ft::map<int, int>::iterator	it2;
	it1 = A.find(-1);
	it2 = A.find(1);
	A.erase(it1, it2);
	for (ft::map<int, int>::iterator first = A.begin(); first != A.end(); ++first)
		ss << " " << first->second;
	ss << " " << A.size() << " ";
	A.erase(A.find(-2));
	A.erase(A.find(2));
	for (ft::map<int, int>::iterator first = A.begin(); first != A.end(); ++first)
		ss << " " << first->second;
	ss << " " << A.size() << " ";
	A.erase(A.find(-3));
	A.erase(A.find(4));
	for (ft::map<int, int>::iterator first = A.begin(); first != A.end(); ++first)
		ss << " " << first->second;
	ss << " " << A.size();
	A.clear();
	ss << " " << A.size();


}
