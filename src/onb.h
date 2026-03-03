/*
onb.h
December 19, 2025
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"
#include "mat.h"

namespace hxm
{
    // ONB3 -----------------------------------------------------------------
    // Building an Orthonormal Basis, Revised - JCGT Vol. 6, No. 1, 2017
    //      Duff, Burgess, Christensen, Hery, Kensler, Liani, and Villemin
    // This assumes that `in` is normalized
    void makeONB3(const vec3f& in, vec3f& out_v0, vec3f& out_v1)
    {
        // branchless version
        float sign = std::copysign(1.f, in.z);
        const float a = -1.f / (sign + in.z);
        const float b = in.x * in.y * a;
        out_v0 = vec3f(1.f + sign * in.x * in.x * a, sign * b, -sign * in.x);
        out_v1 = vec3f(b, sign + in.y * in.y * a, -in.y);
    }

    // ONB4 -----------------------------------------------------------------
    // This uses an optimized rotor rotation to build an ONB
    //  The w-vector (0,0,0,1) is rotated to the input vector,
    //      then the same rotation is applied to the other principal axes to rotate the whole coordinate frame
    // This assumes that `in` is normalized
    void makeONB4(const vec4f& in, vec4f& out_v0, vec4f& out_v1, vec4f& out_v2)
    {
        // Handle w < 0: flip terms if w is negative
        const float sign = std::copysign(1.f, in.w);

        const vec4f fromNorm = vec4f(0, 0, 0, sign);

        // get the normalized vector halfway between the to and from directions
        const vec4f halfDir = normalize(fromNorm + in);

        const float scalar = halfDir.w * sign;
        const float xw = halfDir.x * sign;
        const float wy = -halfDir.y * sign;
        const float zw = halfDir.z * sign;

        // x-column: v=(1,0,0,0)
        out_v0.x = sign * ((scalar * scalar) + ((-xw) * xw) - ((-wy) * wy) + (zw * zw));
        out_v0.y = sign * (-((-xw) * wy) - ((-wy) * xw));
        out_v0.z = sign * (((-xw) * zw) - (zw * xw));
        out_v0.w = sign * (-(scalar * xw) + ((-xw) * scalar));

        // y-column: v=(0,1,0,0)
        out_v1.x = sign * ((wy * xw) - ((-xw) * wy));
        out_v1.y = sign * ((scalar * scalar) - (wy * wy) - ((-xw) * xw) + (zw * zw));
        out_v1.z = sign * ((wy * zw) + (zw * wy));
        out_v1.w = sign * ((scalar * wy) + (wy * scalar));

        // z-column: v=(0,0,1,0)
        out_v2.x = sign * (((-zw) * xw) + ((-xw) * zw));
        out_v2.y = sign * (-((-zw) * wy) + (wy * zw));
        out_v2.z = sign * ((scalar * scalar) + ((-zw) * zw) - ((-xw) * xw) + (wy * wy));
        out_v2.w = sign * (-(scalar * zw) + ((-zw) * scalar));

        // SHOULD BE EQUAL TO THE INPUT VECTOR
        // w-column: v=(0,0,0,1)
        //out_v3.x = sign * ((xw * scalar) + (scalar * xw));
        //out_v3.y = sign * (((-wy) * scalar) - (scalar * wy));
        //out_v3.z = sign * ((zw * scalar) + (scalar * zw));
        //out_v3.w = sign * (-(xw * xw) + ((-wy) * wy) - (zw * zw) + (scalar * scalar));
    }
}