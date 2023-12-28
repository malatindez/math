#pragma once
/**
 * @file vec2.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Defines a 2D vector and provides its operations.
 */

#include "vec.hpp"

#pragma warning(push)
#pragma warning(disable : 4201)
namespace mal_math
{
    /**
     * @brief 2D vector template class.
     * @tparam T Primitive type used for the vector's components.
     */
    template <Primitive T>
    struct vec<2, T>
    {
        static_assert(!std::is_const_v<T>);
        using type = T; ///< Type of the vector's components.
        static constexpr size_t size = 2; ///< Size of the vector.
        /// Default constructor.
        constexpr vec() = default;
        /// Constructs a vec with both components set to value.
        template <Primitive U>
        constexpr vec(U value);
        /// Constructs a vec with given values for x and y components.
        template <Primitive A, Primitive B>
        constexpr vec(A a, B b);
        /// Constructs a vec from a variadic list of values.
        template <typename... U>
        constexpr vec(U... data);
        /// Constructs a vec from a given array.
        constexpr vec(std::array<T, size> const &arr) : data{ arr } {}
        /// Constructs a vec by moving data from a given array.
        constexpr vec(std::array<T, size> &&arr) : data{ std::move(arr) } {}
        /// Returns a new zero-initialized vec.
        constexpr static vec<2, T> zero() noexcept { return vec<2, T>(0); }
        /// Resets the vec to zeroes.
        constexpr void reset() noexcept;

        /// Assignment operator from a rvec.
        template <typename U>
        constexpr vec<size, T> &operator=(_detail::rvec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        /// Assignment operator from another vec.
        template <typename U>
        constexpr vec<size, T> &operator=(vec<size, U> const &b)
        {
            for (size_t i = 0; i < size; i++)
            {
                data[i] = b.data[i];
            }
            return *this;
        }
        /// Unary plus operator.
        [[nodiscard]] constexpr vec<2, T> const &operator+() const noexcept;

        /// Unary minus operator.
        [[nodiscard]] constexpr vec<2, T> operator-() const noexcept;

        template <Primitive U>
        constexpr vec<2, T> &operator+=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<2, T> &operator-=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<2, T> &operator*=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<2, T> &operator/=(U const value) noexcept;
        template <Primitive U>
        constexpr vec<2, T> &operator%=(U const value) noexcept;
        template <AnyVec U>
        constexpr vec<2, T> &operator+=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<2, T> &operator-=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<2, T> &operator*=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<2, T> &operator/=(U const &other) noexcept requires(size == U::size);
        template <AnyVec U>
        constexpr vec<2, T> &operator%=(U const &other) noexcept requires(size == U::size);

        /// Indexing operator (non-const version).
        [[nodiscard]] constexpr T &operator[](size_t i);
        /// Indexing operator (const version).
        [[nodiscard]] constexpr T const &operator[](size_t i) const;
        /// Union providing various ways to access the data.
        union
        {
            struct
            {
                union
                {
                    T x, r, s, u;
                };
                union
                {
                    T y, g, t, v;
                };
            };
            std::array<T, 2> data;  ///< Array access to the elements.
        };
        static_assert(sizeof(data) == 2 * sizeof(T));

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
#pragma warning(pop)
#include "vec2.inl"