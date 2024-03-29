#pragma once
#include "vec4.hpp"
namespace mal_math
{
    template <Primitive T>
    template <Primitive U>
    constexpr vec<4, T>::vec(U value) { x = y = z = w = static_cast<T>(value); }
    template <Primitive T>
    template <Primitive A, Primitive B, Primitive C, Primitive D>
    constexpr vec<4, T>::vec(A a, B b, C c, D d)
    {
        x = static_cast<T>(a);
        y = static_cast<T>(b);
        z = static_cast<T>(c);
        w = static_cast<T>(d);
    }
    template <Primitive T>
    template <typename... U>
    constexpr vec<4, T>::vec(U... data)
    {
        static_assert(get_parameter_pack_size<U...>() == size,
                      "You have provided wrong amount of data");
        unpack_data(0, data...);
    }
    template <Primitive T>
    constexpr void vec<4, T>::reset() noexcept
    {
        x = y = z = w = 0;
    }

    template <Primitive T>
    [[nodiscard]] constexpr vec<4, T> const &vec<4, T>::operator+() const noexcept
    {
        return *this;
    }
    template <Primitive T>
    [[nodiscard]] constexpr vec<4, T> vec<4, T>::operator-() const noexcept
    {
        return vec<4, T>(-x, -y, -z, -w);
    }

    template <Primitive T>
    template <Primitive U>
    constexpr vec<4, T> &vec<4, T>::operator+=(U const value) noexcept
    {
        x = static_cast<T>(x + value);
        y = static_cast<T>(y + value);
        z = static_cast<T>(z + value);
        w = static_cast<T>(w + value);
        return *this;
    }
    template <Primitive T>
    template <Primitive U>
    constexpr vec<4, T> &vec<4, T>::operator-=(U const value) noexcept
    {
        x = static_cast<T>(x - value);
        y = static_cast<T>(y - value);
        z = static_cast<T>(z - value);
        w = static_cast<T>(w - value);
        return *this;
    }
    template <Primitive T>
    template <Primitive U>
    constexpr vec<4, T> &vec<4, T>::operator*=(U const value) noexcept
    {
        x = static_cast<T>(x * value);
        y = static_cast<T>(y * value);
        z = static_cast<T>(z * value);
        w = static_cast<T>(w * value);
        return *this;
    }
    template <Primitive T>
    template <Primitive U>
    constexpr vec<4, T> &vec<4, T>::operator/=(U const value) noexcept
    {
        x = static_cast<T>(x / value);
        y = static_cast<T>(y / value);
        z = static_cast<T>(z / value);
        w = static_cast<T>(w / value);
        return *this;
    }
    template <Primitive T>
    template <Primitive U>
    constexpr vec<4, T> &vec<4, T>::operator%=(U const value) noexcept
    {
        x = static_cast<T>(x % value);
        y = static_cast<T>(y % value);
        z = static_cast<T>(z % value);
        w = static_cast<T>(w % value);
        return *this;
    }
    template <Primitive T>
    template <AnyVec U>
    constexpr vec<4, T> &vec<4, T>::operator+=(U const &other) noexcept requires(size == U::size)
    {
        x = static_cast<T>(x + other.x);
        y = static_cast<T>(y + other.y);
        z = static_cast<T>(z + other.z);
        w = static_cast<T>(w + other.w);
        return *this;
    }
    template <Primitive T>
    template <AnyVec U>
    constexpr vec<4, T> &vec<4, T>::operator-=(U const &other) noexcept requires(size == U::size)
    {
        x = static_cast<T>(x - other.x);
        y = static_cast<T>(y - other.y);
        z = static_cast<T>(z - other.z);
        w = static_cast<T>(w - other.w);
        return *this;
    }
    template <Primitive T>
    template <AnyVec U>
    constexpr vec<4, T> &vec<4, T>::operator*=(U const &other) noexcept requires(size == U::size)
    {
        x = static_cast<T>(x * other.x);
        y = static_cast<T>(y * other.y);
        z = static_cast<T>(z * other.z);
        w = static_cast<T>(w * other.w);
        return *this;
    }
    template <Primitive T>
    template <AnyVec U>
    constexpr vec<4, T> &vec<4, T>::operator/=(U const &other) noexcept requires(size == U::size)
    {
        x = static_cast<T>(x / other.x);
        y = static_cast<T>(y / other.y);
        z = static_cast<T>(z / other.z);
        w = static_cast<T>(w / other.w);
        return *this;
    }
    template <Primitive T>
    template <AnyVec U>
    constexpr vec<4, T> &vec<4, T>::operator%=(U const &other) noexcept requires(size == U::size)
    {
        x = static_cast<T>(x % other.x);
        y = static_cast<T>(y % other.y);
        z = static_cast<T>(z % other.z);
        w = static_cast<T>(w % other.w);
        return *this;
    }
    template <Primitive T>
    [[nodiscard]] constexpr T &vec<4, T>::operator[](size_t i)
    {
        assert(i < size);
        return data[i];
    }
    template <Primitive T>
    [[nodiscard]] constexpr T const &vec<4, T>::operator[](size_t i) const
    {
        assert(i < size);
        return data[i];
    }

    template <Primitive T>
    template <Primitive _> // primitives
    constexpr size_t vec<4, T>::get_parameter_pack_size()
    {
        return 1;
    }
    template <Primitive T>
    template <class V> // vectors
    constexpr size_t vec<4, T>::get_parameter_pack_size()
    {
        return V::size;
    }
    template <Primitive T>
    template <typename A, typename B, typename... C>
    constexpr size_t vec<4, T>::get_parameter_pack_size()
    {
        return get_parameter_pack_size<A>() + get_parameter_pack_size<B, C...>();
    }

    template <Primitive T>
    template <Primitive U> // primitives
    constexpr void vec<4, T>::unpack_data(size_t offset, U u)
    {
        data[offset] = static_cast<T>(u);
    }
    template <Primitive T>
    template <class V> // vectors
    constexpr void vec<4, T>::unpack_data(size_t offset, V vec)
    {
        for (size_t i = 0; i < V::size; i++)
        {
            data[offset + i] = static_cast<T>(vec[i]);
        }
    }
    template <Primitive T>
    template <typename A, typename B, typename... C>
    constexpr void vec<4, T>::unpack_data(size_t offset, A a, B b, C... c)
    {
        unpack_data(offset, a);
        offset += get_parameter_pack_size<A>();
        unpack_data(offset, b, c...);
    }
}; // namespace mal_math