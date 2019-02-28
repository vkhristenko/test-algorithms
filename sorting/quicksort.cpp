#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "../common/utils.hpp"

int partition(std::vector<int>& input, int l, int r) {
    int pivot = l;
    int i = l+1, j = l;

    while (i<=r) {
        if (input[i] <= input[pivot]) {
            j++;
            std::swap(input[i], input[j]);
        }

        i++;
    }

    std::swap(input[pivot], input[j]);
    return j;
}

void quick_sort_impl(std::vector<int>& input, int l, int r) {

    if (l>=r)
        return;

    int m = partition(input, l, r);
    quick_sort_impl(input, l, m-1);
    quick_sort_impl(input, m+1, r);
}

void quick_sort(std::vector<int>& input) {
    quick_sort_impl(input, 0, input.size()-1);
}

void rand_quick_sort_impl(std::vector<int>& input, int l, int r) {
    if (l>=r)
        return;

    int k = (std::rand() % (r-l+1)) + l; // rand number [l, r]
    std::swap(input[k], input[l]);
    int m = partition(input, l, r);
    rand_quick_sort_impl(input, l, m-1);
    rand_quick_sort_impl(input, m+1, r);
}

void rand_quick_sort(std::vector<int>& input) {
    rand_quick_sort_impl(input, 0, input.size() - 1);
}

int main(int argc, char **argv) {
    std::srand(std::time(nullptr));

    auto input = generate_random_vector<int>(std::atoi(argv[1]), 
        []{ return std::rand() % 1000; });
    std::vector<int> input_2{input};
    print_vector(std::cout, input);

    quick_sort(input);
    std::cout << "***\n";

    print_vector(std::cout, input);
    
    std::cout << "***\n";
    rand_quick_sort(input_2);
    print_vector(std::cout, input_2);

    return 0;
}
