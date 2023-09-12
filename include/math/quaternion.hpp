#pragma once
#include "mat.hpp"
#pragma warning(push)
#pragma warning(disable : 4201)
/**
 * @file quaternion.hpp
 * @brief Quaternion operations and related mathematical functions.
 * 
 * This header file provides the definition and utility functions for quaternions.
 * Quaternions are mathematical objects used to represent rotations in 3D space
 * without the gimbal lock issues that can be encountered with Euler angles.
 * The file includes functions to convert between quaternions and various other
 * forms of representing orientation and rotation, such as Euler angles and rotation matrices.
 */
namespace mal_math
{
    /**
     * @class qua
     * @brief Represents a quaternion with primitive type T.
     * @tparam T Data type of the quaternion components (should be a primitive type).
     */
    template <Primitive T>
    struct qua
    {
        /// @brief Alias for the primitive data type used in the quaternion.
        using type = T;
        /// @brief Represents the number of components in the quaternion.
        static constexpr size_t size = 4;
        /// @brief Default constructor initializes the quaternion to its default state (1, 0, 0, 0).
        constexpr qua() : qua(1, 0, 0, 0) {}
        /// @brief Constructs a quaternion from its four components.
        constexpr explicit qua(T w, T x, T y, T z);
        /// @brief Resets the quaternion to its default state (1, 0, 0, 0).
        constexpr void reset();
        /**
         * @brief Constructs a quaternion from an angle and rotation axis.
         * @param radians Angle of rotation in radians.
         * @param axis A 3D vector representing the axis of rotation.
         */
        constexpr explicit qua(T radians, vec<3, T> axis);

        /**
         * @brief Converts the quaternion to a 3x3 rotation matrix.
         * @return A 3x3 matrix representing the rotation defined by this quaternion.
         */
        [[nodiscard]] constexpr mat<3, 3, T> as_mat3() const noexcept;
        /**
         * @brief Converts the quaternion to a 4x4 rotation matrix.
         * @return A 4x4 matrix representing the rotation defined by this quaternion.
         */
        [[nodiscard]] constexpr mat<4, 4, T> as_mat4() const noexcept;
        /**
         * @brief Retrieves the axis of rotation from the quaternion.
         * @return A 3D vector representing the axis of rotation.
         */
        [[nodiscard]] constexpr vec<3, T> const &axis() const noexcept;
        /**
         * @brief Retrieves the angle of rotation from the quaternion.
         * @return Angle of rotation in radians.
         */
        [[nodiscard]] constexpr T radians() const noexcept;
        /**
         * @brief Unary plus operator.
         * @return A reference to the quaternion.
         */
        [[nodiscard]] constexpr qua<T> const &operator+() const noexcept;
        /**
         * @brief Unary minus operator. Inverts the sign of each component.
         * @return A new quaternion with inverted components.
         */
        [[nodiscard]] constexpr qua<T> operator-() const noexcept;

        /**
         * @brief Multiplies the quaternion by a scalar value.
         * @tparam U Primitive type of the scalar.
         * @param value Scalar value to multiply the quaternion with.
         * @return Reference to the modified quaternion.
         */
        template <Primitive U>
        constexpr qua<T> &operator*=(U const value) noexcept;
        /**
         * @brief Divides the components of the quaternion by a scalar value.
         * @tparam U Primitive type of the scalar.
         * @param value Scalar value to divide the quaternion components by.
         * @return Reference to the modified quaternion.
         */
        template <Primitive U>
        constexpr qua<T> &operator/=(U const value) noexcept;
        
        /**
         * @brief Adds another quaternion to this quaternion component-wise.
         * @tparam U Primitive type of the other quaternion.
         * @param other The other quaternion to be added to this one.
         * @return Reference to the modified quaternion.
         */
        template <Primitive U>
        constexpr qua<T> &operator+=(qua<U> const &other) noexcept;
        
        /**
         * @brief Subtracts another quaternion from this quaternion component-wise.
         * @tparam U Primitive type of the other quaternion.
         * @param other The other quaternion to be subtracted from this one.
         * @return Reference to the modified quaternion.
         */
        template <Primitive U>
        constexpr qua<T> &operator-=(qua<U> const &other) noexcept;
        
        /**
         * @brief Multiplies this quaternion with another quaternion.
         * @tparam U Primitive type of the other quaternion.
         * @param other The other quaternion to multiply with this one.
         * @return Reference to the modified quaternion.
         */
        template <Primitive U>
        constexpr qua<T> &operator*=(qua<U> const &other) noexcept;
        
        /**
         * @brief Divides this quaternion by another quaternion.
         * @note Ensure that the divisor quaternion isn't near zero to avoid inaccuracies or division by zero errors.
         * @tparam U Primitive type of the other quaternion.
         * @param other The divisor quaternion.
         * @return Reference to the modified quaternion.
         */
        template <Primitive U>
        constexpr qua<T> &operator/=(qua<U> const &other) noexcept;

        /**
         * @brief Accesses a component of the quaternion by index.
         * @param i Index of the component (0-based).
         * @return Reference to the i-th component of the quaternion.
         */
        [[nodiscard]] constexpr T &operator[](size_t i);
        
