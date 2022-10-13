#pragma once
#include "intersection.hpp"
#include "ray.hpp"
namespace malatindez::math
{
    struct Plane
    {
        bool Intersect(Intersection &i, Ray const &ray) const
        {
            float denom = dot(normal, ray.direction());
            if (std::abs(denom) <= 1e-6f)
            {
                return false;
            }
            float t = dot(-ray.origin(), normal) / denom;
            if (t > i.t || t <= 0)
            {
                return false;
            }
            i.t = t;
            // reverse normal if the ray is on the opposite side of the plane
            i.normal = normal * (denom > 0 ? -1 : 1);
            i.point = ray.PointAtParameter(t);
            return true;
        }
        void update_plane(vec3 const &first, vec3 const &second)
        {
            vec3 temp = -cross(first, second);
            if (length(temp) == 0)
            {
                throw std::invalid_argument("Input vectors can't be collinear!");
            }
            v = first;
            w = second;
            normal = normalize(temp);
        }
        vec3 v;
        vec3 w;
        vec3 normal;
    };
}