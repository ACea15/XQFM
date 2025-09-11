#include <iostream>
#include <Eigen/Dense>
//#include <clad/Differentiator.h>
#include "clad/Differentiator/Differentiator.h"

using namespace Eigen;

// A function that uses Eigen for calculations
double compute(const VectorXd& v, double m) {
    // Simple quadratic expression
    return m.dot(v);
}

int main() {
    // Set up a vector using Eigen
    VectorXd v(3);
    v << 1, 2, 3;

    // Output the original computation result
    std::cout << "Original Value: " << compute(v) << std::endl;

    // Differentiate using Clad
    auto grad = clad::gradient(compute, "m");

    // Convert Eigen VectorXd to raw double array
    double v_array[] = {1.0, 2.0, 3.0};

    // Compute the gradient
    const auto gradient = grad(v_array, 2.);

    // Output the gradient
    std::cout << "Gradient: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << gradient[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
