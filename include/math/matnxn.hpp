#pragma once
#include "mat.hpp"
#pragma warning(push)
#pragma warning(disable : 4201)
/**
 * @file matnxn.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Provides the definition of a generic NxN matrix for mathematical operations.
 * 
 * This header file contains the definition of a templated NxN matrix structure, 
 * along with the necessary constructors, operators, and utility functions for various 
 * mathematical operations. The matrix can be used for linear transformations, 
 * matrix multiplication, and other similar operations. The matrix also allows for 
 * type flexibility and can be initialized with various data types.
 * 
 * @note Warning manipulations are done to prevent unwanted compiler warnings.
 * 
 * @warning This header contains some advanced C++ features, make sure to understand 
 * these features before making modifications.
 * 
 * @namespace mal_math The main namespace for the mathematical utilities.
 */

namespace mal_math
{
    /**
     * @class mat
     * @brief Represents a matrix of dimensions a x b.
     *
     * @tparam a Number of rows of the matrix.
     * @tparam b Number of columns of the matrix.
     * @tparam T Data type of the matrix elements (must be a primitive type).
     */
    template <size_t a, size_t b, Primitive T>
    struct mat
    {
        /// @brief Alias for the primitive data type used in the matrix.
        using type = T;
        /// @brief Represents the dimensions of the matrix.
        static constexpr vec<2, size_t> size{ a, b };
        /**
         * @brief Returns the identity matrix of size a x b.
         *
         * @return mat<a, b, T> Identity matrix.
         */
        static constexpr mat<a, b, T> identity() noexcept
        {
            mat<a, b, T> result;
            for (size_t i = 0; i < a; i++)
            {
                for (size_t j = 0; j < b; j++)
                {
                    result.data[i][j] = i == j ? static_cast<T>(1) : static_cast<T>(0);
                }
            }
            return result;
        }


        /// @brief Default constructor.
        constexpr mat() = default;
        
        /**
         * @brief Constructor that initializes a square matrix with a single value.
         *
         * @tparam P Primitive type for the initialization value.
         * @param p The value to initialize the matrix with.
         */
        template <Primitive P>
        explicit constexpr mat(P p) requires(a == b);
        /**
         * @brief Constructor that initializes the matrix from another matrix.
         * @tparam c Number of rows of the source matrix.
         * @tparam d Number of columns of the source matrix.
         * @tparam P Primitive type of the source matrix.
         * @param p Source matrix to copy from.
         */
        template <size_t c, size_t d, Primitive P>
        explicit constexpr mat(mat<c, d, P> p) requires(a >= c && b >= d);
        /**
         * @brief Constructor that initializes the matrix from another matrix.
         * @tparam c Number of rows of the source matrix.
         * @tparam d Number of columns of the source matrix.
         * @tparam P Primitive type of the source matrix.
         * @param p Source matrix to copy from.
         */
        template <size_t c, size_t d, Primitive P>
        explicit constexpr mat(rmat<c, d, P> p) requires(a >= c && b >= d);
        /**
         * @brief Constructor that initializes the matrix from another matrix with the same dimensions.
         * 
         * @param p Source matrix to copy from.
         */
        template <Primitive P>
        explicit constexpr mat(mat<a, b, P> p);
        /**
         * @brief Constructor that initializes the matrix from another matrix with the same dimensions.
         * 
         * @param p Source matrix to copy from.
         */
        template <Primitive P>
        explicit constexpr mat(rmat<a, b, P> p);
        /**
         * @brief Constructor that initializes the matrix from any data (such as floats, vectors, integers etc.).
         * It doesn't care if primitive type is the same, it can eat basically anything. For example:
         * @code {.cpp}
         * mat3x3<float> m(1, 2, 3, 4, 5, 6, 7, 8, 9);
         * mat3x3<float> m(1, 2, 3, 4, 5, 6, vec3{7, 8, 9});
         * mat3 m2(vec3{1, vec2{2, 3}}, vec<4, int>{4,5,6,7], uivec2{8, 9});
         * @endcode
         * 
         */
        template <typename... U>
        explicit constexpr mat(U... data);
        
        /**
         * @brief Resets the matrix to have all zero values.
         */
        constexpr void reset() noexcept;

        /**
         * @brief Accesses a row of the matrix.
         * @param i Index of the row.
         * @return A reference to the row at the given index.
         */
        [[nodiscard]] constexpr vec<b, T> &operator[](size_t i);
        /**
         * @brief Accesses a row of the matrix (const version).
         * @param i Index of the row.
         * @return A const reference to the row at the given index.
         */
        [[nodiscard]] constexpr vec<b, T> const &operator[](size_t i) const;
        /**
         * @brief Unary plus operator.
         *
         * @return const mat<a, b, T>& Returns a reference to the current matrix without any changes.
         */
        [[nodiscard]] constexpr mat<a, b, T> const &operator+() const noexcept;
        /**
         * @brief Unary minus operator.
         *
         * @return mat<a, b, T> Returns a new matrix with all elements negated.
         */
        [[nodiscard]] constexpr mat<a, b, T> operator-() const noexcept;

