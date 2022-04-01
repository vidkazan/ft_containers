#include "vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <deque>

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

//int main() {
//    struct foo f;
//    f.str = "90";
//    f.n = 90;
//    f.l = 9;
//    ft::vector<struct foo> bar(201,f);
//    bar.pop_back();
//    std::cout << "| size: " << bar.size() << " | capacity: " << bar.capacity() << " |\n";
//    return 0;
//}

#include <stdlib.h>

#define MAX_RAM 400
#define BUFFER_SIZE 80
struct Buffer
{
    int idx;
    char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

int main(int argc, char** argv) {
    if (argc != 2)
    {
        std::cerr << "Usage: ./test seed" << std::endl;
        std::cerr << "Provide a seed please" << std::endl;
        std::cerr << "Count value:" << COUNT << std::endl;
        return 1;
    }
    const int seed = atoi(argv[1]);
    srand(seed);

    ft::vector<std::string> vector_str;
    ft::vector<int> vector_int(5, 1);
    ft::vector<Buffer> vector_buffer;
    for (int i = 0; i < COUNT; i++)
    {
        vector_buffer.push_back(Buffer());
    }

    for (int i = 0; i < COUNT; i++)
    {
        const int idx = rand() % COUNT;
        vector_buffer[idx].idx = 5;
    }
    ft::vector<Buffer>().swap(vector_buffer);

    try
    {
        for (int i = 0; i < COUNT; i++)
        {
                const int idx = rand() % COUNT;
            vector_buffer.at(idx);
            std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
        }
    }
    catch(const std::exception& e)
    {
        //NORMAL ! :P
    }
    return (0);
}