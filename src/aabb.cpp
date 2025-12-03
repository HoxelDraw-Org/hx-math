/*
aabb.cpp
April 11, 2023
Contributors:
Justin Jensen
*/

#include "aabb.h"
#include <climits>

namespace hxm
{
    // AABB3 (float) ------------------------------------------------------------
    void aabb3f::addPoint(const vec3f& pt)
    {
        _b[0].x = std::min(pt.x, _b[0].x);
        _b[0].y = std::min(pt.y, _b[0].y);
        _b[0].z = std::min(pt.z, _b[0].z);

        _b[1].x = std::max(pt.x, _b[1].x);
        _b[1].y = std::max(pt.y, _b[1].y);
        _b[1].z = std::max(pt.z, _b[1].z);
    }

    vec3f aabb3f::dim() const
    {
        return _b[1] - _b[0];
    }

    bool aabb3f::empty() const
    {
        vec3f theDim = dim();
        return (theDim.x <= 0.f || theDim.y <= 0.f || theDim.z <= 0.f);
    }

    bool aabb3f::isValid() const
    {
        return !(max().x > min().x || max().y > min().y || max().z > min().z);
    }

    void aabb3f::addAABB(const aabb3f& other)
    {
        _b[0].x = std::min(other.min().x, _b[0].x);
        _b[0].y = std::min(other.min().y, _b[0].y);
        _b[0].z = std::min(other.min().z, _b[0].z);

        _b[1].x = std::max(other.max().x, _b[1].x);
        _b[1].y = std::max(other.max().y, _b[1].y);
        _b[1].z = std::max(other.max().z, _b[1].z);
    }

    aabb3f aabb3f::intersect(const aabb3f& other) const
    {
        aabb3f result;
        result._b[0].x = std::max(_b[0].x, other.min().x);
        result._b[0].y = std::max(_b[0].y, other.min().y);
        result._b[0].z = std::max(_b[0].z, other.min().z);

        result._b[1].x = std::min(_b[1].x, other.max().x);
        result._b[1].y = std::min(_b[1].y, other.max().y);
        result._b[1].z = std::min(_b[1].z, other.max().z);

        return result;
    }

    float aabb3f::area() const
    {
        vec3f d = dim();
        return 2.0f * ((d.x * d.y) + (d.x * d.z) + (d.y * d.z));
    }

    float aabb3f::volume() const
    {
        if (!isValid())
        {
            return 0.0f;
        }

        return (max().x - min().x) * (max().y - min().y) * (max().z - min().z);
    }

    vec3f aabb3f::centroid() const
    {
        return (min() + max()) * 0.5f;
    }

    float aabb3f::centroid(uint32_t axis) const
    {
        return (min()[axis] + max()[axis]) * 0.5f;
    }

