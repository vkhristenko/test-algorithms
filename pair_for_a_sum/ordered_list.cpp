#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <ctime>

std::vector<int> generate_random(int n) {
    std::vector<int> result(n);
    for (int i=0; i<n; i++)
        result[i] = std::rand() % 100;

    return result;
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
find_pair(std::vector<int> const& input, int s) {
    std::vector<int>::const_iterator first{input.begin()}, second{--(input.end())};

    while (first != second) {
        auto test_sum = *first + *second;
        if (test_sum < s)
            ++first;
        else if (test_sum > s)
            --second;
        else 
            return {first, second};
    }

    return {input.end(), input.end()};
}

void run(int n, int s) {
    auto input = generate_random(n);
    std::sort(input.begin(), input.end());
    std::cout << "{ ";
    for (auto const& value : input)
        std::cout << value << ", ";
    std::cout << " }" << std::endl;

    if (auto p = find_pair(input, s); p.first != input.end())
        std::cout << "found pair. " << *p.first << " + " << *p.second 
                  << " = " << s  << std::endl;
    else 
        std::cout << "did not find a pair for sum = " << s << std::endl;
}

int main(int argc, char **argv) {
    std::srand(time(nullptr));
    run(std::atoi(argv[1]), std::atoi(argv[2]));
}
