#include "Vector.hh"

#include <iostream>

int main() {
	auto vec1 = Vector<double>(3);
	auto vec2 = Vector<double>{1, 2, 3};
	auto vec3 = Vector<double>{2, 2, 2};
	auto res = vec2 * 5.0;

	std::cout << res;

	return 0;
}
