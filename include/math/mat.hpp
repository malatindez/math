#pragma once
#include "vec_math.hpp"
#include "matnxn.hpp"
#include "rmatnxn.hpp"
/**
 * @file mat.hpp
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Provides matrix definitions tailored for various sizes and primitive types.
 * 
 * This header introduces a collection of matrix type definitions varying by dimensions 
 * and primitive data types. The base template `mat` serves as the foundation for these 
 * types, resulting in specific aliases such as `mat2x3` for a 2x3 float matrix or `imat4` 
 * for a 4x4 integer matrix.
 * 
 * In addition, a specialized matrix type `rmat`, which emphasizes reference semantics, is 
 * also defined. This type, short for reference matrix, enables efficient interactions with 
 * matrix subsets or shared matrix data without actual copying. Aliases for `rmat` tailored 
 * to specific dimensions and types are also provided.
 * 
 * Usage:
 * ```cpp
 * mat2x3 a;       // Represents a 2x3 matrix of floats
 * imat4 b;        // Denotes a 4x4 matrix of integers
 * drmat2x2 c;     // Describes a 2x2 reference matrix of doubles
 * ```
 * 
 * For intricate matrix operations and manipulations, please refer to "mat_math.hpp".
 */


/**
 * @namespace mal_math
 * @brief A namespace dedicated for matrix mathematical operations and types.
 */
namespace mal_math {

    /// @typedef mat4
    /// @brief 4x4 matrix with float elements.
    using mat4 = mat<4, 4, float>;

    /// @typedef dmat4
    /// @brief 4x4 matrix with double elements.
    using dmat4 = mat<4, 4, double>;

    /// @typedef imat4
    /// @brief 4x4 matrix with integer elements.
    using imat4 = mat<4, 4, int>;

    /// @typedef mat4x4
    /// @brief 4x4 matrix with float elements.
    using mat4x4 = mat<4, 4, float>;

    /// @typedef dmat4x4
    /// @brief 4x4 matrix with double elements.
    using dmat4x4 = mat<4, 4, double>;

    /// @typedef imat4x4
    /// @brief 4x4 matrix with integer elements.
    using imat4x4 = mat<4, 4, int>;

    /// @typedef mat3
    /// @brief 3x3 matrix with float elements.
    using mat3 = mat<3, 3, float>;

    /// @typedef dmat3
    /// @brief 3x3 matrix with double elements.
    using dmat3 = mat<3, 3, double>;

    /// @typedef imat3
    /// @brief 3x3 matrix with integer elements.
    using imat3 = mat<3, 3, int>;

    /// @typedef mat3x3
    /// @brief 3x3 matrix with float elements.
    using mat3x3 = mat<3, 3, float>;

    /// @typedef dmat3x3
    /// @brief 3x3 matrix with double elements.
    using dmat3x3 = mat<3, 3, double>;

    /// @typedef imat3x3
    /// @brief 3x3 matrix with integer elements.
    using imat3x3 = mat<3, 3, int>;

    /// @typedef mat2
    /// @brief 2x2 matrix with float elements.
    using mat2 = mat<2, 2, float>;

    /// @typedef dmat2
    /// @brief 2x2 matrix with double elements.
    using dmat2 = mat<2, 2, double>;

    /// @typedef imat2
    /// @brief 2x2 matrix with integer elements.
    using imat2 = mat<2, 2, int>;

    /// @typedef mat2x2
    /// @brief 2x2 matrix with float elements.
    using mat2x2 = mat<2, 2, float>;

    /// @typedef dmat2x2
    /// @brief 2x2 matrix with double elements.
    using dmat2x2 = mat<2, 2, double>;

    /// @typedef imat2x2
    /// @brief 2x2 matrix with integer elements.
    using imat2x2 = mat<2, 2, int>;

    /// @typedef mat2x3
    /// @brief 2x3 matrix with float elements.
    using mat2x3 = mat<2, 3, float>;

