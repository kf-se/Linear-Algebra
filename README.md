# Linear Algebra Library

A ground-up C++ linear algebra library targeting Newton-Raphson load flow analysis.

## Vector Class Functionality

### Arithmetic

**Addition and subtraction** — element-wise, same dimension required. Both mutating (`+=`, `-=`) and non-mutating (`+`, `-`) versions. The non-mutating ones create a new vector and leave the originals untouched.

**Scalar multiplication** — every element multiplied by a scalar. Both `*=` and `*`. Scalar division (`/=`, `/`) for Newton-Raphson updates involving dividing by norms or scaling step sizes.

**Negation** — unary minus. Given vector **v**, return **-v** where every element is negated. Useful for the Newton-Raphson step where you compute **-F(x)**.

### Inner Product and Norms

**Dot product** — for vectors **u** and **v** of dimension *n*: **u · v** = Σᵢ uᵢvᵢ. Foundation for everything else.

**Euclidean norm (L2)** — ‖**v**‖₂ = √(**v · v**) = √(Σᵢ vᵢ²). Convergence check in Newton-Raphson: iterate until ‖**F(x)**‖ < ε.

**Normalize** — return **v** / ‖**v**‖₂, a unit vector in the same direction.

### Utility

**Equality with tolerance** — two vectors are "equal" if ‖**u - v**‖ < ε for some small epsilon. Essential for testing with floating-point values.

**Stream output** — `operator<<` for printing vectors. Invaluable for debugging when a power flow iteration isn't converging.

**Size and element access** — `size()`, `operator[]` (const and non-const).

### Future (not yet implemented)

**Matrix-vector product** — lives on the Matrix class, but Vector is the return type of `Ax`.

**Iterators** — `begin()` and `end()` for range-based for loops over Vector elements.
