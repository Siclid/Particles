#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

namespace Matrices {

    class Matrix {
    public:
        Matrix(int _rows, int _cols);       // Initialize matrix with specified size

        // Access and modify elements
        const double& operator()(int i, int j) const { return a.at(i).at(j); }
        double& operator()(int i, int j) { return a.at(i).at(j); }

        int getRows() const { return rows; }
        int getCols() const { return cols; }

    protected:
        vector<vector<double>> a;          // Matrix elements
    private:
        int rows, cols;                    // Matrix dimensions
    };

    Matrix operator+(const Matrix& a, const Matrix& b);
    Matrix operator*(const Matrix& a, const Matrix& b);
    bool operator==(const Matrix& a, const Matrix& b);
    bool operator!=(const Matrix& a, const Matrix& b);
    ostream& operator<<(ostream& os, const Matrix& a);

    //2D rotation matrix:  A = R * A rotates A theta radians counter-clockwise
    class RotationMatrix : public Matrix {
    public:
        RotationMatrix(double theta) : Matrix(2, 2) {
            a[0][0] = cos(theta); a[0][1] = -sin(theta);
            a[1][0] = sin(theta); a[1][1] = cos(theta);
        }  
    };

    //2D scaling matrix:  A = S * A expands or contracts A by the specified scaling factor
    class ScalingMatrix : public Matrix {
    public:
        ScalingMatrix(double scale) : Matrix(2, 2) {
            a[0][0] = scale; a[0][1] = 0;
            a[1][0] = 0; a[1][1] = scale;
        }
    };

    //2D Translation matrix:  A = T + A will shift all coordinates of A by (xShift, yShift)
    class TranslationMatrix : public Matrix {
    public:
        TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols) {
            for (int j = 0; j < nCols; ++j) {
                a[0][j] = xShift;
                a[1][j] = yShift;
            }
        }
    };
}

#endif // MATRIX_H_INCLUDED
