#pragma once
/**
 * @file math.hpp
 * @brief Provides various mathematical utilities, vector operations, and custom hash specializations.
 * 
 * This file contains a collection of mathematical functions and classes tailored for graphics
 * and physics calculations. It includes functionalities for reflection, refraction, and 
 * specialized hash functions for custom math types. Specific utilities involve operations 
 * on vectors, matrices, quaternions, and other geometric primitives.
 */

#if defined(__clang__)
// TODO
#elif defined(__GNUC__) || defined(__GNUG__)
// TODO
#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 6001)  // Using uninitialized memory 'variable'.
#pragma warning(disable : 6287)  // Redundant code: the left and right subexpressions are identical
#pragma warning(disable : 26495) // Variable 'variable' is uninitialized. Always initialize a member variable (type.6).
#endif

#include "math/mat.hpp"
#include "math/ray.hpp"
#include "math/intersection.hpp"
#include "math/triangle.hpp"
#include "math/plane.hpp"
#include "math/box.hpp"
#include "math/quaternion.hpp"
#include "math/sphere.hpp"
#include "math/random.hpp"

/**
 * @namespace mal_math
 * @brief Contains mathematical utility functions and classes.
 */
namespace mal_math
{
    namespace numbers = ::std::numbers;
    
    /**
     * @brief Computes the reflection of an incident vector based on a surface's normal.
     * 
     * Given an incident vector and the normal at the point of incidence, this function
     * calculates the direction that a perfectly reflected ray would take.
     *
     * @tparam Vector A vector type that should satisfy the AnyVec concept, having both `size` and `type` members.
     * @param[in] normal The unit vector normal to the surface at the point of incidence.
     * @param[in] incident The unit vector pointing in the direction of the incoming ray.
     * 
     * @return vec<Vector::size, std::remove_const_t<typename Vector::type>> The reflected vector direction.
     * 
     * @note Assumes both `incident` and `normal` are unit vectors. If they aren't, the result might not be correct.
     */
    template <AnyVec Vector>
    [[nodiscard]] constexpr vec<Vector::size, std::remove_const_t<typename Vector::type>> reflect(Vector const &normal, Vector const &incident) noexcept
    {
        return incident - 2.0f * dot(normal, incident) * normal;
    }
    
    /**
     * @brief Computes the refraction of a vector given an interface's normal and an index of refraction.
     * 
     * This function calculates the refracted direction of an incident vector at the boundary 
     * of two materials with a given index of refraction.
     *
     * @tparam Vector A vector type that should have a defined `size` and `type` member.
     * @param[in] normal The unit vector normal to the interface at the point of incidence.
     * @param[in] incident The unit vector pointing in the direction of the incoming ray.
     * @param[in] eta The relative index of refraction (ratio of indices of refraction).
     * 
     * @return vec<Vector::size, std::remove_const_t<typename Vector::type>> The refracted vector direction.
     * 
     * @note The returned vector may not be a unit vector if there is total internal reflection.
     */
    template <AnyVec Vector>
    [[nodiscard]] constexpr vec<Vector::size, std::remove_const_t<typename Vector::type>> refract(Vector const &normal, Vector const &incident, float eta) noexcept
    {
        auto const cos_theta = dot(normal, incident);
        auto const r_out_perp = eta * (incident - cos_theta * normal);
        auto const r_out_parallel = -std::sqrt(std::abs(1.0f - squared_length(r_out_perp))) * normal;
        return r_out_perp + r_out_parallel;
    }
} // namespace mal_math

/**
 * @namespace std
 * @brief Standard namespace, extended with hash specializations for custom math types.
 */
namespace std {
    /**
     * @brief Hash specialization for mal_math::vec.
     * 
     * @tparam size_x Vector dimension.
     * @tparam vector_type Type of vector's elements.
     */
    template <size_t size_x, typename vector_type>
    struct hash<mal_math::vec<size_x, vector_type>> {
        [[nodiscard]] constexpr size_t operator()(mal_math::vec<size_x, vector_type> const &v) const noexcept {
            size_t seed = 0;
            for (auto const &e : v.data) {
                seed ^= std::hash<vector_type>{}(e)+0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
    /**
     * @brief Hash specialization for mal_math::vec.
     * 
     * @tparam size_x Matrix X dimension.
     * @tparam size_y Matrix Y dimension.
     * @tparam vector_type Type of matrix elements.
     */
    template <size_t size_x, size_t size_y, typename matrix_type>
    struct hash<mal_math::mat<size_x, size_y, matrix_type>> {
        [[nodiscard]] constexpr size_t operator()(mal_math::mat<size_x, size_y, matrix_type> const &m) const noexcept {
            size_t seed = 0;
            for (auto const &e : m.data) {
                seed ^= std::hash<matrix_type>{}(e)+0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
    /**
     * @brief Hash specialization for mal_math::vec.
     * 
     * @tparam size_x Matrix X dimension.
     * @tparam size_y Matrix Y dimension.
     * @tparam vector_type Type of matrix elements.
     */
    template<typename quaternion_type>
    struct hash<mal_math::qua<quaternion_type>> {
        [[nodiscard]] constexpr size_t operator()(mal_math::qua<quaternion_type> const &q) const noexcept {
            size_t seed = 0;
            for (auto const &e : q.data) {
                seed ^= std::hash<quaternion_type>{}(e)+0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
} // namespace std
#if defined(__clang__)
// TODO
#elif defined(__GNUC__) || defined(__GNUG__)
// TODO
#elif defined(_MSC_VER)
#pragma warning(pop)
#endif