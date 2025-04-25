/*
aabb.cpp
April 11, 2023
Contributors:
Justin Jensen
*/

#include "aabb.h"

namespace hxm
{
    // AABB3 (float) ------------------------------------------------------------
    void aabb3f::addPoint(const vec3f& pt)
    {
        min.x = std::min(pt.x, min.x);
        min.y = std::min(pt.y, min.y);
        min.z = std::min(pt.z, min.z);

        max.x = std::max(pt.x, max.x);
        max.y = std::max(pt.y, max.y);
        max.z = std::max(pt.z, max.z);
    }

    vec3f aabb3f::dim() const
    {
        return max - min;
    }

    bool aabb3f::empty() const
    {
        vec3f theDim = dim();
        return (theDim.x <= 0.f || theDim.y <= 0.f || theDim.z <= 0.f);
    }

    bool aabb3f::isValid() const
    {
        return !(max.x < min.x || max.y < min.y || max.z < min.z);
    }

    void aabb3f::addAABB(const aabb3f& other)
    {
        min.x = std::min(other.min.x, min.x);
        min.y = std::min(other.min.y, min.y);
        min.z = std::min(other.min.z, min.z);

        max.x = std::max(other.max.x, max.x);
        max.y = std::max(other.max.y, max.y);
        max.z = std::max(other.max.z, max.z);
    }

    aabb3f aabb3f::intersect(const aabb3f& other) const
    {
        aabb3f result;
        result.min.x = std::max(min.x, other.min.x);
        result.min.y = std::max(min.y, other.min.y);
        result.min.z = std::max(min.z, other.min.z);

        result.max.x = std::min(max.x, other.max.x);
        result.max.y = std::min(max.y, other.max.y);
        result.max.z = std::min(max.z, other.max.z);

        return result;
    }

    float aabb3f::volume() const
    {
        if (!isValid())
        {
            return 0.0f;
        }

        return (max.x - min.x) * (max.y - min.y) * (max.z - min.z);
    }

    vec3f aabb3f::centroid() const
    {
        return (min + max) * 0.5f;
    }

    float aabb3f::centroid(uint32_t axis) const
    {
        return (min[axis] + max[axis]) * 0.5f;
    }

    void aabb3f::padToMin(float pad)
    {
        // adjust the AABB so that no side is narrower than some delta
        const float halfDelta = pad * 0.5f;
        const size_t nDimensions = 3;
        for (size_t axIdx = 0; axIdx < nDimensions; axIdx++)
        {
            if (max[axIdx] - min[axIdx] < AABB_MIN)
            {
                min[axIdx] -= halfDelta;
                max[axIdx] += halfDelta;
            }
        }
    }

    vec3f& aabb3f::operator[](uint32_t idx)
    {
        return _b[idx];
    }

    vec3f aabb3f::operator[](uint32_t idx) const
    {
        return _b[idx];
    }

    aabb3f& aabb3f::operator+=(const aabb3f& other)
    {
        min.x = std::min(other.min.x, min.x);
        min.y = std::min(other.min.y, min.y);
        min.z = std::min(other.min.z, min.z);

        max.x = std::max(other.max.x, max.x);
        max.y = std::max(other.max.y, max.y);
        max.z = std::max(other.max.z, max.z);

        return *this;
    }

    aabb3f& aabb3f::operator+=(const vec3f& v)
    {
        min.x = std::min(v.x, min.x);
        min.y = std::min(v.y, min.y);
        min.z = std::min(v.z, min.z);

        max.x = std::max(v.x, max.x);
        max.y = std::max(v.y, max.y);
        max.z = std::max(v.z, max.z);

        return *this;
    }

    void aabb3f::reset()
    {
        min = vec3f(FLT_MAX);
        max = vec3f(-FLT_MAX);
    }

    aabb3f::aabb3f()
    {
        reset();
    }

    aabb3f::aabb3f(const vec3f& min, const vec3f& max) : min(min), max(max)
    {
    }

    // END AABB3 ----------------------------------------------------------------

    // AABB4I -------------------------------------------------------------------
    void aabb4i::addPoint(const vec4i& pt, bool halfOpenInterval)
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

    vec4i aabb4i::dim() const
    {
        return max - min;
    }

    bool aabb4i::empty() const
    {
        vec4i theDim = dim();
        return (theDim.x <= 0 || theDim.y <= 0 || theDim.z <= 0 || theDim.w <= 0);
    }

    bool aabb4i::isValid(bool halfOpenInterval) const
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

    void aabb4i::addAABB(const aabb4i& other)
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

