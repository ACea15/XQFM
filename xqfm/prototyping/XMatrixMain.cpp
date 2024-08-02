#include <iostream>
#include "XMatrix.hpp"

int main() {
    XMatrix m1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    XMatrix m2{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    XMatrix m3 = m1 + m2;
    XMatrix m4 = m1 * m2;
    
    std::cout << "Matrix m1:\n";
    m1.print();

    std::cout << "Matrix m3 (addition):\n";
    m3.print();

    std::cout << "\nMatrix m4 (multiplication):\n";
    m4.print();

    return 0;
}
