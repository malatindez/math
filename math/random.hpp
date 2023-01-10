#pragma once
#include "../math.hpp"
#include <random>
namespace malatindez::math::random
{
    namespace _detail
    {
        template <AnyVec T>
        inline vec<T::size, std::remove_const_t<typename T::type>> UnitRandom(std::mt19937 &gen) noexcept
        {
            std::uniform_real_distribution<float> dis(-1.0f, 1.0f);
            vec<T::size, std::remove_const_t<typename T::type>> p;
            for (size_t i = 0; i < T::size; i++)
                p[i] = dis(gen);
            return normalize(p);
        }
        template<AnyVec T, AnyVec U>
        inline vec<T::size, std::remove_const_t<typename T::type>> RandomVector(std::mt19937 &gen, U const &from, U const &to) noexcept requires(T::size == U::size)
        {
            std::uniform_real_distribution<float> dis(0.0f, 1.0f);
            vec<T::size, std::remove_const_t<typename T::type>> p;
            for (size_t i = 0; i < T::size; i++)
                p[i] = static_cast<typename T::type>(from[i] + dis(gen) * (to[i] - from[i]));
            return p;
        }

        template<AnyVec T, Primitive U>
        inline vec<T::size, std::remove_const_t<typename T::type>> RandomVector(std::mt19937 &gen, U const &from, U const &to) noexcept
        {
            std::uniform_real_distribution<float> dis(0.0f, 1.0f);
            vec<T::size, std::remove_const_t<typename T::type>> p;
            for (size_t i = 0; i < T::size; i++)
                p[i] = static_cast<typename T::type>(from + dis(gen) * (to - from));
            return p;
        }
    } // namespace _detail
    inline vec2 RandomDirection2(std::mt19937 &gen) noexcept { return _detail::UnitRandom<vec2>(gen); }
    inline vec3 RandomDirection3(std::mt19937 &gen) noexcept { return _detail::UnitRandom<vec3>(gen); }
    inline vec4 RandomDirection4(std::mt19937 &gen) noexcept { return _detail::UnitRandom<vec4>(gen); }
    template<AnyVec U>
    vec2 RandomVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<vec2>(gen, from, to); }
    template<AnyVec U>
    vec3 RandomVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<vec3>(gen, from, to); }
    template<AnyVec U>
    vec4 RandomVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<vec4>(gen, from, to); }
    template<Primitive U>
    vec2 RandomVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<vec2>(gen, from, to); }
    template<Primitive U>
    vec3 RandomVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<vec3>(gen, from, to); }
    template<Primitive U>
    vec4 RandomVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<vec4>(gen, from, to); }

    template<AnyVec U>
    dvec2 RandomDVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<dvec2>(gen, from, to); }
    template<AnyVec U>
    dvec3 RandomDVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<dvec3>(gen, from, to); }
    template<AnyVec U>
    dvec4 RandomDVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<dvec4>(gen, from, to); }
    template<Primitive U>
    dvec2 RandomDVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<dvec2>(gen, from, to); }
    template<Primitive U>
    dvec3 RandomDVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<dvec3>(gen, from, to); }
    template<Primitive U>
    dvec4 RandomDVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<dvec4>(gen, from, to); }

    template<AnyVec U>
    ivec2 RandomIVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<ivec2>(gen, from, to); }
    template<AnyVec U>
    ivec3 RandomIVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<ivec3>(gen, from, to); }
    template<AnyVec U>
    ivec4 RandomIVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<ivec4>(gen, from, to); }
    template<Primitive U>
    ivec2 RandomIVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<ivec2>(gen, from, to); }
    template<Primitive U>
    ivec3 RandomIVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<ivec3>(gen, from, to); }
    template<Primitive U>
    ivec4 RandomIVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<ivec4>(gen, from, to); }

    template<AnyVec U>
    uivec2 RandomUVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<uivec2>(gen, from, to); }
    template<AnyVec U>
    uivec3 RandomUVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<uivec3>(gen, from, to); }
    template<AnyVec U>
    uivec4 RandomUVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<uivec4>(gen, from, to); }
    template<Primitive U>
    uivec2 RandomUVector2(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<uivec2>(gen, from, to); }
    template<Primitive U>
    uivec3 RandomUVector3(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<uivec3>(gen, from, to); }
    template<Primitive U>
    uivec4 RandomUVector4(std::mt19937 &gen, U const &from, U const &to) noexcept { return _detail::RandomVector<uivec4>(gen, from, to); }

    namespace poisson_disc
    {
        namespace _detail
        {
            template<AnyVec U>
            inline std::vector<U> PoissonDisc(std::mt19937 &gen, U const &from, U const &to, float min_distance, size_t max_attempts = 30) noexcept
            {
                std::vector<U> result;
                std::uniform_real_distribution<float> dist(0.0f, 1.0f);
                std::vector<U> active;
                result.push_back(random::_detail::RandomVector<U>(gen, from, to));
                active.push_back(result.back());
                while (!active.empty())
                {
                    std::uniform_int_distribution<size_t> dist2(0, active.size() - 1);
                    size_t index = dist2(gen);
                    U point = active[index];
                    bool found = false;
                    for (size_t i = 0; i < max_attempts; ++i)
                    {
                        U new_point = point + random::_detail::RandomVector<U>(gen, -min_distance, min_distance);
                        if (new_point.x < from.x || new_point.x > to.x || new_point.y < from.y || new_point.y > to.y)
                            continue;
                        bool ok = true;
                        for (auto const &p : result)
                        {
                            if (distance(p, new_point) < min_distance)
                            {
                                ok = false;
                                break;
                            }
                        }
                        if (ok)
                        {
                            found = true;
                            result.push_back(new_point);
                            active.push_back(new_point);
                            break;
                        }
                    }
                    if (!found)
                    {
                        active.erase(active.begin() + index);
                    }
                }
                return result;
            }
        } // namespace _detail
        inline std::vector<vec2> Generate(std::mt19937 &gen, vec2 const &from, vec2 const &to, float min_distance, size_t max_attempts = 30) noexcept
        {
            return _detail::PoissonDisc<vec2>(gen, from, to, min_distance, max_attempts);
        }
    } // namespace poisson_disc
} // namespace malatindez::math::random