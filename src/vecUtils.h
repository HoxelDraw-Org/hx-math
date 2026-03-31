/*
vecUtils.h
March 2026
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"

namespace hxm
{
    // TODO: standardize this API as well
    // the index of the smallest component of this vector
    inline uint32_t minIdx(const vec2f& v)
    {
        uint32_t minIdx = 0;
        float minVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 2; idx++)
        {
            // don't consider components with -infinity values
            if (!std::isinf(v[idx]) && v[idx] < minVal)
            {
                minIdx = idx;
                minVal = v[idx];
            }
        }

        return minIdx;
    }

    // the index of the largest component of this vector
    inline uint32_t maxIdx(const vec2f& v)
    {
        uint32_t maxIdx = 0;
        float maxVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 2; idx++)
        {
            // don't consider components with infinity values
            if (!std::isinf(v[idx]) && v[idx] > maxVal)
            {
                maxIdx = idx;
                maxVal = v[idx];
            }
        }

        return maxIdx;
    }



    inline uint32_t minIdx(const vec3f& v)
    {
        uint32_t minIdx = 0;
        float minVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 3; idx++)
        {
            // don't consider components with -infinity values
            if (!std::isinf(v[idx]) && v[idx] < minVal)
            {
                minIdx = idx;
                minVal = v[idx];
            }
        }

        return minIdx;
    }

    inline uint32_t maxIdx(const vec3f& v)
    {
        uint32_t maxIdx = 0;
        float maxVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 3; idx++)
        {
            // don't consider components with infinity values
            if (!std::isinf(v[idx]) && v[idx] > maxVal)
            {
                maxIdx = idx;
                maxVal = v[idx];
            }
        }

        return maxIdx;
    }


    inline int32_t firstNonZeroComp(const vec4i& v)
    {
        for (int idx = 0; idx < 4; idx++)
        {
            if (v[idx] != 0)
            {
                return idx;
            }
        }

        return -1;
    }


    inline uint32_t numEqualComps(const vec4u& a, const vec4u& b)
    {
        size_t result = 0;
        result += a.x == b.x ? 1 : 0;
        result += a.y == b.y ? 1 : 0;
        result += a.z == b.z ? 1 : 0;
        result += a.w == b.w ? 1 : 0;
        return result;
    }


    inline uint32_t minIdx(const vec4f& v)
    {
        uint32_t minIdx = 0;
        float minVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 4; idx++)
        {
            // don't consider components with -infinity values
            if (!std::isinf(v[idx]) && v[idx] < minVal)
            {
                minIdx = idx;
                minVal = v[idx];
            }
        }

        return minIdx;
    }

    inline uint32_t maxIdx(const vec4f& v)
    {
        uint32_t maxIdx = 0;
        float maxVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 4; idx++)
        {
            // don't consider components with infinity values
            if (!std::isinf(v[idx]) && v[idx] > maxVal)
            {
                maxIdx = idx;
                maxVal = v[idx];
            }
        }

        return maxIdx;
    }


    inline uint32_t minIdx(const vec5f& v)
    {
        uint32_t minIdx = 0;
        float minVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 5; idx++)
        {
            // don't consider components with -infinity values
            if (!std::isinf(v[idx]) && v[idx] < minVal)
            {
                minIdx = idx;
                minVal = v[idx];
            }
        }

        return minIdx;
    }

    inline uint32_t maxIdx(const vec5f& v)
    {
        uint32_t maxIdx = 0;
        float maxVal = FLT_MAX;
        for (uint32_t idx = 0; idx < 5; idx++)
        {
            // don't consider components with infinity values
            if (!std::isinf(v[idx]) && v[idx] > maxVal)
            {
                maxIdx = idx;
                maxVal = v[idx];
            }
        }

        return maxIdx;
    }


    inline int32_t firstNonZeroComp(const vec5i& v)
    {
        for (int idx = 0; idx < 5; idx++)
        {
            if (v[idx] != 0)
            {
                return idx;
            }
        }

        return -1;
    }
}
