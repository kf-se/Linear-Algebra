#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace math::matrix {

struct msize {
	size_t mz;
	size_t nz;
	auto operator==(const msize& rhs) const -> bool { return mz == rhs.mz && nz == rhs.nz; }
};

template <typename T>
class Matrix {
private:
	std::vector<T> matrix;
	msize sz;

public:
	Matrix(size_t m, size_t n) : matrix(m * n), sz(m, n) {}
	Matrix(std::initializer_list<T> data, size_t m, size_t n) : matrix(data), sz(m, n) {}
	Matrix(std::initializer_list<std::initializer_list<T>> data) {
		sz.mz = data.size();
		sz.nz = 0;
		if (sz.mz > 0) {
			for (auto& row : data) {
				size_t newRowSize = row.size();
				if (sz.nz == 0) {
					sz.nz = newRowSize;
				}
				assert((newRowSize == sz.nz) && "Rows must be of equal size in matrix.");
				matrix.append_range(row);
			}
		}
	}
	[[nodiscard]] auto size() const -> msize { return sz; }
};
}	 // namespace math::matrix
