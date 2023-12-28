#pragma once

#include "math-common.hpp"
/**
 * @file rvec3.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Provides the implementation of a 3D reference vector.
 */

#pragma warning(push)
#pragma warning(disable : 4201)
namespace mal_math::_detail
{
    /**
     * @brief 3D reference vector template structure.
     *
     * @tparam T Primitive data type of the vector.
     */
    template <Primitive T>
    struct rvec<3, T>
    {
        using type = T; ///< Alias for the data type.
        static constexpr size_t size = 3; ///< Number of elements in the vector.
        /// Constructor initializing vector with three values.
        explicit constexpr rvec(T &a, T &b, T &c) : x{ a }, y{ b }, z{ c } {}
        /// Construct from another vector with size check.
        template <AnyVec V>
        explicit constexpr rvec(V &other) requires(V::size >= size) : x{ other.x }, y{ other.y }, z{ other.z } {}
        /// Construct from a constant vector with size and constness check.
        template <AnyVec V>
        explicit constexpr rvec(V const &other) requires(V::size >= size && std::is_const_v<typename V::type>) : x{ other.x }, y{ other.y }, z{ other.z } {}
        /// Static method to construct from another vector with size check.
        template <AnyVec U>
        static constexpr rvec<3, T> from_vec(U &other) requires(U::size >= 3) { return rvec<3, T>(other.x, other.y, other.z); }
        /// Static method to construct from a constant vector with size check.
        template <AnyVec U>
        static constexpr rvec<3, T> from_vec(U const &other) requires(U::size >= 3) { return rvec<3, T>(other.x, other.y, other.z); }
        /// Resets the vector values to zeroes.
        constexpr void reset() noexcept;
        /// Overloaded assignment operator for copying from another rvec.
        template <typename U>
        constexpr rvec<size, T> &operator=(rvec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        /// Overloaded assignment operator for copying from vec.
        template <typename U>
        constexpr rvec<size, T> &operator=(vec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }

        /// Overloaded unary plus operator.
        [[nodiscard]] constexpr rvec<3, T> const &operator+() const noexcept;
        /// Overloaded unary minus operator.
        [[nodiscard]] constexpr vec<3, T> operator-() const noexcept;

        template <Primitive U>
        constexpr rvec<3, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<3, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<3, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<3, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<3, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr rvec<3, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<3, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<3, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<3, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<3, T> &operator%=(U const &other) noexcept requires(size == U::size);

        /// Overloaded subscript operator for non-const rvec.
        [[nodiscard]] constexpr T &operator[](size_t i);
        /// Overloaded subscript operator for const rvec.
        [[nodiscard]] constexpr T const &operator[](size_t i) const;

        /// Explicit conversion to a constant rvec.
        constexpr explicit operator rvec<3, const T>() const noexcept { return rvec<3, const T>{x, y, z}; }

        /**
         * @brief Convert the vector to another reference vector type with a different size.
         *
         * @tparam n Target size of the reference vector (defaulted to current size).
         * @return rvec<n, T> The converted reference vector.
         */
        template <size_t n = size>
        [[nodiscard]] constexpr rvec<n, T> as_rvec() noexcept requires(n >= 2 && n <= size);

        /**
         * @brief Convert the vector to a non-reference vector type with a different size and type.
         *
         * @tparam n Target size of the vector (defaulted to current size).
         * @tparam U Target primitive type of the vector (defaulted to current type).
         * @return vec<n, std::remove_const_t<U>> The converted vector.
         */
        template <size_t n = size, Primitive U = T>
        [[nodiscard]] constexpr vec<n, std::remove_const_t<U>> as_vec() const noexcept requires(n >= 2 && n <= size);
        
        /**
         * @brief Convert the vector to a constant reference vector type with a different size.
         *
         * @tparam n Target size of the constant reference vector (defaulted to current size).
         * @return rvec<n, const T> The converted constant reference vector.
         */
        template <size_t n = size>
        [[nodiscard]] constexpr rvec<n, const T> as_crvec() const noexcept requires(n >= 2 && n <= size);
        /// Union allowing multiple ways to access the vector elements.
        union
        {
            struct
            {
                union
                {
                    _detail::primitive_reference_wrapper<T> x, r, s;
                };
                union
                {
                    _detail::primitive_reference_wrapper<T> y, g, t;
                };
                union
                {
                    _detail::primitive_reference_wrapper<T> z, b, p;
                };
            };
            std::array<_detail::primitive_reference_wrapper<T>, 3> data;
        };
        static_assert(sizeof(data) == 3 * sizeof(_detail::primitive_reference_wrapper<T>));
    };
}; // namespace mal_math
#pragma warning(pop)
#include "rvec3.inl"