#include <libList.hpp>
#include <iostream>

int main() {
    List<int> list = {0, 1, 2};
    list = {4, 5};
    std::cout << list[1] << std::endl;
}
