#pragma once
#include "mat.hpp"
/**
 * @file mat_math.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 *
 * @brief Defines various matrix mathematical operations.
 * 
 * This file contains the definition for mathematical operations that can be performed on matrices, 
 * such as multiplication, subtraction, transposition, determinant calculation, etc.
 * 
 * The operations also cover operations with vectors and primitive data types.
 */
namespace mal_math
{
    /** 
     * @brief Reads a matrix from an input stream.
     * @details Extracts values from the given input stream and fills the matrix accordingly.
     * @tparam U Any matrix type
     * @param is Input stream
     * @param matrix Matrix to be filled with values
     * @return Updated input stream
     */
    template <AnyMat U>
    constexpr std::istream &operator>>(std::istream &is, U &matrix);
    
    /** 
     * @brief Writes a matrix to an output stream.
     * @details Converts the matrix into a string representation and inserts it into the given output stream.
     * @tparam U Any matrix type
     * @param os Output stream
     * @param matrix Matrix to be written
     * @return Updated output stream
     */
    template <AnyMat U>
    constexpr std::ostream &operator<<(std::ostream &os, U const &matrix);

    /**
     * @brief Multiplies two matrices.
     * @details Computes the product of two matrices. Requires that the number of columns in the left-hand side matrix matches the number of rows in the right-hand side matrix.
     * @tparam U First matrix type
     * @tparam V Second matrix type
     * @param lhs Left-hand side matrix
     * @param rhs Right-hand side matrix
     * @return Product of the two matrices
     */
    template <AnyMat U, AnyMat V>
    [[nodiscard]] constexpr auto operator*(U const &lhs, V const &rhs) requires (U::size.x == V::size.y);
    
    /**
     * @brief Multiplies a vector by a matrix.
     * @details This function is a specialized implementation of vector-matrix multiplication. The result is a vector with the appropriate type and size.
     * @tparam V A vector type satisfying the AnyVec concept.
     * @tparam M A matrix type satisfying the AnyMat concept.
     * @param left The vector to be multiplied.
     * @param right The matrix to multiply the vector with.
     * @return A vector that is the result of the multiplication.
     */
    template <AnyVec V, AnyMat M>
    [[nodiscard]] constexpr auto operator*(V const &left, M const &right) requires (V::size == M::size.y);
    
    /**
     * @brief Multiplies a matrix by a vector.
     * @details This function multiplies a matrix with a vector, resulting in a vector of the appropriate type and size.
     * @tparam M A matrix type satisfying the AnyMat concept.
     * @tparam V A vector type satisfying the AnyVec concept.
     * @param left The matrix to be multiplied.
     * @param right The vector to multiply the matrix with.
     * @return A vector that is the result of the multiplication.
     */
    template <AnyMat M, AnyVec V>
    [[nodiscard]] constexpr auto operator*(M const &left, V const &right) requires (M::size.x == V::size);
    
    /**
     * @brief Multiplies a matrix by a primitive.
     * @details This function performs scalar multiplication on a matrix. It multiplies each element of the matrix by the given primitive.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A primitive type.
     * @param left The matrix to be multiplied.
     * @param right The primitive value to multiply the matrix with.
     * @return A matrix where each element is multiplied by the primitive value.
     */
    template <AnyMat T, Primitive U>
    [[nodiscard]] constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> operator*(T const &left, U const right);
    
    /**
     * @brief Multiplies a matrix by a primitive.
     * @details Performs scalar multiplication on a matrix by multiplying each element with a primitive value.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A primitive type.
     * @param left The primitive value.
     * @param right The matrix.
     * @return A matrix where each element is multiplied by the primitive value.
     */
    template <AnyMat T, Primitive U>
    [[nodiscard]] constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> operator*(U const left, T const &right);
    
    /**
     * @brief Subtracts a matrix from a primitive.
     * @details Subtracts each element of the matrix from a given primitive.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A primitive type.
     * @param left The matrix.
     * @param right The primitive value.
     * @return A matrix where each element is subtracted from the primitive value.
     */
    template <AnyMat T, Primitive U>
    [[nodiscard]] constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> operator-(T const &left, U const right);
    
