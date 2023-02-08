#include "vector.hpp"
#include <iostream>
#include "./map.hpp"
#include <map>

int main(int argc, char** argv) {
	ft::map<int, std::string> A;
	A.insert(ft::make_pair(0, "A"));
	A.insert(ft::make_pair(-1, "B"));
    return (0);
}
