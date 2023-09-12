#pragma once

#include "vec.hpp"
/**
 * @file rvec4.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Defines a 4-dimensional reference vector struct.
 */

#pragma warning(push)
#pragma warning(disable : 4201)
namespace mal_math::_detail
{
    /**
     * @brief A 4-dimensional reference vector template.
     *
     * @tparam T A primitive data type.
     */
    template <Primitive T>
    struct rvec<4, T>
    {
        using type = T; ///< Alias for the data type.
        static constexpr size_t size = 4; ///< Number of elements in the vector.
        
        /// Constructs a vector from individual components.
        explicit constexpr rvec(T &a, T &b, T &c, T &d) : x{ a }, y{ b }, z{ c }, w{ d } {}
        /// Constructs a vector from another vector with compatible size.
        template <AnyVec V>
        explicit constexpr rvec(T &other) requires(V::size >= size) : x{ other.x }, y{ other.y }, z{ other.z }, w{ other.w } {}
        /// Constructs a vector from a constant vector with compatible size.
        template <AnyVec V>
        explicit constexpr rvec(T const &other) requires(V::size >= size && std::is_const_v<typename V::type>) : x{ other.x }, y{ other.y }, z{ other.z }, w{ other.w } {}

        /// Converts from another vector to this type.
        template <AnyVec U>
        static constexpr rvec<4, T> from_vec(U &other) requires(U::size >= 4) { return rvec<4, T>{other.x, other.y, other.z, other.w}; }
        /// Converts from a constant other vector to this type.
        template <AnyVec U>
        static constexpr rvec<4, T> from_vec(U const &other) requires(U::size >= 4) { return rvec<4, T>{other.x, other.y, other.z, other.w}; }

        /// Assignment operator from another reference vector with compatible type.
        template <typename U>
        constexpr rvec<size, T> &operator=(rvec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        /// Assignment operator from a non-reference vector with compatible type.
        template <typename U>
        constexpr rvec<size, T> &operator=(vec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }

        /// Resets all vector components to zeroes.
        constexpr void reset() noexcept;

        /// Unary plus operator.
        [[nodiscard]] constexpr rvec<4, T> const &operator+() const noexcept;
        /// Unary minus operator.
        [[nodiscard]] constexpr vec<4, T> operator-() const noexcept;

        template <Primitive U>
        constexpr rvec<4, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<4, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<4, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<4, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<4, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr rvec<4, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<4, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<4, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<4, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<4, T> &operator%=(U const &other) noexcept requires(size == U::size);

        /// Overloaded subscript operator for non-const rvec.
        [[nodiscard]] constexpr T &operator[](size_t i);
        /// Overloaded subscript operator for const rvec.
        [[nodiscard]] constexpr T const &operator[](size_t i) const;

        /// Explicit conversion to a constant rvec.
        constexpr explicit operator rvec<4, const T>() const noexcept { return rvec<4, const T>{x, y, z, w}; }

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
        /// Union allowing for various representations of the vector components.
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
                union
                {
                    _detail::primitive_reference_wrapper<T> w, a, q;
                };
            };
            std::array<_detail::primitive_reference_wrapper<T>, 4> data;
        };
        static_assert(sizeof(data) == 4 * sizeof(_detail::primitive_reference_wrapper<T>));
    };
}; // namespace mal_math
#pragma warning(pop)
#include "rvec4.inl"