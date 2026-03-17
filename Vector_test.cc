#include "Vector.hh"

#include <gtest/gtest.h>
using namespace vector;

class VectorTest : public ::testing::Test {
protected:
	Vector<double> v1{1.0, 2.0, 3.0};
	Vector<double> v2{4.0, 5.0, 6.0};
	Vector<double> zeros{0.0, 0.0, 0.0};
	const Vector<double> constV3{1.0, 2.0, 3.0};
};

TEST_F(VectorTest, SizeReturnsCorrectSize) { EXPECT_EQ(v1.size(), 3); }

TEST_F(VectorTest, SizeConstructorCreatesZeros) {
	Vector<double> v(3);
	for (size_t i = 0; i < v.size(); ++i) {
		EXPECT_DOUBLE_EQ(v[i], 0.0);
	}
}

TEST_F(VectorTest, InitializerListConstructor) {
	EXPECT_DOUBLE_EQ(v1[0], 1.0);
	EXPECT_DOUBLE_EQ(v1[1], 2.0);
	EXPECT_DOUBLE_EQ(v1[2], 3.0);
}

TEST_F(VectorTest, IndexOutOfRangeThrows) { EXPECT_THROW(v1[10], std::out_of_range); }

TEST_F(VectorTest, ScalarMultiplication) {
	auto res = v1 * 2.0;
	EXPECT_DOUBLE_EQ(res[0], 2.0);
	EXPECT_DOUBLE_EQ(res[1], 4.0);
	EXPECT_DOUBLE_EQ(res[2], 6.0);

	v1 *= 2.0;
	EXPECT_DOUBLE_EQ(v1[0], 2.0);
	EXPECT_DOUBLE_EQ(v1[1], 4.0);
	EXPECT_DOUBLE_EQ(v1[2], 6.0);
}

TEST_F(VectorTest, ScalarDivision) {
	auto res = v1 / 2.0;
	EXPECT_DOUBLE_EQ(res[0], 0.5);
	EXPECT_DOUBLE_EQ(res[1], 1.0);
	EXPECT_DOUBLE_EQ(res[2], 1.5);

	v1 /= 2.0;
	EXPECT_DOUBLE_EQ(v1[0], 0.5);
	EXPECT_DOUBLE_EQ(v1[1], 1.0);
	EXPECT_DOUBLE_EQ(v1[2], 1.5);
}

TEST_F(VectorTest, Addition) {
	auto res = v1 + v2;
	EXPECT_DOUBLE_EQ(res[0], 5.0);
	EXPECT_DOUBLE_EQ(res[1], 7.0);
	EXPECT_DOUBLE_EQ(res[2], 9.0);

	v1 += v2;
	EXPECT_DOUBLE_EQ(v1[0], 5.0);
	EXPECT_DOUBLE_EQ(v1[1], 7.0);
	EXPECT_DOUBLE_EQ(v1[2], 9.0);
}

TEST_F(VectorTest, Subtraction) {
	auto res = v2 - v1;
	EXPECT_DOUBLE_EQ(res[0], 3.0);
	EXPECT_DOUBLE_EQ(res[1], 3.0);
	EXPECT_DOUBLE_EQ(res[2], 3.0);

	v2 -= v1;
	EXPECT_DOUBLE_EQ(v2[0], 3.0);
	EXPECT_DOUBLE_EQ(v2[1], 3.0);
	EXPECT_DOUBLE_EQ(v2[2], 3.0);
}

TEST_F(VectorTest, Negation) {
	auto res = -v2;
	EXPECT_DOUBLE_EQ(res[0], -4.0);
	EXPECT_DOUBLE_EQ(res[1], -5.0);
	EXPECT_DOUBLE_EQ(res[2], -6.0);
}

TEST_F(VectorTest, Iterators) {
	auto res = 0;
	for (const double& it : v1) {
		res += it;
	}
	EXPECT_DOUBLE_EQ(res, 6.0);

	res = 0;
	for (double& it : v1) {
		res += it;
	}
	EXPECT_DOUBLE_EQ(res, 6.0);

	res = 0;
	for (const auto& it : constV3) {
		res += it;
	}
	EXPECT_DOUBLE_EQ(res, 6.0);
}

TEST_F(VectorTest, SizeMismatchThrows) {
	Vector<double> small{1.0, 2.0};
	EXPECT_THROW(v1 + small, std::invalid_argument);
}

TEST_F(VectorTest, DotProduct) {
	auto res = vector::dot(v1, v1);
	EXPECT_DOUBLE_EQ(res, 14.0) << res;
}
