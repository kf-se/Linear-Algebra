#pragma once
#include <format>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace vector {

template <typename T>
class Vector {
private:
	std::vector<T> data;

public:
	Vector(size_t size) : data(size) {}
	Vector(std::initializer_list<T> list) : data(list) {}
	[[nodiscard]] auto size() const -> size_t { return data.size(); }

	auto operator[](size_t i) -> T& {
		auto sz = size();
		if (i < 0 || i >= sz) {
			throw std::out_of_range(std::format("Index {} out of range, vector size: {}", i, sz));
		}
		return data[i];
	}

	auto operator[](size_t i) const -> const T& {
		auto sz = size();
		if (i < 0 || i >= sz) {
			throw std::out_of_range(std::format("Index {} out of range, vector size: {}", i, sz));
		}
		return data[i];
	}

	/* Unary minus operator */
	auto operator-() const -> const Vector<T> {
		Vector<T> ret(*this);
		for (size_t i = 0; i < ret.size(); ++i) {
			ret[i] = -ret[i];
		}

		return ret;
	}

	auto operator+(Vector<T>& rhs) -> Vector<T> {
		Vector<T> ret(*this);
		ret += rhs;
		return ret;
	}

	auto operator-(Vector<T>& rhs) -> Vector<T> {
		Vector<T> ret(*this);
		ret -= rhs;
		return ret;
	}

	auto operator*(T scalar) const -> Vector<T> {
		Vector<T> ret(*this);
		ret *= scalar;
		return ret;
	}

	auto operator/(T scalar) const -> Vector<T> {
		Vector<T> ret(*this);
		ret /= scalar;
		return ret;
	}

	auto operator+=(Vector<T>& rhs) -> Vector<T>& {
		if (this->size() != rhs.size()) {
			throw std::invalid_argument("Vector size mismatch");
		}

		for (size_t i = 0; i < this->size(); ++i) {
			data[i] += rhs[i];
		}
		return *this;
	}

	auto operator-=(Vector<T>& rhs) -> Vector<T>& {
		if (this->size() != rhs.size()) {
			throw std::invalid_argument("Vector size mismatch");
		}

		for (size_t i = 0; i < this->size(); ++i) {
			data[i] -= rhs[i];
		}
		return *this;
	}

	auto operator*=(T scalar) -> Vector<T>& {
		for (size_t i = 0; i < size(); ++i) {
			data[i] *= scalar;
		}
		return *this;
	}

	auto operator/=(T scalar) -> Vector<T>& {
		for (size_t i = 0; i < size(); ++i) {
			data[i] /= scalar;
		}
		return *this;
	}

	friend auto operator<<(std::ostream& stream, const Vector<T>& vec) -> std::ostream& {
		stream << "[";
		for (size_t i = 0; i < vec.size(); ++i) {
			stream << vec[i];
			if (i < vec.size() - 1) stream << ", ";
		}
		stream << "]";
		return stream;
	}
};

template <typename T>
static auto dot(Vector<T>& lhs, Vector<T>& rhs) -> T {
	if (lhs.size() != rhs.size()) {
		throw std::invalid_argument("Vector size mismatch");
	}

	T res = T{};
	for (size_t i = 0; i < lhs.size(); ++i) {
		res += lhs[i] * rhs[i];
	}
	return res;
}

}	 // namespace vector