    /**
     * @brief Adds a matrix to a primitive.
     * @details Adds a primitive to each element of the matrix.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A primitive type.
     * @param left The primitive value.
     * @param right The matrix.
     * @return A matrix where each element is added to the primitive value.
     */
    template <AnyMat T, Primitive U>
    [[nodiscard]] constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> operator+(U const left, T const &right);
    
    /**
     * @brief Subtracts two matrices.
     * @details Performs element-wise subtraction of two matrices.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A matrix type satisfying the AnyMat concept.
     * @param left The first matrix.
     * @param right The second matrix to be subtracted from the first.
     * @return A matrix where each element is the result of the subtraction of corresponding elements.
     */
    template <AnyMat T, AnyMat U>
    [[nodiscard]] constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> operator-(T const left, U const &right) requires(T::size.x == U::size.x && T::size.y == U::size.y);
    
    /**
     * @brief Adds two matrices.
     * @details Performs element-wise addition of two matrices.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A matrix type satisfying the AnyMat concept.
     * @param left The first matrix.
     * @param right The second matrix to be added to the first.
     * @return A matrix where each element is the result of the addition of corresponding elements.
     */
    template <AnyMat T, AnyMat U>
    [[nodiscard]] constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> operator+(T const &left, U const &right) requires(T::size.x == U::size.x && T::size.y == U::size.y);

    /**
     * @brief Transposes a matrix.
     * @details Swaps rows with columns in a matrix.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param matrix The matrix to be transposed.
     * @return A new matrix that is the transpose of the given matrix.
     */
    template <AnyMat T>
    constexpr mat<T::size.y, T::size.x, std::remove_const_t<typename T::type>> transpose(T const &matrix);
    
    /**
     * @brief Transposes a matrix and returns a reference to it.
     * @details Swaps rows with columns in a matrix, returning a reference.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param matrix The matrix to be transposed.
     * @return A reference to the transposed matrix.
     */
    template <AnyMat T>
    constexpr rmat<T::size.y, T::size.x, typename T::type> rtranspose(T &matrix);
    
    /**
     * @brief Transposes a constant matrix and returns a constant reference to it.
     * @details Swaps rows with columns in a constant matrix, returning a constant reference.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param matrix The matrix to be transposed.
     * @return A constant reference to the transposed matrix.
     */
    template <AnyMat T>
    constexpr rmat<T::size.y, T::size.x, const typename T::type> rctranspose(T const &matrix);

    /**
     * @brief Calculates the determinant of a square matrix.
     * @details Computes the determinant using an appropriate method based on the matrix size.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param matrix The matrix whose determinant is to be computed.
     * @return The determinant of the matrix.
     */
    template <AnyMat T>
    constexpr typename T::type det(T const &matrix) requires(T::size.x == T::size.y);
    
    /**
     * @brief Calculates the determinant of a square matrix.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param matrix The matrix for which to compute the determinant.
     * @return The determinant of the matrix.
     */
    template <AnyMat T>
    constexpr typename T::type determinant(T const &matrix) requires(T::size.x == T::size.y);

    /**
     * @brief Computes the adjoint (or adjugate) of a square matrix.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param m The input matrix.
     * @return The adjoint of the input matrix.
     */
    template <AnyMat T>
    constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> adj(T const &m) requires(T::size.x == T::size.y);
    /**
     * @brief Alias for the adj() function to compute the adjugate of a matrix.
     */
    template <AnyMat T>
    constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> adjugate(T const &m) requires(T::size.x == T::size.y);

    /**
     * @brief Calculates the inverse of a square matrix.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @param matrix The matrix for which to compute the inverse.
     * @return The inverse of the matrix.
     */
    template <AnyMat T>
    constexpr mat<T::size.x, T::size.y, std::remove_const_t<typename T::type>> inverse(T const &matrix) requires(T::size.x == T::size.y);

    /**
     * @brief Translates a matrix by a given vector.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam V A vector type satisfying the AnyVec concept.
     * @param matrix The matrix to be translated.
     * @param vec The translation vector.
     * @return A matrix that has been translated by the given vector.
     */
    template <AnyMat T, AnyVec V>
    constexpr mat<4, 4, std::remove_const_t<typename T::type>> translate(T const &matrix, V const &vec) requires(T::size.x == T::size.y && T::size.x == 4 && V::size == 3);

