# Linear Algebra Library

A ground-up C++ linear algebra library targeting Newton-Raphson load flow analysis.

## Vector Class Functionality

### Arithmetic

[x] **Addition and subtraction** — element-wise, same dimension required. Both mutating (`+=`, `-=`) and non-mutating (`+`, `-`) versions. The non-mutating ones create a new vector and leave the originals untouched.

[x] **Scalar multiplication** — every element multiplied by a scalar. Both `*=` and `*`. Scalar division (`/=`, `/`) for Newton-Raphson updates involving dividing by norms or scaling step sizes.

[x] **Negation** — unary minus. Given vector **v**, return **-v** where every element is negated. Useful for the Newton-Raphson step where you compute **-F(x)**.

### Inner Product and Norms

[x] **Dot product** — for vectors **u** and **v** of dimension *n*: **u · v** = Σᵢ uᵢvᵢ. Foundation for everything else.

[x] **Euclidean norm (L2)** — ‖**v**‖₂ = √(**v · v**) = √(Σᵢ vᵢ²). Convergence check in Newton-Raphson: iterate until ‖**F(x)**‖ < ε.

[x] **Normalize** — return **v** / ‖**v**‖₂, a unit vector in the same direction.

### Utility

**Equality with tolerance** — two vectors are "equal" if ‖**u - v**‖ < ε for some small epsilon. Essential for testing with floating-point values.

[x] **Stream output** — `operator<<` for printing vectors. Invaluable for debugging when a power flow iteration isn't converging.

[x] **Size and element access** — `size()`, `operator[]` (const and non-const).

### Future (not yet implemented)

**Matrix-vector product** — lives on the Matrix class, but Vector is the return type of `Ax`.

[x] **Iterators** — `begin()` and `end()` for range-based for loops over Vector elements.

## Matrix Class Functionality

### Storage and Access

**Construction** — default, from dimensions (rows × cols, zero-initialized), from dimensions with fill value, from `std::initializer_list<std::initializer_list<T>>` for literal matrix definitions in tests.

**Element access** — `operator()(i, j)` (const and non-const) using row-major indexing internally (`i * cols + j`). Prefer `operator()` over double-bracket `[][]` — it's cleaner and avoids exposing internal layout through proxy objects.

**Shape queries** — `rows()`, `cols()`, `size()` (total element count).

**Stream output** — `operator<<` for printing matrices. Invaluable for debugging when the Jacobian looks wrong and iterations diverge.

### Arithmetic

**Addition and subtraction** — element-wise, same dimensions required. Both mutating (`+=`, `-=`) and non-mutating (`+`, `-`). Same pattern as Vector: build binary operators on top of compound assignment.

**Scalar multiplication and division** — every element scaled by a scalar. Both mutating (`*=`, `/=`) and non-mutating (`*`, `/`). Scalar division shows up when normalizing or scaling matrix entries.

**Negation** — unary minus. Given matrix **A**, return **-A** where every element is negated.

### Products

**Matrix-vector multiplication** — `A * v` returning a `Vector<T>`. Each entry of the result is a dot product of a row of **A** with **v**. This is the core operation in Newton-Raphson: the Jacobian **J** multiplied by correction vector **Δx**.

**Matrix-matrix multiplication** — `A * B` returning a `Matrix<T>`. Row-column dot products. Less critical for basic load flow but essential for testing (e.g., verifying `A * A⁻¹ ≈ I`) and for composing transformations.

### Structure

**Transpose** — return **Aᵀ** where rows and columns are swapped. Shows up when assembling the Jacobian from sub-blocks and in various matrix identities used for verification.

**Identity matrix** — static factory `Matrix::identity(n)` returning the *n × n* identity. Used in testing (`A * I = A`), and occasionally in formulations.

### Row Operations

**Row swapping** — swap rows *i* and *j* in place. Required for partial pivoting during LU decomposition.

**Row scaling** — multiply row *i* by a scalar. Elementary operation underlying Gaussian elimination.

**Row addition** — add a scalar multiple of row *i* to row *j*. The workhorse of elimination: `R_j ← R_j + c · R_i`.

### LU Decomposition and Solve

**LU decomposition with partial pivoting** — factor **PA = LU** where **P** is a permutation matrix (stored as a pivot vector), **L** is lower triangular with ones on the diagonal, and **U** is upper triangular. Partial pivoting (swapping rows to put the largest magnitude element on the diagonal) is essential for numerical stability.

**Forward substitution** — solve **Ly = Pb** for **y**, working top-to-bottom. The *L* matrix has ones on the diagonal so no division by diagonal entries is needed.

**Back substitution** — solve **Ux = y** for **x**, working bottom-to-top. This produces the final solution vector.

**Solve interface** — public `solve(A, b)` returning a `Vector<T>`. Internally: factor **A**, permute **b**, forward substitute, back substitute. This is what Newton-Raphson calls each iteration to solve **J · Δx = -F(x)**.

### Utility

**Equality with tolerance** — two matrices are "equal" if the maximum element-wise difference is below ε, or equivalently if some norm of **(A - B)** < ε. Essential for floating-point testing.

**Iterators** — `begin()` and `end()` over the underlying flat storage for range-based for loops when you need to touch every element.

### Future (not yet needed)

**Determinant** — LU gives this nearly for free as the product of the diagonal of **U** (adjusted for pivot sign). Not called during load flow, but trivial to add once LU exists.

**Inverse** — compute **A⁻¹** by solving **AX = I** column-by-column. Almost never what you actually want — `solve(A, b)` is faster and more stable. Useful only for verification.

**Sub-matrix extraction / block assembly** — extract or insert rectangular blocks. Would matter for assembling the Jacobian from its four sub-blocks (J1, J2, J3, J4) in a full AC power flow, but can be done manually at first.

**Sparse storage** — real power systems have thousands of buses and very sparse Jacobians. A sparse matrix format (CSR/CSC) would be essential for performance at scale, but is premature for a learning project with small test cases.
