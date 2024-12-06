#include "Matrices.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace Matrices;

namespace Matrices {
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols) {
        a = vector<vector<double>>(_rows, vector<double>(_cols, 0));
    }

    Matrix operator+(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix result(a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                result(i, j) = a(i, j) + b(i, j);
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& a, const Matrix& b) {
         if (a.getCols() != b.getRows()) {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix result(a.getRows(), b.getCols());

        for (int i = 0; i < a.getRows(); ++i) {
            for (int k = 0; k < b.getCols(); ++k) {
                result(i, k) = 0;
                for (int j = 0; j < a.getCols(); ++j) {
                    result(i, k) += a(i, j) * b(j, k);
                }
            }
        }

        return result;
    }


    bool operator==(const Matrix& a, const Matrix& b) {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
            return false;
        }
        for (int i = 0; i < a.getRows(); i++) {
            for (int j = 0; j < b.getCols(); j++) {
                if (fabs(a(i,j) - b(i,j)) >= 0.001) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b) {
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Matrix& a) {
        for (int i = 0; i < a.getRows(); ++i) {
            for (int j = 0; j < a.getCols(); ++j) {
                os << setw(10) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }
   
}