    /**
     * @brief Rotates a matrix by a given angle around a given axis.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam U A primitive type representing the angle.
     * @tparam V A vector type representing the rotation axis.
     * @param matrix The matrix to be rotated.
     * @param angle The rotation angle.
     * @param axis The rotation axis.
     * @return A matrix that has been rotated by the given angle around the given axis.
     */
    template <AnyMat T, Primitive U, AnyVec V>
    constexpr mat<4, 4, std::remove_const_t<typename T::type>> rotate(T const &matrix, U angle, V const &axis) requires(T::size.x == T::size.y && T::size.x == 4 && V::size == 3);

    /**
     * @brief Scales a matrix by a given vector.
     * @tparam T A matrix type satisfying the AnyMat concept.
     * @tparam V A vector type representing the scaling factors.
     * @param matrix The matrix to be scaled.
     * @param scale The scaling vector.
     * @return A matrix that has been scaled by the given vector.
     */
    template <AnyMat T, AnyVec V>
    constexpr mat<4, 4, std::remove_const_t<typename T::type>> scale(T const &matrix, V const &scale) requires(T::size.x == T::size.y && T::size.x == 4 && V::size == 3);

    /**
     * @brief Generates a look-at matrix for camera positioning.
     * @tparam Position A vector type.
     * @param eye The position of the observer.
     * @param center The position where the observer is looking at.
     * @param up The up direction for the observer.
     * @return A look-at matrix.
     */
    template <AnyVec Position>
    constexpr mat<4, 4, std::remove_const_t<typename Position::type>> look_at(Position const &eye, Position const &center, Position const &up) requires(Position::size == 3);
    /**
     * @brief Generates a perspective projection matrix.
     * @tparam T A primitive type for the function parameters.
     * @param fov_y The vertical field of view in radians.
     * @param aspect_ratio The aspect ratio of the viewport.
     * @param z_near The near clipping plane distance.
     * @param z_far The far clipping plane distance.
     * @return A perspective projection matrix.
     */
    template <Primitive T>
    constexpr mat<4, 4, T> perspective(T fov_y, T aspect_ratio, T z_near, T z_far);

    /**
     * @brief Generates an orthographic projection matrix.
     * @tparam T A primitive type for the function parameters.
     * @param left The left clipping plane distance.
     * @param right The right clipping plane distance.
     * @param bottom The bottom clipping plane distance.
     * @param top The top clipping plane distance.
     * @param zNear The near clipping plane distance.
     * @param zFar The far clipping plane distance.
     * @return An orthographic projection matrix.
     */
    template <Primitive T>
    constexpr mat<4, 4, T> ortho(T left, T right, T bottom, T top, T zNear, T zFar);

    /**
     * @brief Inverts an orthonormal matrix in-place and stores the result in a destination matrix.
     * @tparam T A primitive type.
     * @param src The source orthonormal matrix.
     * @param dst The destination matrix where the result will be stored.
     */
    template <Primitive T>
    constexpr void invert_orthonormal(mat<4, 4, T> const &src, mat<4, 4, T> &dst);
    
    /**
     * @brief Inverts an orthogonal matrix in-place and stores the result in a destination matrix.
     * @tparam T A primitive type.
     * @param src The source orthogonal matrix.
     * @param dst The destination matrix where the result will be stored.
     */
    template <Primitive T>
    constexpr void invert_orthogonal(mat<4, 4, T> const &src, mat<4, 4, T> &dst);
    
    /**
     * @brief Returns an inverted orthonormal matrix.
     * @tparam T A primitive type.
     * @param src The source orthonormal matrix.
     * @return The inverted orthonormal matrix.
     */
    template <Primitive T>
    constexpr mat<4, 4, T> invert_orthonormal(mat<4, 4, T> const &src);
    
    /**
     * @brief Returns an inverted orthogonal matrix.
     * @tparam T A primitive type.
     * @param src The source orthogonal matrix.
     * @return The inverted orthogonal matrix.
     */
    template <Primitive T>
    constexpr mat<4, 4, T> invert_orthogonal(mat<4, 4, T> const &src);
} // namespace mal_math
#include "mat_math.inl"