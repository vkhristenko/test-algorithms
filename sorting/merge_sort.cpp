#include <vector>
#include <iostream>
#include <cstdio>

#include "../common/utils.hpp"

void merge_impl(std::vector<int>& in, 
                int first, int middle, int last) {
    std::vector<int> left; left.reserve(middle-first + 1);
    std::vector<int> right; right.reserve(last-middle);
    int i=first;
    while (i<=middle)
        left.push_back(in[i++]);
    while (i<=last)
        right.push_back(in[i++]);

    /*
    std::cout << first << " " << middle << " " << last << "\n";
    print_vector(std::cout, left);
    print_vector(std::cout, right);
    */

    int next_left = 0;
    int next_right = 0;
    int next = first;
    while (next_left<left.size() && next_right<right.size()) {
        if (left[next_left] > right[next_right])
            in[next++] = right[next_right++];
        else
            in[next++] = left[next_left++];
    }
    assert(next_left>=left.size() || next_right>=right.size());

    // only one of the while loops will be actually trigger
    while (next_left<left.size())
        in[next++] = left[next_left++];
    while (next_right<right.size())
        in[next++] = right[next_right++];
}

void split(std::vector<int>& in,
                     int first, int last) {
    // if size == 1, each guy is trivially sorted
    if (last==first) {
        return;
    }

    int middle = (last + first) / 2;
    // merge_sort left half
    split(in, first, middle);
    // merge_sort
    split(in, middle + 1, last);
    // merge
    merge_impl(in, first, middle, last);
}

void merge_sort(std::vector<int>& in) {
    split(in, 0, in.size()-1);
}

int main(int argc, char** argv) {
    if (argc<2) {
        printf("run with ./merge_sort <number of array elements>\n");
        exit(0);
    }
    int n = std::atoi(argv[1]);

    std::srand(std::time(nullptr));
    auto input = generate_random_vector<int>(n,
        []{return std::rand() % 1000; });
    print_vector(std::cout, input);
    merge_sort(input);
    std::cout << "***\n";
    print_vector(std::cout, input);
}
