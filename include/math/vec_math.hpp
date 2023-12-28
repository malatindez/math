#pragma once
#include "vec.hpp"
/**
 * @file vec_math.hpp
 * 
 * @author malatindez (Vladyslav Ohlii)
 * @date 12/09/2023
 * 
 * @brief Contains a collection of mathematical operations and utility functions for vector objects.
 */

namespace mal_math
{
    /**
     * @brief Input stream operator overload for vector objects.
     */
    template <AnyVec U>
    constexpr std::istream &operator>>(std::istream &is, U &vec);
    /**
     * @brief Output stream operator overload for const vector objects.
     */
    template <AnyVec U>
    constexpr std::ostream &operator<<(std::ostream &os, U const &vec);
    /**
     * @brief Output stream operator overload for vector objects.
     */
    template <AnyVec U>
    constexpr std::ostream &operator<<(std::ostream &os, U &vec);
    /**
     * @brief Convert a given vector to a reference of vec with specified size and type.
     * 
     * @tparam n The size of the resulting vector.
     * @tparam Vector The type of the input vector.
     * @param v The input vector to be converted.
     * @return A reference to vec of size n and the type of Vector.
     * @note Requires that n is between 2 and the size of the input Vector.
     */
    template <size_t n, AnyVec Vector>
    [[nodiscard]] constexpr vec<n, typename Vector::type> &as_rvec(Vector &v) noexcept requires(n >= 2 && n <= Vector::size);
    
    /**
     * @brief Convert a given vector to a reference of vec with the same size and type.
     * 
     * @tparam Vector The type of the input vector.
     * @param v The input vector to be converted.
     * @return A reference to vec of the same size and type as the input Vector.
     */
    template <AnyVec Vector>
    [[nodiscard]] constexpr vec<Vector::size, typename Vector::type> &as_rvec(Vector &v) noexcept;

    /**
     * @brief Create a new vector of a specified size and type from the given vector.
     * 
     * @tparam n The size of the resulting vector.
     * @tparam U The type of the resulting vector.
     * @tparam Vector The type of the input vector.
     * @param v The input vector to be converted.
     * @return A new vec of size n and type U.
     * @note Requires that n is between 2 and the size of the input Vector.
     */
    template <size_t n, Primitive U, AnyVec Vector>
    [[nodiscard]] constexpr vec<n, U> as_vec(Vector const &v) noexcept requires(n >= 2 && n <= Vector::size);
    /**
     * @brief Create a new vector of a specified size from the given vector, preserving the type.
     * 
     * @tparam n The size of the resulting vector.
     * @tparam Vector The type of the input vector.
     * @param v The input vector to be converted.
     * @return A new vec of size n and type derived from the input Vector.
     * @note Requires that n is between 2 and the size of the input Vector.
     */
    template <size_t n, AnyVec Vector>
    [[nodiscard]] constexpr vec<n, std::remove_const_t<typename Vector::type>> as_vec(Vector const &v) noexcept requires(n >= 2 && n <= Vector::size);
    /**
     * @brief Create a new vector of the same size from the given vector, preserving the type.
     * 
     * @tparam Vector The type of the input vector.
     * @param v The input vector to be converted.
     * @return A new vec of the same size and type as the input Vector.
     */
    template <AnyVec Vector>
    [[nodiscard]] constexpr vec<Vector::size, std::remove_const_t<typename Vector::type>> as_vec(Vector const &v) noexcept;

    /**
     * @brief Convert a given const vector to a const reference of vec with specified size and type.
     * 
     * @tparam n The size of the resulting vector.
     * @tparam Vector The type of the input vector.
     * @param v The input const vector to be converted.
     * @return A const reference to vec of size n and the type of Vector.
     * @note Requires that n is between 2 and the size of the input Vector.
     */
    template <size_t n, AnyVec Vector>
    [[nodiscard]] constexpr vec<n, typename Vector::type> const &as_crvec(Vector const &v) noexcept requires(n >= 2 && n <= Vector::size);
    
