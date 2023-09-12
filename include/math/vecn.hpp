#pragma once

#include "vec.hpp"
/**
 * @file vecn.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Contains the definition of the generic vec<L, T> structure.
 */
namespace mal_math
{
    /**
     * @brief Represents a generic vector of a given primitive type.
     * 
     * @tparam L Length of the vector.
     * @tparam T The primitive type of the vector.
     */
    template <size_t L, Primitive T>
    struct vec
    {
        static_assert(!std::is_const_v<T>);
        /// Type of the vector elements.
        using type = T;
        /// Number of elements in the vector.
        static constexpr size_t size = L;
        /// Default constructor.
        constexpr vec() = default;
        /**
         * @brief Constructor initializing all elements to the given value.
         * 
         * @tparam U Type of the value.
         * @param value The value to initialize all elements with.
         */
        template <Primitive U>
        explicit constexpr vec(U value);
        /**
         * @brief Variadic constructor.
         * 
         * @tparam U Types of the values.
         * @param data Values to initialize the vector with.
         */
        template <typename... U>
        explicit constexpr vec(U... data);

        /**
         * @brief Constructor from std::array.
         * 
         * @param arr Array from which to initialize the vector.
         */
        explicit constexpr vec(std::array<T, size> const &arr) : data{ arr } {}
        /**
         * @brief Move constructor from std::array.
         * 
         * @param arr Array from which to move-initialize the vector.
         */
        explicit constexpr vec(std::array<T, size> &&arr) : data{ std::move(arr) } {}

        /// Resets the vector to the zero vector.
        constexpr void reset() noexcept;

        /// Overloaded assignment operator.
        template <typename U>
        constexpr vec<size, T> &operator=(vec<size, U> const &b)
        {
            for (int i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }

        template <Primitive U>
        constexpr vec<L, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<L, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<L, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<L, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<L, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr vec<L, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<L, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<L, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<L, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<L, T> &operator%=(U const &other) noexcept requires(size == U::size);

        /// Overloaded subscript operator for non-const rvec.
        [[nodiscard]] constexpr T &operator[](size_t i);
        /// Overloaded subscript operator for const rvec.
        [[nodiscard]] constexpr T const &operator[](size_t i) const;

        /// The underlying data of the vector.
        std::array<T, size> data;

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
}; // namespace mal_math
#include "vecn.inl"