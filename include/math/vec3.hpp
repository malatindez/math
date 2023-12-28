#pragma once

#include "math-common.hpp"
/**
 * @file vec3.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Header file for the 3D vector definition.
 */

#pragma warning(push)
#pragma warning(disable : 4201)
namespace mal_math
{
    /**
     * @brief Represents a 3D vector of a given primitive type.
     * 
     * @tparam T The primitive type of the vector.
     */
    template <Primitive T>
    struct vec<3, T>
    {
        static_assert(!std::is_const_v<T>);
        /// Type of the vector elements.
        using type = T;
        /// Number of elements in the vector.
        static constexpr size_t size = 3;
        /// Default constructor.
        constexpr vec() = default;
         /**
         * @brief Constructor initializing all elements to the given value.
         * 
         * @tparam U Type of the value.
         * @param value The value to initialize all elements with.
         */
        template <Primitive U>
        constexpr vec(U value);
        /**
         * @brief Constructor for initializing the vector with three values.
         * 
         * @tparam A Type of the first value.
         * @tparam B Type of the second value.
         * @tparam C Type of the third value.
         * @param a First value.
         * @param b Second value.
         * @param c Third value.
         */
        template <Primitive A, Primitive B, Primitive C>
        constexpr vec(A a, B b, C c);
        /**
         * @brief Variadic constructor.
         * 
         * @tparam U Types of the values.
         * @param data Values to initialize the vector with.
         */
        template <typename... U>
        constexpr vec(U... data);
        /// Constructor from std::array.
        constexpr vec(std::array<T, size> const &arr) : data{ arr } {}
        /// Move constructor from std::array.
        constexpr vec(std::array<T, size> &&arr) : data{ std::move(arr) } {}
        /// Returns a zero vector.
        constexpr static vec<3, T> zero() noexcept { return vec<3, T>(0); }
        /// Resets the vector to the zero vector.
        constexpr void reset() noexcept;

        /// Overloaded assignment operator.
        template <typename U>
        constexpr vec<size, T> &operator=(_detail::rvec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        /// Overloaded assignment operator for another vec object.
        template <typename U>
        constexpr vec<size, T> &operator=(vec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }

        /// Overloaded unary plus operator.
        [[nodiscard]] constexpr vec<3, T> const &operator+() const noexcept;
        /// Overloaded unary minus operator.
        [[nodiscard]] constexpr vec<3, T> operator-() const noexcept;

        template <Primitive U>
        constexpr vec<3, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<3, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr vec<3, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<3, T> &operator%=(U const &other) noexcept requires(size == U::size);

        /// Overloaded subscript operator for non-const rvec.
        [[nodiscard]] constexpr T &operator[](size_t i);
        /// Overloaded subscript operator for const rvec.
        [[nodiscard]] constexpr T const &operator[](size_t i) const;
        /// Union allowing multiple ways to access the vector elements.
        union
        {
            struct
            {
                union
                {
                    T x, r, s;
                };
                union
                {
                    T y, g, t;
                };
                union
                {
                    T z, b, p;
                };
            };
            std::array<T, 3> data;
            vec<2, T> xy;
            struct
            {
                T x_anonymous_padding_;
                vec<2, T> yz;
            };
        };
        static_assert(sizeof(data) == 3 * sizeof(T));

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
         * @brief Unpacks a single primitive value into the vector data.
         * 
         * @param offset The position to start unpacking in the vector data.
         * @param u The primitive value to unpack.
         */
        template <Primitive U>
        constexpr void unpack_data(size_t offset, U u);
        /**
         * @brief Unpacks a vector into the matrix data.
         * 
         * @param offset The position to start unpacking in the vector data.
         * @param vec The vector to unpack.
         */
        template <class V>
        constexpr void unpack_data(size_t offset, V vec);
        /**
         * @brief Recursively unpacks multiple values into the vector data.
         * 
         * @param offset The position to start unpacking in the vector data.
         * @param first The first value to unpack.
         * @param second The second value to unpack.
         * @param rest The remaining values to unpack.
         */
        template <typename A, typename B, typename... C>
        constexpr void unpack_data(size_t offset, A a, B b, C... c);
    };

    /**
     * @brief Computes the cross product of two 3D vectors.
     * 
     * @tparam T Type of the first vector.
     * @tparam U Type of the second vector.
     * @param left First vector.
     * @param right Second vector.
     * @return Cross product of the given vectors.
     */
    template <Primitive T, Primitive U>
    constexpr vec<3, T> cross(vec<3, T> const &left, vec<3, U> const &right);
}; // namespace mal_math

#pragma warning(pop)
#include "vec3.inl"