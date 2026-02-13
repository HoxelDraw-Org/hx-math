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
    // BIG TODO



    // ONB4 -----------------------------------------------------------------
    void makeONB4(const vec4f& in, vec4f& out_v0, vec4f& out_v1, vec4f& out_v2, vec4f& out_v3)
    {
        // normalize the vectors, just in case
        vec4f fromNorm = vec4f(0, 0, 0, 1);
        vec4f toNorm = normalize(in);

        // TODO: handle w < 0
            // I think we just need the fromNorm to be {0,0,0,-1} AND
            // we'll assume rotation in the XW plane so we'll need to set +X to -X now

        // get the normalized vector halfway between the to and from directions
        const vec4f halfDir = normalize(fromNorm + toNorm);

        float scalar = halfDir.w;

        float xw = halfDir.x;
        float wy = -halfDir.y;
        float zw = halfDir.z;

        // x-column: v=(1,0,0,0)
        out_v0.x = (scalar * scalar) + ((-xw) * xw) - ((-wy) * wy) + (zw * zw);
        out_v0.y = -((-xw) * wy) - ((-wy) * xw);
        out_v0.z = ((-xw) * zw) - (zw * xw);
        out_v0.w = -(scalar * xw) + ((-xw) * scalar);

        // y-column: v=(0,1,0,0)
        out_v1.x = (wy * xw) - ((-xw) * wy);
        out_v1.y = (scalar * scalar) - (wy * wy) - ((-xw) * xw) + (zw * zw);
        out_v1.z = (wy * zw) + (zw * wy);
        out_v1.w = (scalar * wy) + (wy * scalar);

        // z-column: v=(0,0,1,0)
        out_v2.x = ((-zw) * xw) + ((-xw) * zw);
        out_v2.y = -((-zw) * wy) + (wy * zw);
        out_v2.z = (scalar * scalar) + ((-zw) * zw) - ((-xw) * xw) + (wy * wy);
        out_v2.w = -(scalar * zw) + ((-zw) * scalar);

        // w-column: v=(0,0,0,1)
        out_v3.x = (xw * scalar) + (scalar * xw);
        out_v3.y = ((-wy) * scalar) - (scalar * wy);
        out_v3.z = (zw * scalar) + (scalar * zw);
        out_v3.w = -(xw * xw) + ((-wy) * wy) - (zw * zw) + (scalar * scalar);
    }
}