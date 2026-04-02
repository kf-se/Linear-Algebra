#include "Matrix.hh"

#include <gtest/gtest.h>

using namespace math::matrix;

class MatrixTest : public ::testing::Test {
protected:
	Matrix<double> m1{{1.0, 2.0, 3.0}};
	Matrix<double> m2{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
	Matrix<double> m3{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
	Matrix<double> zeros{{0.0, 0.0, 0.0}};
	const Matrix<double> constM3{{1.0, 2.0, 3.0}};
};

TEST_F(MatrixTest, constructor) {
	msize exp(1, 3);
	EXPECT_EQ(exp, m1.size());
}
