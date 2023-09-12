#pragma once
#include "matnxn.hpp"

namespace mal_math
{
    template <size_t a, size_t b, Primitive T>
    template <Primitive P>
    constexpr mat<a, b, T>::mat(P p) requires(a == b)
    {
        reset();
        for (size_t i = 0; i < a; i++)
        {
            data[i][i] = static_cast<T>(p);
        }
    }
    template <size_t a, size_t b, Primitive T>
    template <size_t c, size_t d, Primitive P>
    constexpr mat<a, b, T>::mat(mat<c, d, P> p) requires(a >= c && b >= d)
    {
        reset();
        for (size_t i = 0; i < c; i++)
        {
            for (size_t j = 0; j < d; j++)
            {
                data[i][j] = static_cast<T>(p.data[i][j]);
            }
        }
    }
    template <size_t a, size_t b, Primitive T>
    template <size_t c, size_t d, Primitive P>
    constexpr mat<a, b, T>::mat(rmat<c, d, P> p) requires(a >= c && b >= d)
    {
        reset();
        for (size_t i = 0; i < c; i++)
        {
            for (size_t j = 0; j < d; j++)
            {
                data[i][j] = static_cast<T>(p.data[i][j]);
            }
        }
    }
    template <size_t a, size_t b, Primitive T>
    template <Primitive P>
    constexpr mat<a, b, T>::mat(mat<a, b, P> p)
    {
        for (size_t i = 0; i < a * b; i++)
        {
            arr[i] = static_cast<T>(p.arr[i]);
        }
    }
    template <size_t a, size_t b, Primitive T>
    template <Primitive P>
    constexpr mat<a, b, T>::mat(rmat<a, b, P> p)
    {
        for (size_t i = 0; i < a * b; i++)
        {
            arr[i] = static_cast<T>(p.arr[i]);
        }
    }
    template <size_t a, size_t b, Primitive T>
    template <typename... U>
    constexpr mat<a, b, T>::mat(U... data)
    {
        static_assert(get_parameter_pack_size<U...>() == a * b,
                      "You have provided wrong amount of data");
        unpack_data(0, data...);
    }

    template <size_t a, size_t b, Primitive T>
    constexpr void mat<a, b, T>::reset() noexcept
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i].reset();
        }
        for (size_t i = 0; i < a && i < b; i++)
        {
            data[i][i] = 1;
        }
    }

    template <size_t a, size_t b, Primitive T>
    [[nodiscard]] constexpr vec<b, T> &mat<a, b, T>::operator[](size_t i)
    {
        assert(i < size.x);
        return data[i];
    }
    template <size_t a, size_t b, Primitive T>
    [[nodiscard]] constexpr vec<b, T> const &mat<a, b, T>::operator[](size_t i) const
    {
        assert(i < size.x);
        return data[i];
    }

    template <size_t a, size_t b, Primitive T>
    [[nodiscard]] constexpr mat<a, b, T> const &mat<a, b, T>::operator+() const noexcept
    {
        return *this;
    }

    template <size_t a, size_t b, Primitive T>
    [[nodiscard]] constexpr mat<a, b, T> mat<a, b, T>::operator-() const noexcept
    {
        mat<a, b, T> return_value{};
        for (size_t i = 0; i < size.x; i++)
        {
            return_value.data[i] = -data[i];
        }
        return return_value;
    }

    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator+=(mat<a, b, U> const &other)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }
    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator-=(mat<a, b, U> const &other)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }

    template <size_t a, size_t b, Primitive T>
    template <size_t c, Primitive U>
    constexpr mat<a, c, T> &mat<a, b, T>::operator*=(mat<b, c, U> const &other)
    {
        return (*this = *this * other);
    }

    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator+=(rmat<a, b, U> const &other)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] += other.data[i];
        }
        return *this;
    }
    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator-=(rmat<a, b, U> const &other)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] -= other.data[i];
        }
        return *this;
    }

    template <size_t a, size_t b, Primitive T>
    template <size_t c, Primitive U>
    constexpr mat<a, c, T> &mat<a, b, T>::operator*=(rmat<b, c, U> const &other)
    {
        return (*this = *this * other);
    }

    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator+=(U const value)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] += value;
        }
        return *this;
    }
    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator-=(U const value)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] -= value;
        }
        return *this;
    }
    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr mat<a, b, T> &mat<a, b, T>::operator*=(U const value)
    {
        for (size_t i = 0; i < size.x; i++)
        {
            data[i] *= value;
        }
        return *this;
    }

    template <size_t a, size_t b, Primitive T>
    template <Primitive _>
    constexpr size_t mat<a, b, T>::get_parameter_pack_size()
    {
        // Return the size of the parameter pack for primitive types (always 1).
        return 1;
    }

    template <size_t a, size_t b, Primitive T>
    template <class V>
    constexpr size_t mat<a, b, T>::get_parameter_pack_size()
    {
        // Return the size of the parameter pack for vectors (determined by V::size).
        return V::size;
    }

    template <size_t a, size_t b, Primitive T>
    template <typename A, typename B, typename... C>
    constexpr size_t mat<a, b, T>::get_parameter_pack_size()
    {
        // Recursively compute the total size of the parameter pack.
        // This is achieved by summing the sizes of A, B, and the sizes of C... using recursive calls.
        return get_parameter_pack_size<A>() + get_parameter_pack_size<B, C...>();
    }

    template <size_t a, size_t b, Primitive T>
    template <Primitive U>
    constexpr void mat<a, b, T>::unpack_data(size_t offset, U u)
    {
        // Store the primitive value 'u' at the specified offset in the linear array 'arr'.
        arr[offset] = static_cast<T>(u);
    }

    template <size_t a, size_t b, Primitive T>
    template <class V>
    constexpr void mat<a, b, T>::unpack_data(size_t offset, V vec)
    {
        // Store the elements of the vector 'vec' at the specified offset in the linear array 'arr'.
        for (size_t i = 0; i < V::size; i++)
        {
            arr[offset + i] = static_cast<T>(vec[i]);
        }
    }

    template <size_t a, size_t b, Primitive T>
    template <typename A, typename B, typename... C>
    constexpr void mat<a, b, T>::unpack_data(size_t offset, A first, B second, C... rest)
    {
        // Recursively unpack and store multiple values in the linear array 'arr' at the specified offset.
        // The first value 'first' is stored, and the offset is updated.
        unpack_data(offset, first);

        // Increment the offset based on the size of the parameter 'first', then unpack and store the remaining values.
        offset += get_parameter_pack_size<A>();
        unpack_data(offset, second, rest...);
    }

} // namespace mal_math