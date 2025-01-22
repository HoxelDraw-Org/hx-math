/*
rotor.h
January 17, 2025
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"
#include "mat.h"

namespace hxm
{
    // ROTOR3 -----------------------------------------------------------------
    class rotor3
    {
        // BIG TODO
    };


    // ROTOR4 -----------------------------------------------------------------
    class rotor4
    {
    // Members
    private:
    protected:
    public:
        float scalar;
        float xy;
        float zx;
        float xw;
        float yz;
        float wy;
        float zw;

        // TODO: do we need the trivector parts for anything at all?
        //float xyz;
        //float xyw;
        //float xzw;
        //float yzw;

        // and there might also be a quadvector part?
        // float xyzw is always 0

    // Functions
    private:
    protected:
    public:
        rotor4 operator-() const;

        rotor4& reverse();

        vec4f transform(const vec4f& v) const;

        rotor4& fromTo(const vec4f& fromDir, const vec4f& toDir);
        rotor4& fromToTrig(const vec4f& fromDir, const vec4f& toDir);

        // NOTE: rotor multiplying works the same way as column-major matrix multiplication, from right to left
        // i.e. "rotor2 * rotor1 * pt"  means rotate pt by rotor1 first, then by rotor2 second
        // append/combine/multiply two rotors
        rotor4& add(const rotor4& rotor);

        // TODO: use operator*() syntax for both combining rotors and transforming vectors

        Mat5 matrix() const;

        rotor4();
        rotor4(float scalar, float xy, float zx, float xw, float yz, float wy, float zw);
        rotor4(const vec4f& fromDir, const vec4f& toDir);
        ~rotor4();
    };

    inline rotor4 reverse(const rotor4& r)
    {
        return -r;
    }

    // TODO:
    // lerp between two rotor4s
    // convert Euler6 to Rotor4
    // convert Rotor4 to Euler6?
}