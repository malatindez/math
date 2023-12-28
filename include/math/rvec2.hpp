#pragma once

#include "math-common.hpp"
/**
 * @file rvec2.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Definitions for the rvec<2, T> specialized template representing 2D vectors with reference-like semantics.
 */
#pragma warning(push)
#pragma warning(disable : 4201)
namespace mal_math::_detail
{
    /**
     * @brief Specialization of rvec for 2D vectors.
     * @tparam T Underlying primitive type.
     * 
     * The rvec<2, T> structure represents a 2-dimensional vector with reference-like semantics.
     * This is particularly useful in situations where you want to treat parts of memory as vectors without copying.
     */
    template <Primitive T>
    struct rvec<2, T>
    {
        using type = T; ///< The underlying primitive type.
        static constexpr size_t size = 2; ///< The number of elements in the vector.

        /// Constructor from two primitive values.
        explicit constexpr rvec(T a, T b) : x{ a }, y{ b } {}
        /// Templated constructor from another vector type (non-const version).
        template <AnyVec V>
        explicit constexpr rvec(V &other) requires(V::size >= size) : x{ other.x }, y{ other.y } {}
        /// Templated constructor from another vector type (const version).
        template <AnyVec V>
        explicit constexpr rvec(V const &other) requires(V::size >= size && std::is_const_v<typename V::type>) : x{ other.x }, y{ other.y } {}
        /// Templated factory method to create an rvec<2, T> from another vector type (non-const version).
        template <AnyVec U>
        static constexpr rvec<2, T> from_vec(U &other) requires(U::size >= 2) { return rvec<2, T>{other.x, other.y}; }
        /// Templated factory method to create an rvec<2, T> from another vector type (const version).
        template <AnyVec U>
        static constexpr rvec<2, T> from_vec(U const &other) requires(U::size >= 2) { return rvec<2, T>{other.x, other.y}; }
        /// Resets the vector elements to default.
        constexpr void reset() noexcept;

        /// Assignment operator from another rvec of same size.
        template <typename U>
        constexpr rvec<size, T> &operator=(rvec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        /// Assignment operator from a vec of same size.
        template <typename U>
        constexpr rvec<size, T> &operator=(vec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }

        /// Unary plus operator.
        [[nodiscard]] constexpr rvec<2, T> const &operator+() const noexcept;

        /// Unary minus operator.
        [[nodiscard]] constexpr vec<2, T> operator-() const noexcept;

        // Arithmetic assignment operators with primitives and vectors.
        template <Primitive U>
        constexpr rvec<2, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<2, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<2, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<2, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr rvec<2, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr rvec<2, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<2, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<2, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<2, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr rvec<2, T> &operator%=(U const &other) noexcept requires(size == U::size);

        /// Indexing operator (non-const version).
        [[nodiscard]] constexpr T &operator[](size_t i);
        /// Indexing operator (const version).
        [[nodiscard]] constexpr T const &operator[](size_t i) const;

        /// Explicit cast to a const rvec<2, T>.
        constexpr explicit operator rvec<2, const T>() const noexcept { return rvec<2, const T>{x, y}; }
        /// Union providing various ways to access the data.
        union
        {
            struct
            {
                union
                {
                    _detail::primitive_reference_wrapper<T> x, r, s, u;
                };
                union
                {
                    _detail::primitive_reference_wrapper<T> y, g, t, v;
                };
            };
            std::array<_detail::primitive_reference_wrapper<T>, 2> data; ///< Array access to the elements.
        };
        static_assert(sizeof(data) == 2 * sizeof(_detail::primitive_reference_wrapper<T>));
    };
}; // namespace mal_math
#pragma warning(pop)
#include "rvec2.inl"