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
    class rotor4
    {
    // Members
    private:
    protected:
    public:
        float scalar;
        float xy;
        float xz;
        float xw;
        float yz;
        float yw;
        float zw;

    // Functions
    private:
    protected:
    public:
        rotor4 operator-() const;

        rotor4& reverse();

        vec4f transform(const vec4f& v) const;

        rotor4& fromTo(const vec4f& fromDir, const vec4f& toDir);
        rotor4& fromToTrig(const vec4f& fromDir, const vec4f& toDir);

        Mat5 matrix() const;

        rotor4();
        rotor4(float scalar, float xy, float xz, float xw, float yz, float yw, float zw);
        rotor4(const vec4f& fromDir, const vec4f& toDir);
        ~rotor4();
    };

    /*
    inline rotor4 reversed(const rotor4& r)
    {
        // TODO
    }
    */
}