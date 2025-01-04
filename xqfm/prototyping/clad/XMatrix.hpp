#pragma once

#include <valarray>


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