    /**
     * @brief Convert a given const vector to a const reference of vec with the same size and type.
     * 
     * @tparam Vector The type of the input vector.
     * @param v The input const vector to be converted.
     * @return A const reference to vec of the same size and type as the input Vector.
     */
    template <AnyVec Vector>
    [[nodiscard]] constexpr vec<Vector::size, typename Vector::type> const &as_crvec(Vector const &v) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator+(vec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator-(vec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator*(vec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator/(vec<size, T> const &vector, U const value) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator*(U const value, vec<size, T> const &vector) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator/(U const value, vec<size, T> const &vector) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator+(U const value, vec<size, T> const &vector) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator-(U const value, vec<size, T> const &vector) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator*(U const value, _detail::rvec<size, T> const &vector) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator+(_detail::rvec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator-(_detail::rvec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator*(_detail::rvec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator/(_detail::rvec<size, T> const &vector, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator%(_detail::rvec<size, T> const &left, U const value) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator+(vec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator-(vec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator*(vec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator/(vec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator%(vec<size, T> const &left, U const value) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator%(vec<size, T> const &left, vec<size, U> const &right) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator+(_detail::rvec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator-(_detail::rvec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator*(_detail::rvec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator/(_detail::rvec<size, T> const &left, vec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator%(_detail::rvec<size, T> const &left, vec<size, U> const &right) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator+(_detail::rvec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator-(_detail::rvec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator*(_detail::rvec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator/(_detail::rvec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, std::remove_const_t<T>> operator%(_detail::rvec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;

    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator+(vec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator-(vec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator*(vec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator/(vec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;
    template <size_t size, Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<size, T> operator%(vec<size, T> const &left, _detail::rvec<size, U> const &right) noexcept;

    template <AnyVec T, AnyVec U>
    [[nodiscard]] constexpr bool operator==(T const &left, U const &right) noexcept requires(T::size == U::size);

    template <AnyVec T, AnyVec U>
    [[nodiscard]] constexpr bool operator!=(T const &left, U const &right) noexcept requires(T::size == U::size);
    /**
     * @brief Compute the squared length of the given vector.
     * 
     * @tparam T The vector type.
     * @param vector The input vector.
     * @return The squared length of the vector.
     */
    template <AnyVec T>
    [[nodiscard]] constexpr typename std::remove_const_t<typename T::type> squared_length(T const &vector) noexcept;
    /**
     * @brief Compute the length (magnitude) of the given vector.
     * 
     * @tparam T The vector type.
     * @param vector The input vector.
     * @return The length of the vector.
     */
    template <AnyVec T>
    [[nodiscard]] constexpr auto length(T const &vector) noexcept;

    /**
     * @brief Compute the unit vector (normalized vector) of the given vector.
     * 
     * @tparam T The vector type.
     * @param vector The input vector.
     * @return The unit vector.
     */
    template <AnyVec T>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> unit_vector(T const &vector) noexcept;
    /**
     * @brief Normalize the given vector.
     * 
     * @tparam T The vector type.
     * @param vector The input vector.
     * @return The normalized vector.
     * @note This function is synonymous to unit_vector.
     */
    template <AnyVec T>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> normalize(T const &vector) noexcept;

    /**
     * @brief Compute the dot product of two vectors.
     * 
     * @tparam T The type of the left vector.
     * @tparam U The type of the right vector.
     * @param left The left vector.
     * @param right The right vector.
     * @return The dot product of the two vectors.
     * @note Requires that both vectors have the same size.
     */
    template <AnyVec T, AnyVec U>
    constexpr std::remove_const_t<typename T::type> dot(T const &left, U const &right) noexcept requires(T::size == U::size);

    /**
     * @brief Compute the angle between two vectors.
     * 
     * @tparam T The type of the left vector.
     * @tparam U The type of the right vector.
     * @param left The left vector.
     * @param right The right vector.
     * @return The angle between the two vectors.
     * @note Requires that both vectors have the same size.
     */
    template <AnyVec T, AnyVec U>
    constexpr std::remove_const_t<typename T::type> angle(T const &left, U const &right) noexcept requires(T::size == U::size);

    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> cos(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> sin(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> tan(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> acos(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> asin(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> atan(T const &vector) noexcept;
    template <AnyVec T, AnyVec U>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> atan(T const &left, U const &right) noexcept requires(T::size == U::size);
    template <AnyVec T, AnyVec U>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> atan2(T const &left, U const &right) noexcept requires(T::size == U::size);
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> cosh(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> sinh(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> tanh(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> acosh(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> asinh(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> atanh(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> exp(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> exp2(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> expm1(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> log(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> log2(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> log10(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> log1p(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> logb(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> sqrt(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> inversesqrt(T const &vector) noexcept;

    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> abs(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> sign(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> floor(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> ceil(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> trunc(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> round(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> roundEven(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> fract(T const &vector) noexcept;
    template <AnyVec T>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> mod(T const &vector, typename T::type const &scalar) noexcept;
    template <AnyVec T, AnyVec U>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> mod(T const &left, U const &right) noexcept requires(T::size == U::size);

    template <AnyVec T, Primitive U>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> pow(T const &vector, U const pow) noexcept;

    template <AnyVec T, AnyVec U>
    constexpr vec<T::size, std::remove_const_t<typename T::type>> pow(T const &vector1, U const &vector2) noexcept;
    /**
     * @brief Compute the cross product of two 3D vectors.
     * 
     * @tparam T Type of the left vector.
     * @tparam U Type of the right vector.
     * @param left The left vector.
     * @param right The right vector.
     * @return The cross product of the two vectors.
     * @note Requires that both vectors have a size of 3.
     */
    template <AnyVec T, AnyVec U>
    constexpr vec<3, std::remove_const_t<typename T::type>> cross(T const &left, U const &right) noexcept requires(T::size == U::size && T::size == 3);

    /**
     * @brief Clamp the value of `left` between `min` and `max` in-place.
     * 
     * @tparam T Type of the value to be clamped.
     * @tparam U Type of the boundary values.
     * @param left The value to be clamped.
     * @param min The minimum value.
     * @param max The maximum value.
     */
    template <Primitive T, Primitive U>
    constexpr void rclamp(T &left, U const min, U const max) noexcept;

    /**
     * @brief Clamp the value of `left` between `min` and `max` in-place.
     * 
     * @tparam T Type of the value to be clamped.
     * @tparam U Type of the boundary values.
     * @param left The value to be clamped.
     * @param min The minimum value.
     * @param max The maximum value.
     */
    template <AnyVec T, AnyVec U>
    constexpr void rclamp(T &left, U const min, U const max) noexcept requires(T::size == U::size);

    /**
     * @brief Clamp the value of `left` between `min` and `max`.
     * 
     * @tparam T Type of the value to be clamped.
     * @tparam U Type of the boundary values.
     * @param left The value to be clamped.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The clamped value.
     */
    template <AnyVec T, Primitive U>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> clamp(T const &left, U const min, U const max) noexcept;

    /**
     * @brief Clamp the value of `left` between `min` and `max`.
     * 
     * @tparam T Type of the value to be clamped.
     * @tparam U Type of the boundary values.
     * @param left The value to be clamped.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The clamped value.
     */
    template <AnyVec T, AnyVec U>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> clamp(T const &left, U const &min, U const &max) noexcept requires(T::size == U::size);

    /**
     * @brief Clamp the value of `left` between `min` and `max`.
     * 
     * @tparam T Type of the value to be clamped.
     * @tparam U Type of the boundary values.
     * @param left The value to be clamped.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return The clamped value.
     */
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr T clamp(T left, U const min, U const max) noexcept;
    /**
     * @brief Returns a new vector with each element being the minimum of the corresponding element in `left` and `max`.
     * 
     * @tparam T Vector type.
     * @tparam U Primitive type for the max value.
     * @param left Input vector.
     * @param max Maximum value for each element.
     * @return Vector containing the element-wise minimum values.
     */
    template <AnyVec T, Primitive U>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> min(T const &left, U const min) noexcept;
    /**
     * @brief Returns a new vector with each element being the maximum of the corresponding element in `left` and `min`.
     * 
     * @tparam T Vector type.
     * @tparam U Primitive type for the min value.
     * @param left Input vector.
     * @param min Minimum value for each element.
     * @return Vector containing the element-wise maximum values.
     */
    template <AnyVec T, Primitive U>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> max(T const &left, U const max) noexcept;

    /**
     * @brief Returns a new vector with each element being the minimum of the corresponding elements in `left` and `right`.
     * 
     * @tparam T Type of the left vector.
     * @tparam U Type of the right vector.
     * @param left First input vector.
     * @param right Second input vector.
     * @return Vector containing the element-wise minimum values.
     */
    template <AnyVec T, AnyVec U>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> min(T const &left, U const &min) noexcept requires(T::size == U::size);

    /**
     * @brief Returns a new vector with each element being the maximum of the corresponding elements in `left` and `right`.
     * 
     * @tparam T Type of the left vector.
     * @tparam U Type of the right vector.
     * @param left First input vector.
     * @param right Second input vector.
     * @return Vector containing the element-wise maximum values.
     */
    template <AnyVec T, AnyVec U>
    [[nodiscard]] constexpr vec<T::size, std::remove_const_t<typename T::type>> max(T const &left, U const &max) noexcept requires(T::size == U::size);

    /**
     * @brief Modifies `left` in-place, setting each element to the minimum of itself and the corresponding element in `max`.
     * 
     * @tparam T Type of the vector to modify.
     * @tparam U Type of the max vector.
     * @param left Vector to be modified.
     * @param max Vector containing maximum values.
     */
    template <AnyVec T, AnyVec U>
    constexpr void rmin(T &left, U const &max) noexcept  requires(T::size == U::size);

    /**
     * @brief Modifies `left` in-place, setting each element to the maximum of itself and the corresponding element in `min`.
     * 
     * @tparam T Type of the vector to modify.
     * @tparam U Type of the min vector.
     * @param left Vector to be modified.
     * @param min Vector containing minimum values.
     */
    template <AnyVec T, AnyVec U>
    constexpr void rmax(T &left, U const &min) noexcept  requires(T::size == U::size);

    /**
     * @brief Modifies `left` in-place, setting each element to the minimum of itself and `max`.
     * 
     * @tparam T Type of the vector to modify.
     * @tparam U Primitive type for the max value.
     * @param left Vector to be modified.
     * @param max Maximum value for each element.
     */
    template <AnyVec T, Primitive U>
    constexpr void rmin(T &left, U const max) noexcept;

    /**
     * @brief Modifies `left` in-place, setting each element to the maximum of itself and `min`.
     * 
     * @tparam T Type of the vector to modify.
     * @tparam U Primitive type for the min value.
     * @param left Vector to be modified.
     * @param min Minimum value for each element.
     */
    template <AnyVec T, Primitive U>
    constexpr void rmax(T &left, U const min) noexcept;

    /**
     * @brief Modifies `left` in-place, setting its value to the minimum of itself and `max`.
     * 
     * @tparam T Primitive type of the value to modify.
     * @tparam U Primitive type for the max value.
     * @param left Value to be modified.
     * @param max Maximum value.
     */
    template <Primitive T, Primitive U>
    constexpr void rmin(T &left, U const max) noexcept;

    /**
     * @brief Modifies `left` in-place, setting its value to the maximum of itself and `min`.
     * 
     * @tparam T Primitive type of the value to modify.
     * @tparam U Primitive type for the min value.
     * @param left Value to be modified.
     * @param min Minimum value.
     */
    template <Primitive T, Primitive U>
    constexpr void rmax(T &left, U const min) noexcept;
    /**
     * @brief Compute the distance between two vectors.
     * 
     * @tparam T Type of the vectors.
     * @param left The first vector.
     * @param right The second vector.
     * @return The distance between the two vectors.
     */
    template <AnyVec T>
    [[nodiscard]] constexpr std::remove_const_t<typename T::type> distance(T const &left, T const &right) noexcept;
    /**
     * @brief Linearly interpolate between two values.
     * 
     * @tparam T Type of the values to interpolate between.
     * @tparam U Type of the interpolation parameter.
     * @param from The starting value.
     * @param to The target value.
     * @param param The interpolation parameter (usually between 0 and 1).
     * @return The interpolated value.
     */
    template <typename T, Primitive U>
    [[nodiscard]] constexpr auto lerp(T const &from, T const &to, U const param) noexcept;

    /**
     * @brief Mix between two values (same as lerp).
     * 
     * @tparam T Type of the values to mix between.
     * @tparam U Type of the mix parameter.
     * @param from The starting value.
     * @param to The target value.
     * @param param The mix parameter (usually between 0 and 1).
     * @return The mixed value.
     */
    template <typename T, Primitive U>
    [[nodiscard]] constexpr auto mix(T const &from, T const &to, U const param) noexcept;
} // namespace mal_math
#include "vec_math.inl"
