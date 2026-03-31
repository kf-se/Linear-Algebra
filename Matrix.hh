#pragma once

#include <cstddef>
#include <vector>

namespace math::matrix {
template <typename T>
class Matrix {
private:
	std::vector<T> matrix;

public:
	Matrix(size_t m, size_t n) : matrix(m * n) {}
};
}	 // namespace math::matrix
