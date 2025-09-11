#include <clad/Differentiator/Differentiator.h>
#include <iostream>

class Calculator {
public:
    double scale;

    Calculator(double s) : scale(s) {}

    double multiply(double x) const {
        return scale * x;
    }
};

int main() {
    Calculator calc(2.0);

    // Differentiate the multiply method with respect to the first parameter
    auto dMultiply = clad::differentiate(&Calculator::multiply, /*diffArg=*/0);

    double x = 3.0;
    double dValue = dMultiply(&calc, x);

    std::cout << "The derivative of multiply at x = " << x << " is " << dValue << std::endl;

    return 0;
}
