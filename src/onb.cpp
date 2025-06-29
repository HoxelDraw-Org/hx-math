/*
onb.cpp
October 2024
Copyright Justin Jensen
*/

#include "onb.h"

namespace hxm
{
    inline vec4u onb::sortAbsAsc(const vec4f& v) const
    {
        // sort absolute values of x, y, z, and w, ascending
        float v0 = std::fabsf(v.x);
        float v1 = std::fabsf(v.y);
        float v2 = std::fabsf(v.z);
        float v3 = std::fabsf(v.w);
        int idx0 = 0;
        int idx1 = 1;
        int idx2 = 2;
        int idx3 = 3;

        // sort elements smallest to largest
        // 0-2
        if (v0 > v2)
        {
            std::swap(v0, v2);
            std::swap(idx0, idx2);
        }

        // 1-3
        if (v1 > v3)
        {
            std::swap(v1, v3);
            std::swap(idx1, idx3);
        }

        // 0-1
        if (v0 > v1)
        {
            std::swap(v0, v1);
            std::swap(idx0, idx1);
        }

        // 2-3
        if (v2 > v3)
        {
            std::swap(v2, v3);
            std::swap(idx2, idx3);
        }

        // 1-2
        if (v1 > v2)
        {
            std::swap(v1, v2);
            std::swap(idx1, idx2);
        }

        return vec4u(idx0, idx1, idx2, idx3);
    }

    // emperically determined to be pretty darn good at finding a pair of non-parallel vectors that are also not parallel to the input vector
    // 10,000,000 random vectors in [-1,1] produced zero results that had a dot product of > 0.99
    inline void onb::makeTwoNonParallel(const vec4f& v, vec4f& out_a, vec4f& out_b) const
    {
        // sort x, y, z, and w
        vec4u idxSorted = sortAbsAsc(v);

        // out_a is 0 everywhere except for v's smallest value, which is set to v's largest value
        out_a = 0;
        out_a[idxSorted[0]] = v[idxSorted[3]];

        // out_b is 0 everywhere except for v's second-smallest value, which is set to v's largest value
        out_b = 0;
        out_b[idxSorted[1]] = v[idxSorted[3]];
    }

    inline void onb::init(const vec4f& n, const vec4f& np1, const vec4f& np2)
    {
        _t = normalize(n);	// up or something
        _u = normalize(cross4(np1, np2, _t));	// right or something
        //vec4f B = normalize(cross4(nonParallel2, _t, _u));	// up or something
        _v = normalize(cross4(np2, _u, _t));	// up or something
        _s = cross4(_t, _u, _v);	// over or something
    }

    vec4f onb::transform(const vec4f& v) const
    {
        // Transform v out of basis space into local space
        return (v.x * _u) + (v.y * _v) + (v.z * _s) + (v.w * _t);
    }

    void onb::init_Shirley(const vec4f& norm)
    {
        _t = normalize(norm);	// up or something
        vec4f np1, np2;
        if (std::fabs(_t.x) > 0.9f)
        {
            np1 = vec4f(0, 1, 0, 0);
        }
        else
        {
            np1 = vec4f(1, 0, 0, 0);
        }

        if (std::fabs(_t.z) > 0.9f)
        {
            np2 = vec4f(0, 0, 0, 1);
        }
        else
        {
            np2 = vec4f(0, 0, 1, 0);
        }

        init(norm, np1, np2);
    }

    onb::onb(const vec4f& norm)
    {
        // Steve Hollasch thesis, section 4.3
        // 4D TODO: y-up and right-handed?
        // create basis vectors
        _t = normalize(norm);	// up or something
        vec4f nonParallel1, nonParallel2;

        // make two vectors that are not parallel to either each other or the normal
        makeTwoNonParallel(_t, nonParallel1, nonParallel2);

        // see if the two new vectors are actually not parallel to the normal or to each other
        // TODO: remove
        /*
        {
            vec4f npNorm1 = normalize(nonParallel1);
            vec4f npNorm2 = normalize(nonParallel2);

            float dot1 = std::fabsf(dot(_t, npNorm1));
            if (dot1 > 0.999f)
            {
                std::printf("todoremove: THEY WEREN'T ACTUALLY NON-PARALLEL 1\n");
            }

            float dot2 = std::fabsf(dot(_t, npNorm1));
            if (dot2 > 0.999f)
            {
                std::printf("todoremove: THEY WEREN'T ACTUALLY NON-PARALLEL 2\n");
            }

            float dot3 = std::fabsf(dot(npNorm1, npNorm2));
            if (dot3 > 0.999f)
            {
                std::printf("todoremove: THEY WEREN'T ACTUALLY NON-PARALLEL 3\n");
            }
        }
        */

        init(_t, nonParallel1, nonParallel2);
    }

    onb::onb()
    {
        init(vec4f(0, 0, 1, 0), vec4f(1, 0, 0, 0), vec4f(0, 1, 0, 0));
    }
}