    void aabb3f::padToMin(float pad)
    {
        // adjust the AABB so that no side is narrower than some delta
        const float halfDelta = pad * 0.5f;
        const size_t nDimensions = 3;
        for (size_t axIdx = 0; axIdx < nDimensions; axIdx++)
        {
            if (max()[axIdx] - min()[axIdx] < AABB_MIN)
            {
                _b[0][axIdx] -= halfDelta;
                _b[1][axIdx] += halfDelta;
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

    vec3f aabb3f::min() const
    {
        return _b[0];
    }

    vec3f aabb3f::max() const
    {
        return _b[1];
    }

    aabb3f& aabb3f::operator+=(const aabb3f& other)
    {
        _b[0].x = std::min(other.min().x, _b[0].x);
        _b[0].y = std::min(other.min().y, _b[0].y);
        _b[0].z = std::min(other.min().z, _b[0].z);

        _b[1].x = std::max(other.max().x, _b[1].x);
        _b[1].y = std::max(other.max().y, _b[1].y);
        _b[1].z = std::max(other.max().z, _b[1].z);

        return *this;
    }

    aabb3f& aabb3f::operator+=(const vec3f& v)
    {
        _b[0].x = std::min(v.x, _b[0].x);
        _b[0].y = std::min(v.y, _b[0].y);
        _b[0].z = std::min(v.z, _b[0].z);

        _b[1].x = std::max(v.x, _b[1].x);
        _b[1].y = std::max(v.y, _b[1].y);
        _b[1].z = std::max(v.z, _b[1].z);

        return *this;
    }

    void aabb3f::reset()
    {
        _b[0] = vec3f(FLT_MAX);
        _b[1] = vec3f(-FLT_MAX);
    }

    aabb3f::aabb3f()
    {
        reset();
    }

    aabb3f::aabb3f(const vec3f& min, const vec3f& max)
    {
        _b[0] = min;
        _b[1] = max;
    }

    // END AABB3 ----------------------------------------------------------------

    // AABB4I -------------------------------------------------------------------
    void aabb4i::addPoint(const vec4i& pt, bool halfOpenInterval)
    {
        _b[0].x = std::min(pt.x, _b[0].x);
        _b[0].y = std::min(pt.y, _b[0].y);
        _b[0].z = std::min(pt.z, _b[0].z);
        _b[0].w = std::min(pt.w, _b[0].w);

        if (halfOpenInterval)
        {
            _b[1].x = std::max(pt.x + 1, _b[1].x);
            _b[1].y = std::max(pt.y + 1, _b[1].y);
            _b[1].z = std::max(pt.z + 1, _b[1].z);
            _b[1].w = std::max(pt.w + 1, _b[1].w);
        }
        else
        {
            _b[1].x = std::max(pt.x, _b[1].x);
            _b[1].y = std::max(pt.y, _b[1].y);
            _b[1].z = std::max(pt.z, _b[1].z);
            _b[1].w = std::max(pt.w, _b[1].w);
        }
    }

    vec4i aabb4i::dim() const
    {
        return max() - min();
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
            return !(max().x <= min().x || max().y <= min().y || max().z <= min().z || max().w <= min().w);
        }
        else
        {
            return !(max().x < min().x || max().y < min().y || max().z < min().z || max().w < min().w);
        }
    }

    void aabb4i::addAABB(const aabb4i& other)
    {
        _b[0].x = std::min(other.min().x, _b[0].x);
        _b[0].y = std::min(other.min().y, _b[0].y);
        _b[0].z = std::min(other.min().z, _b[0].z);
        _b[0].w = std::min(other.min().w, _b[0].w);

        _b[1].x = std::max(other.max().x, _b[1].x);
        _b[1].y = std::max(other.max().y, _b[1].y);
        _b[1].z = std::max(other.max().z, _b[1].z);
        _b[1].w = std::max(other.max().w, _b[1].w);
    }

    aabb4i aabb4i::intersect(const aabb4i& other) const
    {
        aabb4i result;
        result._b[0].x = std::max(_b[0].x, other.min().x);
        result._b[0].y = std::max(_b[0].y, other.min().y);
        result._b[0].z = std::max(_b[0].z, other.min().z);
        result._b[0].w = std::max(_b[0].w, other.min().w);

        result._b[1].x = std::min(_b[1].x, other.max().x);
        result._b[1].y = std::min(_b[1].y, other.max().y);
        result._b[1].z = std::min(_b[1].z, other.max().z);
        result._b[1].w = std::min(_b[1].w, other.max().w);

        return result;
    }

    aabb4i aabb4i::intersect(const vec4i& otherStart, const vec4i& otherEnd) const
    {
        aabb4i result;
        for (uint32_t cIdx = 0; cIdx < 4; cIdx++)
        {
            result._b[0][cIdx] = std::max(otherStart[cIdx], _b[0][cIdx]);
            result._b[1][cIdx] = std::min(otherEnd[cIdx], _b[1][cIdx]);
        }

        return result;
    }
    
    int aabb4i::volume(bool halfOpenInterval) const
    {
        vec4i d = dim();
        if (!halfOpenInterval)
            d += 1;

        return 2 * ((d.x * d.y * d.z) + (d.x * d.y * d.w) + (d.x * d.z * d.w) + (d.y * d.z * d.w));
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
            tDim = max() - min();
        }
        else
        {
            tDim = (max() + 1) - min();
        }
        
        return tDim.x * tDim.y * tDim.z * tDim.w;
    }

    void aabb4i::reset()
    {
        _b[0] = vec4i(INT_MAX);
        _b[1] = vec4i(INT_MIN);
    }

    vec4i& aabb4i::operator[](uint32_t idx)
    {
        return _b[idx];
    }

    vec4i aabb4i::operator[](uint32_t idx) const
    {
        return _b[idx];
    }

    vec4i aabb4i::min() const
    {
        return _b[0];
    }

    vec4i aabb4i::max() const
    {
        return _b[1];
    }

    aabb4i& aabb4i::operator+=(const aabb4i& other)
    {
        _b[0].x = std::min(other.min().x, _b[0].x);
        _b[0].y = std::min(other.min().y, _b[0].y);
        _b[0].z = std::min(other.min().z, _b[0].z);
        _b[0].w = std::min(other.min().w, _b[0].w);

        _b[1].x = std::max(other.max().x, _b[1].x);
        _b[1].y = std::max(other.max().y, _b[1].y);
        _b[1].z = std::max(other.max().z, _b[1].z);
        _b[1].w = std::max(other.max().w, _b[1].w);

        return *this;
    }

    aabb4i::aabb4i()
    {
        reset();
    }

    aabb4i::aabb4i(const vec4i& min, const vec4i& max)
    {
        _b[0] = min;
        _b[1] = max;
    }
    // END AABB4I ---------------------------------------------------------------

    // AABB4F -------------------------------------------------------------------
    void aabb4f::addPoint(const vec4f& pt)
    {
        _b[0].x = std::min(pt.x, _b[0].x);
        _b[0].y = std::min(pt.y, _b[0].y);
        _b[0].z = std::min(pt.z, _b[0].z);
        _b[0].w = std::min(pt.w, _b[0].w);

        _b[1].x = std::max(pt.x, _b[1].x);
        _b[1].y = std::max(pt.y, _b[1].y);
        _b[1].z = std::max(pt.z, _b[1].z);
        _b[1].w = std::max(pt.w, _b[1].w);
    }

    vec4f aabb4f::dim() const
    {
        return max() - min();
    }

    bool aabb4f::empty() const
    {
        vec4f theDim = dim();
        return (theDim.x <= 0.f || theDim.y <= 0.f || theDim.z <= 0.f || theDim.w <= 0.f);
    }

    bool aabb4f::isValid() const
    {
        return !(max().x < min().x || max().y < min().y || max().z < min().z || max().w < min().w);
    }

    void aabb4f::addAABB(const aabb4f& other)
    {
        _b[0].x = std::min(other.min().x, _b[0].x);
        _b[0].y = std::min(other.min().y, _b[0].y);
        _b[0].z = std::min(other.min().z, _b[0].z);
        _b[0].w = std::min(other.min().w, _b[0].w);

        _b[1].x = std::max(other.max().x, _b[1].x);
        _b[1].y = std::max(other.max().y, _b[1].y);
        _b[1].z = std::max(other.max().z, _b[1].z);
        _b[1].w = std::max(other.max().w, _b[1].w);
    }

    aabb4f aabb4f::intersect(const aabb4f& other) const
    {
        aabb4f result;
        result._b[0].x = std::max(_b[0].x, other.min().x);
        result._b[0].y = std::max(_b[0].y, other.min().y);
        result._b[0].z = std::max(_b[0].z, other.min().z);
        result._b[0].w = std::max(_b[0].w, other.min().w);

        result._b[1].x = std::min(_b[1].x, other.max().x);
        result._b[1].y = std::min(_b[1].y, other.max().y);
        result._b[1].z = std::min(_b[1].z, other.max().z);
        result._b[1].w = std::min(_b[1].w, other.max().w);

        return result;
    }
    
    float aabb4f::volume() const
    {
        vec4f d = dim();
        return 2.0f * ((d.x * d.y * d.z) + (d.x * d.y * d.w) + (d.x * d.z * d.w) + (d.y * d.z * d.w));
    }

    float aabb4f::bulk() const
    {
        if (!isValid())
        {
            return 0.0f;
        }
        
        return (max().x - min().x) * (max().y - min().y) * (max().z - min().z) * (max().w - min().w);
    }

    vec4f aabb4f::centroid() const
    {
        return (min() + max()) * 0.5f;
    }

    float aabb4f::centroid(uint32_t axis) const
    {
        return (min()[axis] + max()[axis]) * 0.5f;
    }

    void aabb4f::padToMin(float pad)
    {
        // adjust the AABB so that no side is narrower than some delta
        const float halfDelta = pad * 0.5f;
        const size_t nDimensions = 4;
        for (size_t axIdx = 0; axIdx < nDimensions; axIdx++)
        {
            if (_b[1][axIdx] - _b[0][axIdx] < AABB_MIN)
            {
                _b[0][axIdx] -= halfDelta;
                _b[1][axIdx] += halfDelta;
            }
        }
    }

    void aabb4f::reset()
    {
        _b[0] = vec4f(FLT_MAX);
        _b[1] = vec4f(-FLT_MAX);
    }

    vec4f& aabb4f::operator[](uint32_t idx)
    {
        return _b[idx];
    }

    vec4f aabb4f::operator[](uint32_t idx) const
    {
        return _b[idx];
    }

    vec4f aabb4f::min() const
    {
        return _b[0];
    }

    vec4f aabb4f::max() const
    {
        return _b[1];
    }

    aabb4f& aabb4f::operator+=(const aabb4f& other)
    {
        _b[0].x = std::min(other.min().x, _b[0].x);
        _b[0].y = std::min(other.min().y, _b[0].y);
        _b[0].z = std::min(other.min().z, _b[0].z);
        _b[0].w = std::min(other.min().w, _b[0].w);

        _b[1].x = std::max(other.max().x, _b[1].x);
        _b[1].y = std::max(other.max().y, _b[1].y);
        _b[1].z = std::max(other.max().z, _b[1].z);
        _b[1].w = std::max(other.max().w, _b[1].w);

        return *this;
    }

    aabb4f& aabb4f::operator+=(const vec4f& v)
    {
        _b[0].x = std::min(v.x, _b[0].x);
        _b[0].y = std::min(v.y, _b[0].y);
        _b[0].z = std::min(v.z, _b[0].z);
        _b[0].w = std::min(v.w, _b[0].w);

        _b[1].x = std::max(v.x, _b[1].x);
        _b[1].y = std::max(v.y, _b[1].y);
        _b[1].z = std::max(v.z, _b[1].z);
        _b[1].w = std::max(v.w, _b[1].w);

        return *this;
    }

    aabb4f::aabb4f()
    {
        reset();
    }

    aabb4f::aabb4f(const vec4f& min, const vec4f& max)
    {
        _b[0] = min;
        _b[1] = max;
    }

    aabb4f::aabb4f(const aabb4i& otheri)
    {
        _b[0] = vec4f(otheri.min());
        _b[1] = vec4f(otheri.max());
    }

    // END AABB4 ----------------------------------------------------------------
}