#include "vector.hpp"
#include <iostream>
#include <vector>

template<typename T>
void printVector(const ft::vector<T>& vector)
{
    std::cout << vector.size() << " " << vector.capacity() << "\n";
    for(size_t i=0;i<vector.size();i++)
    {
        std::cout << "pos: " << i << " " << vector.at(i) << "\n";
    }
}

struct foo{
    int n;
    std::string str;
    long long l;
};

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
    int idx;
    char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))


int main(int argc, char** argv) {
    ft::vector<int> vector_int;
	vector_int.push_back(1);
    return (0);
}
