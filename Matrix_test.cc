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

TEST_F(MatrixTest, index) {
	EXPECT_EQ(1, m1(0, 0));
	EXPECT_EQ(2, m1(0, 1));
	EXPECT_EQ(3, m1(0, 2));

	EXPECT_EQ(4, m2(1, 0));
	EXPECT_EQ(5, m2(1, 1));
	EXPECT_EQ(6, m2(1, 2));
}
