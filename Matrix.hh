#pragma once

#include <cassert>
#include <cstddef>
#include <format>
#include <vector>

namespace math::matrix {

struct msize {
	size_t rows;
	size_t columns;
	auto operator==(const msize& rhs) const -> bool { return rows == rhs.rows && columns == rhs.columns; }
};

template <typename T>
class Matrix {
private:
	std::vector<T> matrix;
	msize sz;

public:
	Matrix(size_t m, size_t n) : matrix(m * n), sz(m, n) {}
	Matrix(std::initializer_list<T> data, size_t m, size_t n) : matrix(data), sz(m, n) {
		assert(data.size() == m * n && "Size mismatch between data and m * n.");
	}
	Matrix(std::initializer_list<std::initializer_list<T>> data) {
		sz.rows = data.size();
		sz.columns = 0;
		if (sz.rows > 0) {
			for (auto& row : data) {
				size_t newRowSize = row.size();
				if (sz.columns == 0) {
					sz.columns = newRowSize;
				}
				assert((newRowSize == sz.columns) && "Rows must be of equal size in matrix.");
				matrix.append_range(row);
			}
		}
	}
	[[nodiscard]] auto size() const -> msize { return sz; }

	auto operator()(int i, int j) const -> T {
		if (i * j > matrix.size()) {
			throw std::invalid_argument(std::format("Index i {}, j {} out of range {}", i, j, matrix.size()));
		}

		return matrix[(i * sz.columns) + j];
	}
};
}	 // namespace math::matrix
