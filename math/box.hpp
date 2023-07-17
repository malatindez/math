#pragma once

#include "../math.hpp"

namespace malatindez::math
{
    template<typename T>
    struct TBox
    {
        using vector3 = vec<3, T>;
        vector3 min;
        vector3 max;

        static constexpr float Inf = std::numeric_limits<float>::infinity();
        static constexpr TBox empty() { return  { vector3{ Inf, Inf, Inf }, vector3{ -Inf, -Inf, -Inf } }; }
        static constexpr TBox unit() { return  { vector3{ -1.f, -1.f, -1.f }, vector3{ 1.f, 1.f, 1.f } }; }

        vector3 size() const { return max - min; }
        vector3 center() const { return (min + max) / 2.f; }
        float radius() const { return length(size()) / 2.f; }

        void reset()
        {
            constexpr float maxf = std::numeric_limits<float>::max();
            min = vector3{ maxf , maxf , maxf };
            max = -min;
        }

        template<typename U>
        void expand(const TBox<U> &other)
        {
            expand(other.min);
            expand(other.max);
        }

        void expand(const vector3 &point)
        {
            min = math::min(min, point);
            max = math::max(max, point);
        }

        bool contains(const vector3 &P)
        {
            return
                min[0] <= P[0] && P[0] <= max[0] &&
                min[1] <= P[1] && P[1] <= max[1] &&
                min[2] <= P[2] && P[2] <= max[2];
        }
        inline bool Intersect(Ray const &ray, float &nearest_t) const
        {
            float tmin, tmax, tymin, tymax, tzmin, tzmax;

            auto const &bounds = reinterpret_cast<std::array<vector3, 2> const &>(*this);

            tmin = (bounds[ray.sign()[0]].x - ray.origin().x) * ray.inv_direction().x;
            tmax = (bounds[1ll - ray.sign()[0]].x - ray.origin().x) * ray.inv_direction().x;
            tymin = (bounds[ray.sign()[1]].y - ray.origin().y) * ray.inv_direction().y;
            tymax = (bounds[1ll - ray.sign()[1]].y - ray.origin().y) * ray.inv_direction().y;

            if ((tmin > tymax) || (tymin > tmax))
                return false;

            if (tymin > tmin)
                tmin = tymin;
            if (tymax < tmax)
                tmax = tymax;

            tzmin = (bounds[ray.sign()[2]].z - ray.origin().z) * ray.inv_direction().z;
            tzmax = (bounds[1ll - ray.sign()[2]].z - ray.origin().z) * ray.inv_direction().z;

            if ((tmin > tzmax) || (tzmin > tmax))
                return false;

            if (tzmin > tmin)
                tmin = tzmin;
            if (tzmax < tmax)
                tmax = tzmax;

            float t = tmin;

            if (t < 0)
            {
                t = tmax;
                if (t < 0 || t > nearest_t)
                    return false;
            }
            nearest_t = t;
            return true;
        }

        inline bool Intersect(Ray const &ray, Intersection &nearest) const
        {
            float tmin, tmax, tymin, tymax, tzmin, tzmax;

            auto const &bounds = reinterpret_cast<std::array<vector3, 2> const &>(*this);

            tmin = (bounds[ray.sign()[0]].x - ray.origin().x) * ray.inv_direction().x;
            tmax = (bounds[1ll - ray.sign()[0]].x - ray.origin().x) * ray.inv_direction().x;
            tymin = (bounds[ray.sign()[1]].y - ray.origin().y) * ray.inv_direction().y;
            tymax = (bounds[1ll - ray.sign()[1]].y - ray.origin().y) * ray.inv_direction().y;

            if ((tmin > tymax) || (tymin > tmax))
                return false;

            if (tymin > tmin)
                tmin = tymin;
            if (tymax < tmax)
                tmax = tymax;

            tzmin = (bounds[ray.sign()[2]].z - ray.origin().z) * ray.inv_direction().z;
            tzmax = (bounds[1ll - ray.sign()[2]].z - ray.origin().z) * ray.inv_direction().z;

            if ((tmin > tzmax) || (tzmin > tmax))
                return false;

            if (tzmin > tmin)
                tmin = tzmin;
            if (tzmax < tmax)
                tmax = tzmax;

            float t = tmin;

            if (t < 0)
            {
                t = tmax;
                if (t < 0 || t > nearest.t)
                    return false;
            }
            nearest.t = t;
            nearest.point = ray.PointAtParameter(t);
            return true;
        }
    };

    using Box = TBox<float>;
    using Boxf = TBox<float>;
    using Boxd = TBox<double>;
}