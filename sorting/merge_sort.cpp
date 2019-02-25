#include <vector>
#include <iostream>
#include <cstdio>

#include "../common/utils.hpp"

void merge_impl(std::vector<int>& in, 
                std::vector<int>& out,
                int first, int middle, int last) {
    int next_left = first;
    int next_right = middle+1;
    int next = first;

    while (next_left<=middle && next_right<=last) {
        if (in[next_left] > in[next_right]) {
            out[next] = in[next_right];
            next_right++;
        }
        else {
            out[next] = in[next_left];
            next_left++;
        }

        next++;
    }
    assert(next_left>middle || next_right>last);

    // only one of the while loops will be actually trigger
    while (next_left<=middle)
        out[next++] = in[next_left++];
    while (next_right<=last)
        out[next++] = in[next_right++];
}

void merge_sort_impl(std::vector<int>& in,
                     std::vector<int>& tmp,
                     int first, int last) {
    // if size == 1
    if (last==first) {
        tmp[last] = in[last];
        return;
    }

    int middle = (last + first) / 2;
    // merge_sort left half
    merge_sort_impl(in, tmp, first, middle);
    // merge_sort
    merge_sort_impl(in, tmp, middle + 1, last);
    // merge
    merge_impl(tmp, in, first, middle, last);
}

void merge_sort(std::vector<int>& in) {
    std::vector<int> tmp(in.size());
    merge_sort_impl(in, tmp, 0, in.size()-1);
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
