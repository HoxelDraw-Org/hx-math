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
    bool rotor4::operator==(const rotor4& other) const
    {
        return scalar == other.scalar
            && xy == other.xy
            && zx == other.zx
            && xw == other.xw
            && yz == other.yz
            && wy == other.wy
            && zw == other.zw;
    }

    bool rotor4::operator!=(const rotor4& other) const
    {
        return !(*this == other);
    }

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
        return *this * v;
    }

    rotor4& rotor4::fromTo(const vec4f& fromDir, const vec4f& toDir)
    {
        // normalize the vectors, just in case
        vec4f fromNorm = normalize(fromDir);
        vec4f toNorm = normalize(toDir);

        if (dot(fromNorm, toNorm) < -0.99999f)
        {
            // TODO: what's the best course of action here?
            std::printf("Invalid rotor: 180 degree rotation\n");
        }

        // get the normalized vector halfway between the to and from directions
        const vec4f halfDir = normalize(fromNorm + toNorm);

        // These two operations comprise the Geometric Product
        // Geometric Product of a and b = (a dot b) + (a wedge b)
        // dot product of the two vectors
        scalar = dot(fromNorm, halfDir);

        // compute the normalized "halfDir wedge fromDir" product
        xy = (halfDir.x * fromNorm.y) - (halfDir.y * fromNorm.x);
        zx = (halfDir.z * fromNorm.x) - (halfDir.x * fromNorm.z);
        xw = (halfDir.x * fromNorm.w) - (halfDir.w * fromNorm.x);
        yz = (halfDir.y * fromNorm.z) - (halfDir.z * fromNorm.y);
        wy = (halfDir.w * fromNorm.y) - (halfDir.y * fromNorm.w);
        zw = (halfDir.z * fromNorm.w) - (halfDir.w * fromNorm.z);

        return *this;
    }

    rotor4& rotor4::fromToTrig(const vec4f& fromDir, const vec4f& toDir)
    {
        // normalize the vectors, just in case
        vec4f fromNorm = normalize(fromDir);
        vec4f toNorm = normalize(toDir);

        if (dot(fromNorm, toNorm) < -0.99999f)
        {
            // TODO: what's the best course of action here?
            std::printf("Invalid rotor: 180 degree rotation\n");
        }
        
        // get the angle between the input directions
        const float fromDotTo = std::min(std::max(dot(fromNorm, toNorm), -1.0f), 1.0f);
        const float theta = std::acosf(fromDotTo);
        const float cosHalfTheta = std::cosf(theta * 0.5f);
        const float sinHalfTheta = std::sinf(theta * 0.5f);

        // compute the normalized "toDir wedge fromDir" product
        const float a = (toNorm.x * fromNorm.y) - (toNorm.y * fromNorm.x);
        const float b = (toNorm.z * fromNorm.x) - (toNorm.x * fromNorm.z);
        const float c = (toNorm.x * fromNorm.w) - (toNorm.w * fromNorm.x);
        const float d = (toNorm.y * fromNorm.z) - (toNorm.z * fromNorm.y);
        const float e = (toNorm.w * fromNorm.y) - (toNorm.y * fromNorm.w);
        const float f = (toNorm.z * fromNorm.w) - (toNorm.w * fromNorm.z);
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

    rotor4& rotor4::add(const rotor4& rotor)
    {
        /*
        = (s0t0 - s12t12 - s31t31 - s14t14 - s23t23 - s42t42 - s34t34)
		+ (s0t12 + s12t0 + s31t23 + s14t42 - s23t31 - s42t14)e12
		+ (s0t31 - s12t23 + s31t0 + s14t34 + s23t12 - s34t14)e31
		+ (s0t14 - s12t42 - s31t34 + s14t0 + s42t12 + s34t31)e14
		+ (s0t23 + s12t31 - s31t12 + s23t0 + s42t34 - s34t42)e23
		+ (s0t42 + s12t14 - s14t12 - s23t34 + s42t0 + s34t23)e42
		+ (s0t34 + s31t14 - s14t31 + s23t42 - s42t23 + s34t0)e34
		+ (s12t34 - s31t42 + s14t23 + s23t14 - s42t31 + s34t12)e1234
        */
        const float s = (scalar * rotor.scalar) - (xy * rotor.xy) - (zx * rotor.zx) - (xw * rotor.xw) - (yz * rotor.yz) - (wy * rotor.wy) - (zw * rotor.zw);
        const float e12 = (scalar * rotor.xy) + (xy * rotor.scalar) + (zx * rotor.yz) + (xw * rotor.wy) - (yz * rotor.zx) - (wy * rotor.xw);
        const float e31 = (scalar * rotor.zx) - (xy * rotor.yz) + (zx * rotor.scalar) + (xw * rotor.zw) + (yz * rotor.xy) - (zw * rotor.xw);
        const float e14 = (scalar * rotor.xw) - (xy * rotor.wy) - (zx * rotor.zw) + (xw * rotor.scalar) + (wy * rotor.xy) + (zw * rotor.zx);
        const float e23 = (scalar * rotor.yz) + (xy * rotor.zx) - (zx * rotor.xy) + (yz * rotor.scalar) + (wy * rotor.zw) - (zw * rotor.wy);
        const float e42 = (scalar * rotor.wy) + (xy * rotor.xw) - (xw * rotor.xy) - (yz * rotor.zw) + (wy * rotor.scalar) + (zw * rotor.yz);
        const float e34 = (scalar * rotor.zw) + (zx * rotor.xw) - (xw * rotor.zx) + (yz * rotor.wy) - (wy * rotor.yz) + (zw * rotor.scalar);
        // e1234 cancels out to zero
        //const float e1234 = (xy * rotor.zw) - (zx * rotor.wy) + (xw * rotor.yz) + (yz * rotor.xw) - (wy * rotor.zx) + (zw * rotor.xy);

        scalar = s;
        xy = e12;
        zx = e31;
        xw = e14;
        yz = e23;
        wy = e42;
        zw = e34;
        //xyzw = e1234;

        return *this;
    }

    rotor4 rotor4::operator*(const rotor4& other) const
    {
        /*
        = (s0t0 - s12t12 - s31t31 - s14t14 - s23t23 - s42t42 - s34t34)
        + (s0t12 + s12t0 + s31t23 + s14t42 - s23t31 - s42t14)e12
        + (s0t31 - s12t23 + s31t0 + s14t34 + s23t12 - s34t14)e31
        + (s0t14 - s12t42 - s31t34 + s14t0 + s42t12 + s34t31)e14
        + (s0t23 + s12t31 - s31t12 + s23t0 + s42t34 - s34t42)e23
        + (s0t42 + s12t14 - s14t12 - s23t34 + s42t0 + s34t23)e42
        + (s0t34 + s31t14 - s14t31 + s23t42 - s42t23 + s34t0)e34
        + (s12t34 - s31t42 + s14t23 + s23t14 - s42t31 + s34t12)e1234
        */
        const float s = (scalar * other.scalar) - (xy * other.xy) - (zx * other.zx) - (xw * other.xw) - (yz * other.yz) - (wy * other.wy) - (zw * other.zw);
        const float e12 = (scalar * other.xy) + (xy * other.scalar) + (zx * other.yz) + (xw * other.wy) - (yz * other.zx) - (wy * other.xw);
        const float e31 = (scalar * other.zx) - (xy * other.yz) + (zx * other.scalar) + (xw * other.zw) + (yz * other.xy) - (zw * other.xw);
        const float e14 = (scalar * other.xw) - (xy * other.wy) - (zx * other.zw) + (xw * other.scalar) + (wy * other.xy) + (zw * other.zx);
        const float e23 = (scalar * other.yz) + (xy * other.zx) - (zx * other.xy) + (yz * other.scalar) + (wy * other.zw) - (zw * other.wy);
        const float e42 = (scalar * other.wy) + (xy * other.xw) - (xw * other.xy) - (yz * other.zw) + (wy * other.scalar) + (zw * other.yz);
        const float e34 = (scalar * other.zw) + (zx * other.xw) - (xw * other.zx) + (yz * other.wy) - (wy * other.yz) + (zw * other.scalar);
        // e1234 cancels out to zero
        //const float e1234 = (xy * other.zw) - (zx * other.wy) + (xw * other.yz) + (yz * other.xw) - (wy * other.zx) + (zw * other.xy);

        return rotor4(s, e12, e31, e14, e23, e42, e34);
    }

    vec4f rotor4::operator*(const vec4f& v) const
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
        result.x = (s1 * scalar) + (s2 * xy) - (s3 * zx) + (s4 * xw) + (s123 * yz) - (s124 * wy) + (s134 * zw);
        result.y = -(s1 * xy) + (s2 * scalar) + (s3 * yz) - (s4 * wy) + (s123 * zx) - (s124 * xw) + (s234 * zw);
        result.z = (s1 * zx) - (s2 * yz) + (s3 * scalar) + (s4 * zw) + (s123 * xy) - (s134 * xw) + (s234 * wy);
        result.w = -(s1 * xw) + (s2 * wy) - (s3 * zw) + (s4 * scalar) + (s124 * xy) - (s134 * zx) + (s234 * yz);
        return result;
    }

    Mat5 rotor4::matrix() const
    {
        // TODO: optimize this transform section since most values are 0?
        const vec4f newX = transform(vec4f(1, 0, 0, 0));
        const vec4f newY = transform(vec4f(0, 1, 0, 0));
        const vec4f newZ = transform(vec4f(0, 0, 1, 0));
        const vec4f newW = transform(vec4f(0, 0, 0, 1));

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
        // the identity rotor
        scalar = 1.0f;
        xy = zx = xw = yz = wy = zw = 0.0f;
        //xyz = xyw = xzw = yzw = 0.0f;
        //xyzw = 0.0f;
    }

    rotor4::rotor4(float scalar, float xy, float zx, float xw, float yz, float wy, float zw) : scalar(scalar), xy(xy), zx(zx), xw(xw), yz(yz), wy(wy), zw(zw) {}

    rotor4::rotor4(const vec4f& fromDir, const vec4f& toDir)
    {
        fromTo(fromDir, toDir);
    }

    rotor4::~rotor4() {}

    // END rotor4 ---------------------------------------------------------------
}