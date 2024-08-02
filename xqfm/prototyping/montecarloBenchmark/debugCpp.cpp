#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <cmath>






int main() {
#include <valarray>
#include <iostream>
#include <stdexcept>

class XMatrix {
private:
  std::valarray<double> data;
  size_t rows, cols;

public:
  // Default constructor
  XMatrix();

    // Constructor with dimensions
  XMatrix(size_t rows, size_t cols);
    // Constructor with initializer list
  XMatrix(std::initializer_list<std::initializer_list<double>> init);

  // Get number of rows
  size_t numRows() const;
  // Get number of columns
  size_t numCols() const;

  // access operator
  double& operator()(size_t row, size_t col);
  // access operator
  const double& operator()(size_t row, size_t col) const;  
  // Matrix addition
  XMatrix operator+(const XMatrix& other) const;
  // Matrix subtraction
  XMatrix operator-(const XMatrix& other) const;
  // Matrix multiplication
  XMatrix operator*(const XMatrix& other) const;
  // Print matrix (for debugging)
  void print() const;
};

XMatrix::XMatrix(): rows(0), cols(0) {}

XMatrix::XMatrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows * cols) {}

// Constructor with initializer list
XMatrix::XMatrix(std::initializer_list<std::initializer_list<double>> init) {
        rows = init.size();
        cols = init.begin()->size();
        data.resize(rows * cols);
        size_t index = 0;
        for (const auto& row : init) {
            for (const auto& elem : row) {
                data[index++] = elem;
            }
        }
    }

double& XMatrix::operator()(size_t row, size_t col) {
        // if (row >= rows || col >= cols) {
        //     throw std::out_of_range("Index out of range.");
        // }
        return data[row * cols + col];
    }

const double& XMatrix::operator()(size_t row, size_t col) const {
        // if (row >= rows || col >= cols) {
        //     throw std::out_of_range("Index out of range.");
        // }
        return data[row * cols + col];
    }

size_t XMatrix::numRows() const { return rows; }
size_t XMatrix::numCols() const { return cols; }

XMatrix XMatrix::operator+(const XMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices dimensions do not match for addition.");
        }
        XMatrix result(rows, cols);
        result.data = data + other.data;
        return result;
    }

XMatrix XMatrix::operator-(const XMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices dimensions do not match for addition.");
        }
        XMatrix result(rows, cols);
        result.data = data - other.data;
        return result;
    }

XMatrix XMatrix::operator*(const XMatrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrices dimensions do not match for multiplication.");
        }
        XMatrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                double sum = 0.0;
                for (size_t k = 0; k < cols; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

void XMatrix::print() const {
       for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << "\n";
        }    }


XMatrix mcAnalytical(unsigned long numPaths, unsigned long numSteps, double T,
                      double mu, double sigma, double S0) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0.0, 1.0);

  double dt = T / numSteps;
  double sqrt_dt = std::sqrt(dt);
  XMatrix S(numPaths, numSteps);

  for (unsigned long i = 0; i < numPaths; ++i) {
    S(i, 0) = S0;
    for (unsigned long j = 1; j < numSteps; ++j) {
      double dW = dis(gen) * sqrt_dt;
      S(i, j) = S(i, j - 1) * std::exp((mu - 0.5*sigma*sigma)*dt + sigma*dW);
    };
  };

  return S;
}

double strike = 1.0;
double spot = 100.0;
double vol = 0.3;
double rate = 0.03;
int numPaths = 100000;
int numSteps = 300;
double T = 1.0;

auto start = std::chrono::high_resolution_clock::now();
XMatrix averageFinalValue = mcAnalytical(numPaths, numSteps, T, rate, vol, spot);
auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double> duration = end - start;
//std::cout << "Estimated average final value: " << averageFinalValue << std::endl;
std::cout << "Totalpaths: " << numPaths << std::endl;
std::cout << "Duration(seconds): " << duration.count() <<  std::endl;

return 0;
}