        /**
         * @brief Adds another matrix to the current matrix.
         *
         * @tparam U Type of the elements in the other matrix.
         * @param other Matrix to add to the current matrix.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator+=(mat<a, b, U> const &other);
        /**
         * @brief Subtracts another matrix from the current matrix.
         *
         * @tparam U Type of the elements in the other matrix.
         * @param other Matrix to subtract from the current matrix.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator-=(mat<a, b, U> const &other);
        /**
         * @brief Multiplies the current matrix with another matrix.
         *
         * @tparam c Number of columns in the resulting matrix.
         * @tparam U Type of the elements in the other matrix.
         * @param other Matrix to multiply with the current matrix.
         * @return mat<a, c, T>& Returns a reference to the modified current matrix.
         */
        template <size_t c, Primitive U>
        constexpr mat<a, c, T> &operator*=(mat<b, c, U> const &other);

        /**
         * @brief Adds another row-major matrix to the current matrix.
         *
         * @tparam U Type of the elements in the other row-major matrix.
         * @param other Row-major matrix to add to the current matrix.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator+=(rmat<a, b, U> const &other);
        /**
         * @brief Subtracts another row-major matrix from the current matrix.
         *
         * @tparam U Type of the elements in the other row-major matrix.
         * @param other Row-major matrix to subtract from the current matrix.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator-=(rmat<a, b, U> const &other);
        /**
         * @brief Multiplies the current matrix with another row-major matrix.
         *
         * @tparam c Number of columns in the resulting matrix.
         * @tparam U Type of the elements in the other row-major matrix.
         * @param other Row-major matrix to multiply with the current matrix.
         * @return mat<a, c, T>& Returns a reference to the modified current matrix.
         */
        template <size_t c, Primitive U>
        constexpr mat<a, c, T> &operator*=(rmat<b, c, U> const &other);

        /**
         * @brief Adds a scalar value to each element of the current matrix.
         *
         * @tparam U Type of the scalar value.
         * @param value Scalar value to add to each element.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator+=(U const value);
        /**
         * @brief Subtracts a scalar value from each element of the current matrix.
         *
         * @tparam U Type of the scalar value.
         * @param value Scalar value to subtract from each element.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator-=(U const value);
        /**
         * @brief Multiplies each element of the current matrix by a scalar value.
         *
         * @tparam U Type of the scalar value.
         * @param value Scalar value to multiply each element with.
         * @return mat<a, b, T>& Returns a reference to the modified current matrix.
         */
        template <Primitive U>
        constexpr mat<a, b, T> &operator*=(U const value);

        /**
         * @brief Converts the matrix to an rmat type.
         *
         * @tparam c Number of rows for the rmat (default is a).
         * @tparam d Number of columns for the rmat (default is b).
         * @return rmat<c, d, T> The matrix in rmat form.
         */
        template <size_t c = a, size_t d = b>
        constexpr rmat<c, d, T> as_rmat() noexcept { return rmat<c, d, T>{*this}; }

        /// @brief Union containing two ways to represent matrix data.
        union
        {
            std::array<T, size.x *size.y> arr; ///< Linear array representation of matrix data.
            std::array<vec<size.y, T>, size.x> data; ///< 2D array (rows x columns) representation of matrix data.
        };
        static_assert(sizeof(arr) == sizeof(data));

    private:
        /**
         * @brief Determines the size of a parameter pack for primitive types.
         * 
         * @return size_t Always returns 1 for primitive types.
         */
        template <Primitive _>
        static constexpr size_t get_parameter_pack_size();
        /**
         * @brief Determines the size of a parameter pack for vector types.
         * 
         * @return size_t Returns the size attribute of the vector type.
         */
        template <class V>
        static constexpr size_t get_parameter_pack_size();
        /**
         * @brief Determines the size of a parameter pack for a mixed set of types.
         * 
         * @return size_t Returns the cumulative size of the parameter pack types.
         */
        template <typename A, typename B, typename... C>
        static constexpr size_t get_parameter_pack_size();

        /**
         * @brief Unpacks a single primitive value into the matrix data.
         * 
         * @param offset The position to start unpacking in the matrix data.
         * @param u The primitive value to unpack.
         */
        template <Primitive U>
        constexpr void unpack_data(size_t offset, U u);
        /**
         * @brief Unpacks a vector into the matrix data.
         * 
         * @param offset The position to start unpacking in the matrix data.
         * @param vec The vector to unpack.
         */
        template <class V>
        constexpr void unpack_data(size_t offset, V vec);
        /**
         * @brief Recursively unpacks multiple values into the matrix data.
         * 
         * @param offset The position to start unpacking in the matrix data.
         * @param first The first value to unpack.
         * @param second The second value to unpack.
         * @param rest The remaining values to unpack.
         */
        template <typename A, typename B, typename... C>
        constexpr void unpack_data(size_t offset, A, B, C...);
    };
} // namespace mal_math
#pragma warning(pop)
#include "matnxn.inl"