    aabb4i aabb4i::intersect(const aabb4i& other) const
    {
        aabb4i result;
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

    aabb4i aabb4i::intersect(const vec4i& otherStart, const vec4i& otherEnd) const
    {
        aabb4i result;
        for (uint32_t cIdx = 0; cIdx < 4; cIdx++)
        {
            result.min[cIdx] = std::max(otherStart[cIdx], min[cIdx]);
            result.max[cIdx] = std::min(otherEnd[cIdx], max[cIdx]);
        }

        return result;
    }
    
    int aabb4i::bulk(bool halfOpenInterval) const
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

    void aabb4i::reset()
    {
        min = vec4i(INT_MAX);
        max = vec4i(INT_MIN);
    }

    vec4i& aabb4i::operator[](uint32_t idx)
    {
        return _b[idx];
    }

    vec4i aabb4i::operator[](uint32_t idx) const
    {
        return _b[idx];
    }

    aabb4i& aabb4i::operator+=(const aabb4i& other)
    {
        min.x = std::min(other.min.x, min.x);
        min.y = std::min(other.min.y, min.y);
        min.z = std::min(other.min.z, min.z);
        min.w = std::min(other.min.w, min.w);

        max.x = std::max(other.max.x, max.x);
        max.y = std::max(other.max.y, max.y);
        max.z = std::max(other.max.z, max.z);
        max.w = std::max(other.max.w, max.w);

        return *this;
    }

    aabb4i::aabb4i()
    {
        reset();
    }

    aabb4i::aabb4i(const vec4i& min, const vec4i& max) : min(min), max(max)
    {
    }
    // END AABB4I ---------------------------------------------------------------

    // AABB4F -------------------------------------------------------------------
    void aabb4f::addPoint(const vec4f& pt)
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

    vec4f aabb4f::dim() const
    {
        return max - min;
    }

    bool aabb4f::empty() const
    {
        vec4f theDim = dim();
        return (theDim.x <= 0.f || theDim.y <= 0.f || theDim.z <= 0.f || theDim.w <= 0.f);
    }

    bool aabb4f::isValid() const
    {
        return !(max.x < min.x || max.y < min.y || max.z < min.z || max.w < min.w);
    }

    void aabb4f::addAABB(const aabb4f& other)
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

    aabb4f aabb4f::intersect(const aabb4f& other) const
    {
        aabb4f result;
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
    
    float aabb4f::bulk() const
    {
        if (!isValid())
        {
            return 0.0f;
        }
        
        return (max.x - min.x) * (max.y - min.y) * (max.z - min.z) * (max.w - min.w);
    }

    vec4f aabb4f::centroid() const
    {
        return (min + max) * 0.5f;
    }

    float aabb4f::centroid(uint32_t axis) const
    {
        return (min[axis] + max[axis]) * 0.5f;
    }

    void aabb4f::padToMin(float pad)
    {
        // adjust the AABB so that no side is narrower than some delta
        const float halfDelta = pad * 0.5f;
        const size_t nDimensions = 4;
        for (size_t axIdx = 0; axIdx < nDimensions; axIdx++)
        {
            if (max[axIdx] - min[axIdx] < AABB_MIN)
            {
                min[axIdx] -= halfDelta;
                max[axIdx] += halfDelta;
            }
        }
    }

    void aabb4f::reset()
    {
        min = vec4f(FLT_MAX);
        max = vec4f(-FLT_MAX);
    }

    vec4f& aabb4f::operator[](uint32_t idx)
    {
        return _b[idx];
    }

    vec4f aabb4f::operator[](uint32_t idx) const
    {
        return _b[idx];
    }

    aabb4f& aabb4f::operator+=(const aabb4f& other)
    {
        min.x = std::min(other.min.x, min.x);
        min.y = std::min(other.min.y, min.y);
        min.z = std::min(other.min.z, min.z);
        min.w = std::min(other.min.w, min.w);

        max.x = std::max(other.max.x, max.x);
        max.y = std::max(other.max.y, max.y);
        max.z = std::max(other.max.z, max.z);
        max.w = std::max(other.max.w, max.w);

        return *this;
    }

    aabb4f& aabb4f::operator+=(const vec4f& v)
    {
        min.x = std::min(v.x, min.x);
        min.y = std::min(v.y, min.y);
        min.z = std::min(v.z, min.z);
        min.w = std::min(v.w, min.w);

        max.x = std::max(v.x, max.x);
        max.y = std::max(v.y, max.y);
        max.z = std::max(v.z, max.z);
        max.w = std::max(v.w, max.w);

        return *this;
    }

    aabb4f::aabb4f()
    {
        reset();
    }

    aabb4f::aabb4f(const vec4f& min, const vec4f& max) : min(min), max(max)
    {
    }

    aabb4f::aabb4f(const aabb4i& otheri) : min(vec4f(otheri.min)), max(vec4f(otheri.max))
    {
    }

    // END AABB4 ----------------------------------------------------------------
}