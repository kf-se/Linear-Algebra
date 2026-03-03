#include "Vector.hh"
#include <initializer_list>
#include <vector>

template <typename T> class Vector {
  private:
    std::vector<T> data;

  public:
    Vector(size_t size) {}
    Vector(std::initializer_list<T> list) : data(list) {}
};

int main() { return 0; }
