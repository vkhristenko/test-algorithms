#include <iostream>
#include <unordered_set>
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

std::pair<bool, std::pair<int, int>>
find_pair(std::vector<int> const& input, int s) {
    std::unordered_set<std::vector<int>::value_type> lookup;

    for (auto x : input) {
        if (auto y = s-x; lookup.find(y) != lookup.end())
            return {true, {y, x}};
        else 
            lookup.insert(x);
    }

    return {false, {-1, -1}};
}

void run(int n, int s) {
    auto input = generate_random(n);
    std::cout << "{ ";
    for (auto const& value : input)
        std::cout << value << ", ";
    std::cout << " }" << std::endl;

    if (auto p = find_pair(input, s); p.first)
        std::cout << "found pair. " << p.second.first << " + " << p.second.second 
                  << " = " << s  << std::endl;
    else 
        std::cout << "did not find a pair for sum = " << s << std::endl;
}

int main(int argc, char **argv) {
    std::srand(time(nullptr));
    run(std::atoi(argv[1]), std::atoi(argv[2]));
}
