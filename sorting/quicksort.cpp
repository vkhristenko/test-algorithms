#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "../common/utils.hpp"

int main(int argc, char **argv) {
    std::srand(std::time(nullptr));

    auto input = generate_random_vector<int>(std::atoi(argv[1]), 
        []{ return std::rand() % 100; });
    print_vector(std::cout, input);

    return 0;
}