    /// @typedef dmat2x3
    /// @brief 2x3 matrix with double elements.
    using dmat2x3 = mat<2, 3, double>;

    /// @typedef imat2x3
    /// @brief 2x3 matrix with integer elements.
    using imat2x3 = mat<2, 3, int>;

    /// @typedef mat3x2
    /// @brief 3x2 matrix with float elements.
    using mat3x2 = mat<3, 2, float>;

    /// @typedef dmat3x2
    /// @brief 3x2 matrix with double elements.
    using dmat3x2 = mat<3, 2, double>;

    /// @typedef imat3x2
    /// @brief 3x2 matrix with integer elements.
    using imat3x2 = mat<3, 2, int>;

    /// @typedef mat2x4
    /// @brief 2x4 matrix with float elements.
    using mat2x4 = mat<2, 4, float>;

    /// @typedef dmat2x4
    /// @brief 2x4 matrix with double elements.
    using dmat2x4 = mat<2, 4, double>;

    /// @typedef imat2x4
    /// @brief 2x4 matrix with integer elements.
    using imat2x4 = mat<2, 4, int>;

    /// @typedef mat4x2
    /// @brief 4x2 matrix with float elements.
    using mat4x2 = mat<4, 2, float>;

    /// @typedef dmat4x2
    /// @brief 4x2 matrix with double elements.
    using dmat4x2 = mat<4, 2, double>;

    /// @typedef imat4x2
    /// @brief 4x2 matrix with integer elements.
    using imat4x2 = mat<4, 2, int>;

    /// @typedef mat3x4
    /// @brief 3x4 matrix with float elements.
    using mat3x4 = mat<3, 4, float>;

    /// @typedef dmat3x4
    /// @brief 3x4 matrix with double elements.
    using dmat3x4 = mat<3, 4, double>;

    /// @typedef imat3x4
    /// @brief 3x4 matrix with integer elements.
    using imat3x4 = mat<3, 4, int>;

    /// @typedef mat4x3
    /// @brief 4x3 matrix with float elements.
    using mat4x3 = mat<4, 3, float>;

    /// @typedef dmat4x3
    /// @brief 4x3 matrix with double elements.
    using dmat4x3 = mat<4, 3, double>;

    /// @typedef imat4x3
    /// @brief 4x3 matrix with integer elements.
    using imat4x3 = mat<4, 3, int>;

    /// @typedef rmat4
    /// @brief 4x4 reference matrix to float elements.
    using rmat4 = rmat<4, 4, float>;

    /// @typedef drmat4
    /// @brief 4x4 reference matrix to double elements.
    using drmat4 = rmat<4, 4, double>;

    /// @typedef irmat4
    /// @brief 4x4 reference matrix to integer elements.
    using irmat4 = rmat<4, 4, int>;

    /// @typedef rmat4x4
    /// @brief 4x4 reference matrix to float elements.
    using rmat4x4 = rmat<4, 4, float>;

    /// @typedef drmat4x4
    /// @brief 4x4 reference matrix to double elements.
    using drmat4x4 = rmat<4, 4, double>;

    /// @typedef irmat4x4
    /// @brief 4x4 reference matrix to integer elements.
    using irmat4x4 = rmat<4, 4, int>;

    /// @typedef rmat3
    /// @brief 3x3 reference matrix to float elements.
    using rmat3 = rmat<3, 3, float>;

    /// @typedef drmat3
    /// @brief 3x3 reference matrix to double elements.
    using drmat3 = rmat<3, 3, double>;

    /// @typedef irmat3
    /// @brief 3x3 reference matrix to integer elements.
    using irmat3 = rmat<3, 3, int>;

    /// @typedef rmat3x3
    /// @brief 3x3 reference matrix to float elements.
    using rmat3x3 = rmat<3, 3, float>;

    /// @typedef drmat3x3
    /// @brief 3x3 reference matrix to double elements.
    using drmat3x3 = rmat<3, 3, double>;

