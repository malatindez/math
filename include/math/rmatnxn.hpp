#pragma once
#include "mat.hpp"
#pragma warning(push)
#pragma warning(disable : 4201)
/**
 * @file rmatnxn.hpp
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Specialized representation of matrices using reference semantics.
 * 
 * This header provides a unique matrix implementation, `rmat`, which utilizes 
 * reference semantics to efficiently work with subsets of larger matrices or 
 * to share matrix data without copying. Each `rmat` instance is defined by its 
 * dimensions (`a` and `b`) and the type of its elements (`T`), and can be 
 * constructed from existing `mat` or `rmat` objects if they fit certain size 
 * constraints.
 * 
 * The file also includes various operator overloads to make matrix arithmetic 
 * more intuitive and straightforward. Additionally, certain utility methods, 
 * such as `reset()`, are provided to simplify matrix manipulations.
 * 
 * Usage:
 * ```cpp
 * rmat<2, 3, float> matrixA;
 * rmat<3, 2, int> matrixB(matrixA);
 * ```
 * 
 * Note: Care should be taken when working with `rmat` instances to ensure 
 * that the underlying data they reference remains valid.
 * 
 * For implementation details, please refer to "rmatnxn.inl".
 */namespace mal_math {

    /**
     * @brief Represents a matrix of references, allowing efficient interactions 
     *        without actual copying.
     * 
     * @tparam a Number of rows in the matrix.
     * @tparam b Number of columns in the matrix.
     * @tparam T Primitive type of the matrix elements.
     */
    template <size_t a, size_t b, Primitive T>
    struct rmat {
        using type = T; //!< Alias for the data type of the matrix elements.

        static constexpr ivec2 size{ a, b }; //!< Defines the size of the matrix.

        /// Default constructor.
        constexpr rmat() {}

        /**
         * @brief Constructs a reference matrix from another matrix.
         * 
         * @tparam c Number of rows in the source matrix.
         * @tparam d Number of columns in the source matrix.
         * @tparam P Primitive type of the source matrix elements.
         * @param p Source matrix to be copied from.
         */
        template <size_t c, size_t d, Primitive P>
        constexpr rmat(mat<c, d, P>& p) requires(c >= a && d >= b);

        /**
         * @brief Constructs a reference matrix from another reference matrix.
         * 
         * @tparam c Number of rows in the source matrix.
         * @tparam d Number of columns in the source matrix.
         * @tparam P Primitive type of the source matrix elements.
         * @param p Source reference matrix to be copied from.
         */
        template <size_t c, size_t d, Primitive P>
        constexpr rmat(rmat<c, d, P>& p) requires(c >= a && d >= b);

        /// Assigns values from a matrix of the same size.
        template <typename U>
        constexpr rmat<a, b, T>& operator=(mat<a, b, U> const& mat);

        /// Assigns values from a reference matrix of the same size.
        template <typename U>
        constexpr rmat<a, b, T>& operator=(rmat<a, b, U> const& mat);

        /// Resets all elements to zero.
        constexpr void reset() noexcept;

        /// Indexing operator to access rows.
        [[nodiscard]] constexpr _detail::rvec<b, T>& operator[](size_t i);

        /// Const version of indexing operator to access rows.
        [[nodiscard]] constexpr _detail::rvec<b, T> const& operator[](size_t i) const;

        /// Unary plus operator, returns the matrix itself.
        [[nodiscard]] constexpr rmat<a, b, T> const& operator+() const noexcept;

        /// Unary minus operator, returns negated matrix.
        [[nodiscard]] constexpr mat<a, b, T> operator-() const noexcept;

        /// Adds another reference matrix of the same size to this matrix.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator+=(rmat<a, b, U> const& other);

        /// Subtracts another reference matrix of the same size from this matrix.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator-=(rmat<a, b, U> const& other);

        /// Matrix multiplication with another reference matrix.
        template <size_t c, Primitive U>
        constexpr rmat<a, c, T>& operator*=(rmat<b, c, U> const& other);

        /// Adds another matrix of the same size to this matrix.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator+=(mat<a, b, U> const& other);

        /// Subtracts another matrix of the same size from this matrix.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator-=(mat<a, b, U> const& other);

        /// Matrix multiplication with another matrix.
        template <size_t c, Primitive U>
        constexpr rmat<a, c, T>& operator*=(mat<b, c, U> const& other);

        /// Adds a scalar to all elements of this matrix.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator+=(U const value);

        /// Subtracts a scalar from all elements of this matrix.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator-=(U const value);

        /// Multiplies all elements of this matrix with a scalar.
        template <Primitive U>
        constexpr rmat<a, b, T>& operator*=(U const value);

        /// Union to represent matrix data in different formats.
        union {
            std::array<_detail::primitive_reference_wrapper<T>, size.x * size.y> arr; //!< Linear representation of the matrix.
            std::array<_detail::rvec<size.y, T>, size.x> data; //!< 2D representation of the matrix.
        };

        static_assert(sizeof(arr) == sizeof(data)); //!< Ensure both representations have the same size.
    };

} // namespace mal_math

#pragma warning(pop)
#include "rmatnxn.inl"