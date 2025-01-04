#include <iostream>
#include <stdexcept>

#include "XMatrix.hpp"

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
    