        /**
         * @brief Accesses a component of the quaternion by index (const version).
         * @param i Index of the component (0-based).
         * @return Const reference to the i-th component of the quaternion.
         */
        [[nodiscard]] constexpr T const &operator[](size_t i) const;

        /// @brief Unions allowing various ways to access quaternion components.
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
                union
                {
                    T w, a, q;
                };
            };
            std::array<T, size> data;
        };
        static_assert(sizeof(data) == size * sizeof(T));
    };
    /// @brief Reads a vector of given size from an input stream.
    template <size_t size, Primitive T>
    constexpr std::istream &operator>>(std::istream &is, vec<size, T> &vec);
    /// @brief Writes a vector of given size to an output stream.
    template <size_t size, Primitive T>
    constexpr std::ostream &operator<<(std::ostream &os, vec<size, T> &vec);

    /// Scalar-quaternion multiplication.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator*(U const value, qua<T> const &vector) noexcept;
    
    /// Scalar-quaternion division.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator/(U const value, qua<T> const &vector) noexcept;
    /// Quaternion-scalar multiplication.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator*(qua<T> const &vector, U const value) noexcept;
    /// Quaternion-scalar division.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator/(qua<T> const &vector, U const value) noexcept;
    /// Quaternion addition.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator+(qua<T> const &left, qua<U> const &right) noexcept;
    /// Quaternion subtraction.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator-(qua<T> const &left, qua<U> const &right) noexcept;
    /// Quaternion multiplication.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator*(qua<T> const &left, qua<U> const &right) noexcept;
    /// Quaternion division.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> operator/(qua<T> const &left, qua<U> const &right) noexcept;

    /// @brief Computes the dot product of two quaternions.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr T dot(qua<T> const &left, qua<U> const &right) noexcept;
    /// @brief Computes the angle (or magnitude) of a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr T angle(qua<T> const &quaternion) noexcept;
    /// @brief Computes the pitch from a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr T pitch(qua<T> const &quaternion) noexcept;
    /// @brief Computes the yaw from a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr T yaw(qua<T> const &quaternion) noexcept;
    /// @brief Computes the roll from a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr T roll(qua<T> const &quaternion) noexcept;
    /// @brief Converts a quaternion to Euler angles.
    template <Primitive T>
    [[nodiscard]] constexpr vec<3, T> QuaternionToEuler(qua<T> const &quaternion) noexcept;

    /// @brief Creates a quaternion from Euler angles given in a vector.
    template <Primitive T>
    [[nodiscard]] constexpr qua<T> QuaternionFromEuler(vec<3, T> const &angles) noexcept;
    /// @brief Creates a quaternion from individual Euler angles.
    template <Primitive T>
    [[nodiscard]] constexpr qua<T> QuaternionFromEuler(T roll, T pitch, T yaw) noexcept requires(std::is_floating_point_v<T>);
    /// @brief Creates a quaternion from a 3x3 rotation matrix.
    template <AnyMat U>
    [[nodiscard]] constexpr qua<typename U::type> QuaternionFromRotationMatrix(U const &mat) noexcept requires(U::size.x == 3 && U::size.y == 3 && std::is_floating_point_v<typename U::type>);
    /// Quaternion-Quaternion multiplication.
    template <Primitive T>
    [[nodiscard]] constexpr qua<T> operator*(qua<T> const &q, qua<T> const &p) noexcept;
    /// Quaternion-Vector multiplication.
    template <Primitive T>
    [[nodiscard]] constexpr vec<3, T> operator*(qua<T> const &q, vec<3, T> const &v) noexcept;
    
    /// Vector-Quaternion multiplication.
    template <Primitive T>
    [[nodiscard]] constexpr vec<3, T> operator*(vec<3, T> const &v, qua<T> const &q) noexcept;
    /// @brief Computes the conjugate of a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr qua<T> conjugate(qua<T> const &q) noexcept;
    /// @brief Computes the inverse of a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr qua<T> inverse(qua<T> const &q) noexcept;
    /// Cross product between quaternion and vector.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<3, T> cross(qua<T> const &left, vec<3, U> const &right) noexcept;
    /// Cross product between vector and quaternion.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr vec<3, T> cross(vec<3, U> const &left, qua<T> const &right) noexcept;
    /// @brief Computes the cross product of two quaternions.
    template <Primitive T, Primitive U>
    [[nodiscard]] constexpr qua<T> cross(qua<T> const &left, qua<U> const &right) noexcept;

    /// @brief Rotates a 4x4 matrix using a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr mat<4, 4, T> rotate(mat<4, 4, T> const &matrix, qua<T> const &q) noexcept;
    /// @brief Computes the length (or magnitude) of a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr T length(qua<T> const &q) noexcept;
    /// @brief Normalizes a quaternion.
    template <Primitive T>
    [[nodiscard]] constexpr qua<T> normalize(qua<T> const &q) noexcept;
} // namespace mal_math

#pragma warning(pop)

namespace mal_math
{
    using quat = qua<float>;
    using dquat = qua<double>;
}; // namespace mal_math
#include "quaternion.inl"