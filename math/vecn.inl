#pragma once
#include "vecn.hpp"
namespace malatindez::math
{
    template <size_t L, Primitive T>
    template <Primitive U>
    constexpr vec<L, T>::vec(U value)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(value);
        }
    }
    template <size_t L, Primitive T>
    template <typename... U>
    constexpr vec<L, T>::vec(U... data)
    {
        static_assert(get_parameter_pack_size<U...>() == size,
                      "You have provided wrong amount of data");
        unpack_data(0, data...);
    }
    template <size_t L, Primitive T>
    constexpr void vec<L, T>::reset() noexcept
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = 0;
        }
    }

    template <size_t L, Primitive T>
    template <Primitive U>
    constexpr vec<L, T> &vec<L, T>::operator+=(U const value) noexcept
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] + value);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <Primitive U>
    constexpr vec<L, T> &vec<L, T>::operator-=(U const value) noexcept
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] - value);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <Primitive U>
    constexpr vec<L, T> &vec<L, T>::operator*=(U const value) noexcept
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] * value);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <Primitive U>
    constexpr vec<L, T> &vec<L, T>::operator/=(U const value) noexcept
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] / value);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <Primitive U>
    constexpr vec<L, T> &vec<L, T>::operator%=(U const value) noexcept
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] % value);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <AnyVec U>
    constexpr vec<L, T> &vec<L, T>::operator+=(U const &other) noexcept requires(size == U::size)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] + other.data[i]);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <AnyVec U>
    constexpr vec<L, T> &vec<L, T>::operator-=(U const &other) noexcept requires(size == U::size)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] - other.data[i]);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <AnyVec U>
    constexpr vec<L, T> &vec<L, T>::operator*=(U const &other) noexcept requires(size == U::size)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] * other.data[i]);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <AnyVec U>
    constexpr vec<L, T> &vec<L, T>::operator/=(U const &other) noexcept requires(size == U::size)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] / other.data[i]);
        }
        return *this;
    }
    template <size_t L, Primitive T>
    template <AnyVec U>
    constexpr vec<L, T> &vec<L, T>::operator%=(U const &other) noexcept requires(size == U::size)
    {
        for (int i = 0; i < size; i++)
        {
            data[i] = static_cast<T>(data[i] % other.data[i]);
        }
        return *this;
    }

    template <size_t L, Primitive T>
    [[nodiscard]] constexpr T &vec<L, T>::operator[](size_t i)
    {
        assert(i < size);
        return data[i];
    }
    template <size_t L, Primitive T>
    [[nodiscard]] constexpr T const &vec<L, T>::operator[](size_t i) const
    {
        assert(i < size);
        return data[i];
    }
    template <size_t L, Primitive T>
    template <Primitive _> // primitives
    constexpr size_t vec<L, T>::get_parameter_pack_size()
    {
        return 1;
    }
    template <size_t L, Primitive T>
    template <class V> // vectors
    constexpr size_t vec<L, T>::get_parameter_pack_size()
    {
        return V::size;
    }
    template <size_t L, Primitive T>
    template <typename A, typename B, typename... C>
    constexpr size_t vec<L, T>::get_parameter_pack_size()
    {
        return get_parameter_pack_size<A>() + get_parameter_pack_size<B, C...>();
    }

    template <size_t L, Primitive T>
    template <Primitive U> // primitives
    constexpr void vec<L, T>::unpack_data(int offset, U u)
    {
        data[offset] = static_cast<T>(u);
    }
    template <size_t L, Primitive T>
    template <class V> // vectors
    constexpr void vec<L, T>::unpack_data(int offset, V vec)
    {
        for (int i = 0; i < V::size; i++)
        {
            data[offset + i] = static_cast<T>(vec[i]);
        }
    }
    template <size_t L, Primitive T>
    template <typename A, typename B, typename... C>
    constexpr void vec<L, T>::unpack_data(int offset, A a, B b, C... c)
    {
        unpack_data(offset, a);
        offset += get_parameter_pack_size<A>();
        unpack_data(offset, b, c...);
    }
}; // namespace malatindez::math