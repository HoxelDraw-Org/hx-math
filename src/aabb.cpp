/*
aabb.cpp
April 11, 2023
Contributors:
Justin Jensen
*/

#include "aabb.h"

namespace hxm
{
    // AABBI -------------------------------------------------------------------
    void aabbi::addPoint(const vec4i& pt, bool halfOpenInterval)
    {
        min.x = std::min(pt.x, min.x);
        min.y = std::min(pt.y, min.y);
        min.z = std::min(pt.z, min.z);
        min.w = std::min(pt.w, min.w);

        if (halfOpenInterval)
        {
            max.x = std::max(pt.x + 1, max.x);
            max.y = std::max(pt.y + 1, max.y);
            max.z = std::max(pt.z + 1, max.z);
            max.w = std::max(pt.w + 1, max.w);
        }
        else
        {
            max.x = std::max(pt.x, max.x);
            max.y = std::max(pt.y, max.y);
            max.z = std::max(pt.z, max.z);
            max.w = std::max(pt.w, max.w);
        }
    }

    vec4i aabbi::dim() const
    {
        return max - min;
    }

    bool aabbi::empty() const
    {
        vec4i theDim = dim();
        return (theDim.x <= 0 || theDim.y <= 0 || theDim.z <= 0 || theDim.w <= 0);
    }

    bool aabbi::isValid(bool halfOpenInterval) const
    {
        if (halfOpenInterval)
        {
            return !(max.x <= min.x || max.y <= min.y || max.z <= min.z || max.w <= min.w);
        }
        else
        {
            return !(max.x < min.x || max.y < min.y || max.z < min.z || max.w < min.w);
        }
    }

    void aabbi::addAABB(const aabbi& other)
    {
        min.x = std::min(other.min.x, min.x);
        min.y = std::min(other.min.y, min.y);
        min.z = std::min(other.min.z, min.z);
        min.w = std::min(other.min.w, min.w);

        max.x = std::max(other.max.x, max.x);
        max.y = std::max(other.max.y, max.y);
        max.z = std::max(other.max.z, max.z);
        max.w = std::max(other.max.w, max.w);
    }

    aabbi aabbi::intersect(const aabbi& other) const
    {
        aabbi result;
        result.min.x = std::max(min.x, other.min.x);
        result.min.y = std::max(min.y, other.min.y);
        result.min.z = std::max(min.z, other.min.z);
        result.min.w = std::max(min.w, other.min.w);

        result.max.x = std::min(max.x, other.max.x);
        result.max.y = std::min(max.y, other.max.y);
        result.max.z = std::min(max.z, other.max.z);
        result.max.w = std::min(max.w, other.max.w);

        return result;
    }

    aabbi aabbi::intersect(const vec4i& otherStart, const vec4i& otherEnd) const
    {
        aabbi result;
        for (uint32_t cIdx = 0; cIdx < 4; cIdx++)
        {
            result.min[cIdx] = std::max(otherStart[cIdx], min[cIdx]);
            result.max[cIdx] = std::min(otherEnd[cIdx], max[cIdx]);
        }

        return result;
    }
    
    int aabbi::bulk(bool halfOpenInterval) const
    {
        if (!isValid())
        {
            return 0;
        }
        
        vec4i tDim;
        if (halfOpenInterval)
        {
            tDim = max - min;
        }
        else
        {
            tDim = (max + 1) - min;
        }
        
        return tDim.x * tDim.y * tDim.z * tDim.w;
    }

    void aabbi::reset()
    {
        min = vec4i(INT_MAX);
        max = vec4i(INT_MIN);
    }

    aabbi::aabbi()
    {
        reset();
    }

    aabbi::aabbi(const vec4i& min, const vec4i& max) : min(min), max(max)
    {
    }
    // END AABBI ---------------------------------------------------------------

    // AABB (float) ------------------------------------------------------------
    void aabb::addPoint(const vec4f& pt)
    {
        min.x = std::min(pt.x, min.x);
        min.y = std::min(pt.y, min.y);
        min.z = std::min(pt.z, min.z);
        min.w = std::min(pt.w, min.w);
        
        max.x = std::max(pt.x, max.x);
        max.y = std::max(pt.y, max.y);
        max.z = std::max(pt.z, max.z);
        max.w = std::max(pt.w, max.w);
        
    }

    vec4f aabb::dim() const
    {
        return max - min;
    }

    bool aabb::empty() const
    {
        vec4f theDim = dim();
        return (theDim.x <= 0.f || theDim.y <= 0.f || theDim.z <= 0.f || theDim.w <= 0.f);
    }

    bool aabb::isValid() const
    {
        return !(max.x < min.x || max.y < min.y || max.z < min.z || max.w < min.w);
    }

    void aabb::addAABB(const aabb& other)
    {
        min.x = std::min(other.min.x, min.x);
        min.y = std::min(other.min.y, min.y);
        min.z = std::min(other.min.z, min.z);
        min.w = std::min(other.min.w, min.w);

        max.x = std::max(other.max.x, max.x);
        max.y = std::max(other.max.y, max.y);
        max.z = std::max(other.max.z, max.z);
        max.w = std::max(other.max.w, max.w);
    }

    aabb aabb::intersect(const aabb& other) const
    {
        aabb result;
        result.min.x = std::max(min.x, other.min.x);
        result.min.y = std::max(min.y, other.min.y);
        result.min.z = std::max(min.z, other.min.z);
        result.min.w = std::max(min.w, other.min.w);

        result.max.x = std::min(max.x, other.max.x);
        result.max.y = std::min(max.y, other.max.y);
        result.max.z = std::min(max.z, other.max.z);
        result.max.w = std::min(max.w, other.max.w);

        return result;
    }
    
    float aabb::bulk() const
    {
        if (!isValid())
        {
            return 0.0f;
        }
        
        return (max.x - min.x) * (max.y - min.y) * (max.z - min.z) * (max.w - min.w);
    }

    vec4f aabb::centroid() const
    {
        return (min + max) * 0.5f;
    }

    void aabb::reset()
    {
        min = vec4f(FLT_MAX);
        max = vec4f(-FLT_MAX);
    }

    aabb::aabb()
    {
        reset();
    }

    aabb::aabb(const vec4f& min, const vec4f& max) : min(min), max(max)
    {
    }

    aabb::aabb(const aabbi& otheri) : min(vec4f(otheri.min)), max(vec4f(otheri.max))
    {
    }

    // END AABB ----------------------------------------------------------------
}