#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <ctime>

template<typename T>
std::vector<T> generate_random_vector(int n, std::function<T()> gen) {
    std::vector<T> result(n);
    for (int i=0; i<n; i++)
        result[i] = gen();

    return result;
}

template<typename T>
std::ostream& print_vector(std::ostream& os, std::vector<T> const& xs) {
    os << "{ ";
    for (auto const& x : xs) 
        os << x << ", ";
    return os << " }\n";
}
