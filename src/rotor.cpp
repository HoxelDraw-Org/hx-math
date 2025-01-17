/*
rotor.cpp
January 17, 2025
Contributors:
Justin Jensen
*/

#include "rotor.h"

namespace hxm
{
    // rotor4 -------------------------------------------------------------------
    rotor4 rotor4::operator-() const
    {
        return { scalar, -xy, -xz, -xw, -yz, -yw, -zw };
    }

    rotor4& rotor4::reverse()
    {
        xy = -xy;
        xz = -xz;
        xw = -xw;
        yz = -yz;
        yw = -yw;
        zw = -zw;
        return *this;
    }

    vec4f rotor4::transform(const vec4f& v) const
    {
        // TODO: perform the 4D rotor sandwich operation
        return vec4f();
    }

    rotor4& rotor4::fromTo(const vec4f& fromDir, const vec4f& toDir)
    {
        // normalize the vectors and determine whether we need trig or not
        vec4f fromNorm = normalize(fromDir);
        vec4f toNorm = normalize(toDir);
    }

    rotor4& rotor4::fromToTrig(const vec4f& fromDir, const vec4f& toDir)
    {
        // TODO: insert return statement here
    }

    Mat5 rotor4::matrix() const
    {
        // TODO
        return Mat5();
    }

    rotor4::rotor4()
    {
        scalar = xy = xz = xw = yz = yw = zw = 0.0f;
    }

    rotor4::rotor4(float scalar, float xy, float xz, float xw, float yz, float yw, float zw) : scalar(scalar), xy(xy), xz(xz), xw(xw), yz(yz), yw(yw), zw(zw) {}

    rotor4::rotor4(const vec4f& fromDir, const vec4f& toDir)
    {
        // TODO
    }

    rotor4::~rotor4() {}

    // END rotor4 ---------------------------------------------------------------
}