    /// @typedef irmat3x3
    /// @brief 3x3 reference matrix to integer elements.
    using irmat3x3 = rmat<3, 3, int>;

    /// @typedef rmat2
    /// @brief 2x2 reference matrix to float elements.
    using rmat2 = rmat<2, 2, float>;

    /// @typedef drmat2
    /// @brief 2x2 reference matrix to double elements.
    using drmat2 = rmat<2, 2, double>;

    /// @typedef irmat2
    /// @brief 2x2 reference matrix to integer elements.
    using irmat2 = rmat<2, 2, int>;

    /// @typedef rmat2x2
    /// @brief 2x2 reference matrix to float elements.
    using rmat2x2 = rmat<2, 2, float>;

    /// @typedef drmat2x2
    /// @brief 2x2 reference matrix to double elements.
    using drmat2x2 = rmat<2, 2, double>;

    /// @typedef irmat2x2
    /// @brief 2x2 reference matrix to integer elements.
    using irmat2x2 = rmat<2, 2, int>;

    /// @typedef rmat2x3
    /// @brief 2x3 reference matrix to float elements.
    using rmat2x3 = rmat<2, 3, float>;

    /// @typedef drmat2x3
    /// @brief 2x3 reference matrix to double elements.
    using drmat2x3 = rmat<2, 3, double>;

    /// @typedef irmat2x3
    /// @brief 2x3 reference matrix to integer elements.
    using irmat2x3 = rmat<2, 3, int>;

    /// @typedef rmat3x2
    /// @brief 3x2 reference matrix to float elements.
    using rmat3x2 = rmat<3, 2, float>;

    /// @typedef drmat3x2
    /// @brief 3x2 reference matrix to double elements.
    using drmat3x2 = rmat<3, 2, double>;

    /// @typedef irmat3x2
    /// @brief 3x2 reference matrix to integer elements.
    using irmat3x2 = rmat<3, 2, int>;

    /// @typedef rmat2x4
    /// @brief 2x4 reference matrix to float elements.
    using rmat2x4 = rmat<2, 4, float>;

    /// @typedef drmat2x4
    /// @brief 2x4 reference matrix to double elements.
    using drmat2x4 = rmat<2, 4, double>;

    /// @typedef irmat2x4
    /// @brief 2x4 reference matrix to integer elements.
    using irmat2x4 = rmat<2, 4, int>;

    /// @typedef rmat4x2
    /// @brief 4x2 reference matrix to float elements.
    using rmat4x2 = rmat<4, 2, float>;

    /// @typedef drmat4x2
    /// @brief 4x2 reference matrix to double elements.
    using drmat4x2 = rmat<4, 2, double>;

    /// @typedef irmat4x2
    /// @brief 4x2 reference matrix to integer elements.
    using irmat4x2 = rmat<4, 2, int>;

    /// @typedef rmat3x4
    /// @brief 3x4 reference matrix to float elements.
    using rmat3x4 = rmat<3, 4, float>;

    /// @typedef drmat3x4
    /// @brief 3x4 reference matrix to double elements.
    using drmat3x4 = rmat<3, 4, double>;

    /// @typedef irmat3x4
    /// @brief 3x4 reference matrix to integer elements.
    using irmat3x4 = rmat<3, 4, int>;

    /// @typedef rmat4x3
    /// @brief 4x3 reference matrix to float elements.
    using rmat4x3 = rmat<4, 3, float>;

    /// @typedef drmat4x3
    /// @brief 4x3 reference matrix to double elements.
    using drmat4x3 = rmat<4, 3, double>;

    /// @typedef irmat4x3
    /// @brief 4x3 reference matrix to integer elements.
    using irmat4x3 = rmat<4, 3, int>;
} // namespace mal_math

/// @file
/// @brief Includes math-related matrix functions.
#include "mat_math.hpp"
