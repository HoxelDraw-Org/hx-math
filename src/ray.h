/*
ray.h
September 29, 2022
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"
#include "mat.h"

namespace hxm
{
    class ray3
    {
    // Members
    private:
    protected:
    public:
        vec3f orig;
        vec3f dir;

        int sign[3];
        vec3f invDir;

    // Functions
    private:
    protected:
    public:
        vec3f getPoint(float dist) const
        { return orig + (dir * dist); }

        ray3() : orig(0), dir(0), invDir(0)
        {
            sign[0] = 0;
            sign[1] = 0;
            sign[2] = 0;
        }
        ray3(const vec3f& orig, const vec3f& dir) : orig(orig), dir(dir)
        {
            invDir = 1.0f / dir;
            sign[0] = int(invDir.x >= 0);
            sign[1] = int(invDir.y >= 0);
            sign[2] = int(invDir.z >= 0);
        }
        ~ray3() {};
    };

    inline ray3 operator*(const Mat4& m, const ray3& ray) {
        vec3f newOrig(0);
        vec3f newDir(0);

        // multiply the origin by the matrix as a point (5th component: 1.0)
        float oX = ray.orig.x;
        float oY = ray.orig.y;
        float oZ = ray.orig.z;
        newOrig.x = (m[0] * oX) + (m[4] * oY) + (m[8] * oZ) + m[12];
        newOrig.y = (m[1] * oX) + (m[5] * oY) + (m[9] * oZ) + m[13];
        newOrig.z = (m[2] * oX) + (m[6] * oY) + (m[10] * oZ) + m[14];
        //newOrig.w = (m[3] * oX) + (m[7] * oY) + (m[11] * oZ) + m[15];

        // multiply the direction by the matrix as a vector (4th component: 0.0)
        float dX = ray.dir.x;
        float dY = ray.dir.y;
        float dZ = ray.dir.z;
        newDir.x = (m[0] * dX) + (m[4] * dY) + (m[8] * dZ) + m[12];
        newDir.y = (m[1] * dX) + (m[5] * dY) + (m[9] * dZ) + m[13];
        newDir.z = (m[2] * dX) + (m[6] * dY) + (m[10] * dZ) + m[14];
        //newDir.w = (m[3] * dX) + (m[7] * dY) + (m[11] * dZ) + m[15];

        return ray3(newOrig, newDir);
    }

    class ray4
    {
    // Members
    private:
    protected:
    public:
        vec4f orig;
        vec4f dir;

        int sign[4];
        vec4f invDir;

    // Functions
    private:
    protected:
    public:
        vec4f getPoint(float dist) const
        { return orig + (dir * dist); }

        ray4() : orig(0), dir(0), invDir(0)
        {
            sign[0] = 0;
            sign[1] = 0;
            sign[2] = 0;
            sign[3] = 0;
        }
        ray4(const vec4f& orig, const vec4f& dir) : orig(orig), dir(dir)
        {
            invDir = 1.0f / dir;
            sign[0] = int(invDir.x >= 0);
            sign[1] = int(invDir.y >= 0);
            sign[2] = int(invDir.z >= 0);
            sign[3] = int(invDir.w >= 0);
        }
        ~ray4() {};
    };

    inline ray4 operator*(const Mat5& m, const ray4& ray) {
        vec4f newOrig(0);
        vec4f newDir(0);

        // multiply the origin by the matrix as a point (5th component: 1.0)
        float oX = ray.orig.x;
        float oY = ray.orig.y;
        float oZ = ray.orig.z;
        float oW = ray.orig.w;
        newOrig.x = (m[0] * oX) + (m[5] * oY) + (m[10] * oZ) + (m[15] * oW) + m[20];
        newOrig.y = (m[1] * oX) + (m[6] * oY) + (m[11] * oZ) + (m[16] * oW) + m[21];
        newOrig.z = (m[2] * oX) + (m[7] * oY) + (m[12] * oZ) + (m[17] * oW) + m[22];
        newOrig.w = (m[3] * oX) + (m[8] * oY) + (m[13] * oZ) + (m[18] * oW) + m[23];
        // orig.v = (m._el[4] * oX) + (m._el[9] * oX) + (m._el[14] * oX) + (m._el[19] * oX) + m._el[24];

        // multiply the direction by the matrix as a vector (5th component: 0.0)
        float dX = ray.dir.x;
        float dY = ray.dir.y;
        float dZ = ray.dir.z;
        float dW = ray.dir.w;
        newDir.x = (m[0] * dX) + (m[5] * dY) + (m[10] * dZ) + (m[15] * dW);
        newDir.y = (m[1] * dX) + (m[6] * dY) + (m[11] * dZ) + (m[16] * dW);
        newDir.z = (m[2] * dX) + (m[7] * dY) + (m[12] * dZ) + (m[17] * dW);
        newDir.w = (m[3] * dX) + (m[8] * dY) + (m[13] * dZ) + (m[18] * dW);
        // dir.v = (m._el[4] * oX) + (m._el[9] * oX) + (m._el[14] * oX) + (m._el[19] * oX);

        return ray4(newOrig, newDir);
    }
}