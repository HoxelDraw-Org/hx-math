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
        return { scalar, -xy, -zx, -xw, -yz, -wy, -zw };
    }

    rotor4& rotor4::reverse()
    {
        // scalar = scalar;
        xy = -xy;
        zx = -zx;
        xw = -xw;
        yz = -yz;
        wy = -wy;
        zw = -zw;
        return *this;
    }

    vec4f rotor4::transform(const vec4f& v) const
    {
        // perform the 4D rotor sandwich operation
        /*
        r0: rotor.scalar
        r12: rotor.XY
        v1: vector.x

        s1 =	(r0v1 + r12v2 - r31v3 + r14v4)
        s2 =	(r0v2 - r12v1 + r23v3 - r42v4)
        s3 =	(r0v3 + r31v1 - r23v2 + r34v4)
        s4 =	(r0v4 - r14v1 + r42v2 - r34v3)
        s123 =	(r12v3 + r31v2 + r23v1)
        s124 =	(r12v4 - r14v2 - r42v1)
        s134 =	(-r31v4 - r14v3 + r34v1)
        s234 =	(r23v4 + r42v3 + r34v2)

        */
        float s1 = (scalar * v.x) + (xy * v.y) - (zx * v.z) + (xw * v.w);
        float s2 = (scalar * v.y) - (xy * v.x) + (yz * v.z) - (wy * v.w);
        float s3 = (scalar * v.z) + (zx * v.x) - (yz * v.y) + (zw * v.w);
        float s4 = (scalar * v.w) - (xw * v.x) + (wy * v.y) - (zw * v.z);
        float s123 = (xy * v.z) + (zx * v.y) + (yz * v.x);
        float s124 = (xy * v.w) - (xw * v.y) - (wy * v.x);
        float s134 = -(zx * v.w) - (xw * v.z) + (zw * v.x);
        float s234 = (yz * v.w) + (wy * v.z) + (zw * v.y);

        /*
        v'.x =  s1r0 + s2r12 - s3r31 + s4r14 + s123r23 - s124r42 + s134r34
        v'.y = -s1r12 + s2r0 + s3r23 - s4r42 + s123r31 - s124r14 + s234r34
        v'.z =  s1r31 - s2r23 + s3r0 + s4r34 + s123r12 - s134r14 + s234r42
        v'.w = -s1r14 + s2r42 - s3r34 + s4r0 + s124r12 - s134r31 + s234r23
        */

        vec4f result;
        result.x =  (s1 * scalar) + (s2 * xy) - (s3 * zx) + (s4 * xw) + (s123 * yz) - (s124 * wy) + (s134 * zw);
        result.y = -(s1 * xy) + (s2 * scalar) + (s3 * yz) - (s4 * wy) + (s123 * zx) - (s124 * xw) + (s234 * zw);
        result.z =  (s1 * zx) - (s2 * yz) + (s3 * scalar) + (s4 * zw) + (s123 * xy) - (s134 * xw) + (s234 * wy);
        result.w = -(s1 * xw) + (s2 * wy) - (s3 * zw) + (s4 * scalar) + (s124 * xy) - (s134 * zx) + (s234 * yz);
        return result;
    }

    rotor4& rotor4::fromTo(const vec4f& fromDir, const vec4f& toDir)
    {
        // normalize the vectors and determine whether we need trig or not
        vec4f fromNorm = normalize(fromDir);
        vec4f toNorm = normalize(toDir);

        if (dot(fromNorm, toNorm) < -0.99f)
        {
            return fromToTrig(fromNorm, toNorm);
        }

        // get the normalized vector halfway between the to and from directions
        const vec4f halfDir = normalize(fromNorm + toNorm);

        // compute the normalized "halfDir wedge fromDir" product
        const float a = (halfDir.x * fromNorm.y) - (halfDir.y * fromNorm.x);
        const float b = (halfDir.x * fromNorm.z) - (halfDir.z * fromNorm.x);
        const float c = (halfDir.x * fromNorm.w) - (halfDir.w * fromNorm.x);
        const float d = (halfDir.y * fromNorm.z) - (halfDir.z * fromNorm.y);
        const float e = (halfDir.y * fromNorm.w) - (halfDir.w * fromNorm.y);
        const float f = (halfDir.z * fromNorm.w) - (halfDir.w * fromNorm.z);
        const float len = std::sqrtf((a * a) + (b * b) + (c * c) + (d * d) + (e * e) + (f * f));

        scalar = dot(fromNorm, halfDir);
        xy = a / len;
        zx = b / len;
        xw = c / len;
        yz = d / len;
        wy = e / len;
        zw = f / len;

        return *this;
    }

    rotor4& rotor4::fromToTrig(const vec4f& fromDirNorm, const vec4f& toDirNorm)
    {
        // These calculations assume fromDir and toDir are normalized
        
        // get the angle between the input directions
        const float fromDotTo = std::min(std::max(dot(fromDirNorm, toDirNorm), -1.0f), 1.0f);
        const float theta = std::acosf(fromDotTo);
        const float cosHalfTheta = std::cosf(theta * 0.5f);
        const float sinHalfTheta = std::sinf(theta * 0.5f);

        // compute the normalized "toDir wedge fromDir" product
        const float a = (toDirNorm.x * fromDirNorm.y) - (toDirNorm.y * fromDirNorm.x);
        const float b = (toDirNorm.x * fromDirNorm.z) - (toDirNorm.z * fromDirNorm.x);
        const float c = (toDirNorm.x * fromDirNorm.w) - (toDirNorm.w * fromDirNorm.x);
        const float d = (toDirNorm.y * fromDirNorm.z) - (toDirNorm.z * fromDirNorm.y);
        const float e = (toDirNorm.y * fromDirNorm.w) - (toDirNorm.w * fromDirNorm.y);
        const float f = (toDirNorm.z * fromDirNorm.w) - (toDirNorm.w * fromDirNorm.z);
        const float len = std::sqrtf((a * a) + (b * b) + (c * c) + (d * d) + (e * e) + (f * f));

        scalar = cosHalfTheta;
        xy = sinHalfTheta * (a / len);
        zx = sinHalfTheta * (b / len);
        xw = sinHalfTheta * (c / len);
        yz = sinHalfTheta * (d / len);
        wy = sinHalfTheta * (e / len);
        zw = sinHalfTheta * (f / len);

        return *this;
    }

    Mat5 rotor4::matrix() const
    {
        // TODO: optimize this transform section since most values are 0?
        const vec4f newX = transform(vec4f(1, 0, 0, 0));
        const vec4f newY = transform(vec4f(0, 1, 0, 0));
        const vec4f newZ = transform(vec4f(0, 0, 1, 0));
        const vec4f newW = transform(vec4f(0, 0, 0, 1));

        // TODO: do we need to transpose this matrix?
        Mat5 result;
        result.set( newX[0], newY[0], newZ[0], newW[0], 0,
                    newX[1], newY[1], newZ[1], newW[1], 0,
                    newX[2], newY[2], newZ[2], newW[2], 0,
                    newX[3], newY[3], newZ[3], newW[3], 0,
                    0, 0, 0, 0, 1);
        return result;
    }

    rotor4::rotor4()
    {
        scalar = xy = zx = xw = yz = wy = zw = 0.0f;
        xyz = xyw = xzw = yzw = 0.0f;
    }

    rotor4::rotor4(float scalar, float xy, float zx, float xw, float yz, float yw, float zw) : scalar(scalar), xy(xy), zx(zx), xw(xw), yz(yz), wy(wy), zw(zw) {}

    rotor4::rotor4(const vec4f& fromDir, const vec4f& toDir)
    {
        fromTo(fromDir, toDir);
    }

    rotor4::~rotor4() {}

    // END rotor4 ---------------------------------------------------------------
}