#include <iostream>
#include <chrono>

int main() {
    std::chrono::high_resolution_clock clock;

    const auto start = clock.now();

    std::cout << "Test" << std::endl;

    const auto end = clock.now();
    const auto ns = end - start;
    std::cout << ns.count() << "u" << std::endl;
}

/*
- simple main
- print
- time it
- make timing class
    - ctor
    - dtor
- move to header + cpp
- move main work to class + header + cpp
*/
