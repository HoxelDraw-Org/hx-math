/*
vec.h
Janury 2021
Contributors:
Justin Jensen
*/

#pragma once

#include <cstdint>
#include <cmath>
#include <float.h>
#include <algorithm>

namespace hxm
{
    // Forward declarations of classes here
    class vec2f;
    class vec2i;
    class vec2u;
    class vec3f;
    class vec3u;
    class vec4f;
    class vec4i;
    class vec4u;
    class vec5f;
    class vec5i;

    // VEC2F ------------------------------------------------------------------
    class vec2f {
        // Members
    private:
    protected:
    public:
        // TODO: make this a Union of an array and three separate floats
        union { float x, u; };
        union { float y, v; };

        // Functions
    private:
    protected:
    public:
        vec2f& operator+=(const vec2f& rhs);
        vec2f& operator-=(const vec2f& rhs);
        vec2f& operator*=(const vec2f& rhs);
        vec2f& operator*=(float rhs);
        vec2f& operator/=(const vec2f& rhs);
        vec2f& operator/=(float rhs);
        float& operator[](uint32_t idx);

        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        float dot(const vec2f& rhs) const;
        float length() const;
        vec2f& normalize();

        vec2f();
        vec2f(float v);
        vec2f(float x, float y);
        vec2f(const vec3f& v);
        vec2f(const vec2u& v);
        //vec2f(const vec2i& v);
        ~vec2f();
    };

    inline vec2f operator+(vec2f lhs, const vec2f& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec2f operator-(vec2f lhs, const vec2f& rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline vec2f operator*(vec2f lhs, const vec2f& rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec2f operator*(vec2f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec2f operator/(vec2f lhs, const vec2f& rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline vec2f operator/(vec2f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline float dot(const vec2f& a, const vec2f& b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }

    inline vec2f normalize(const vec2f& v)
    {
        vec2f result = v;
        result /= v.length();
        return result;
    }


    // VEC2I ------------------------------------------------------------------
    class vec2i {
        // Members
    private:
    protected:
    public:
        int32_t x;
        int32_t y;

        // Functions
    private:
    protected:
    public:
        // TODO: more operators
        int32_t& operator[](uint32_t idx);
        vec2i& operator+=(const vec2i& rhs);
        vec2i& operator-=(const vec2i& rhs);
        bool operator==(const vec2i& other);
        bool operator!=(const vec2i& rhs);

        vec2i();
        vec2i(int32_t v);
        vec2i(int32_t x, int32_t y);
        vec2i(const vec2f& fvec);
        vec2i(const vec2u& uvec);
        ~vec2i();
    };

    inline vec2i operator+(vec2i lhs, const vec2i& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec2i operator-(vec2i lhs, const vec2i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec2i clamp(vec2i v, int32_t min, int32_t max)
    {
        v.x = std::max(std::min(v.x, max), min);
        v.y = std::max(std::min(v.y, max), min);
        return v;
    }

    inline vec2i clamp(vec2i v, const vec2i& vMin, const vec2i& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        return v;
    }


    // VEC2U ------------------------------------------------------------------
    class vec2u {
        // Members
    private:
    protected:
    public:
        uint32_t x;
        uint32_t y;

        // Functions
    private:
    protected:
    public:
        // TODO: more operators
        uint32_t& operator[](uint32_t idx);
        uint32_t operator[](uint32_t idx) const;
        vec2u& operator+=(const vec2u& rhs);
        vec2u& operator-=(const vec2u& rhs);
        bool operator==(const vec2u& rhs);
        bool operator!=(const vec2u& rhs);

        vec2u();
        vec2u(uint32_t v);
        vec2u(uint32_t x, uint32_t y);
        vec2u(const vec2i& v);
        ~vec2u();
    };

    inline vec2u operator+(vec2u lhs, const vec2u& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec2u operator-(vec2u lhs, const vec2u& rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline vec2u clamp(vec2u v, const vec2u& vMin, const vec2u& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        return v;
    }


    // VEC3F ------------------------------------------------------------------
    class vec3f {
        // Members
    private:
    protected:
    public:
        // TODO: can we make this a Union of an array and three separate floats?
        union { float x, r, u; };
        union { float y, g, v; };
        union { float z, b, w; };

        // Functions
    private:
    protected:
    public:
        vec3f& operator+=(const vec3f& rhs);
        vec3f& operator-=(const vec3f& rhs);
        vec3f& operator*=(const vec3f& rhs);
        vec3f& operator*=(float rhs);
        vec3f& operator/=(const vec3f& rhs);
        vec3f& operator/=(float rhs);
        float& operator[](uint32_t idx);
        float  operator[](uint32_t idx) const;
        bool   operator==(const vec3f& rhs) const;

        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        float dot(const vec3f& rhs) const;
        float length() const;
        vec3f& normalize();

        vec3f();
        vec3f(float v);
        vec3f(float x, float y, float z);
        vec3f(const vec2f&, float z);
        vec3f(const vec3u& v);
        vec3f(const vec4f& v);
        vec3f(const vec4u& v);
        ~vec3f();
    };

    inline vec3f operator+(vec3f lhs, const vec3f& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec3f operator-(vec3f lhs, const vec3f& rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline vec3f operator*(vec3f lhs, const vec3f& rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec3f operator*(vec3f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec3f operator/(vec3f lhs, const vec3f& rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline vec3f operator/(vec3f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    // result is perpendicular to U and V
    inline vec3f cross(const vec3f& U, const vec3f& V) {
        return vec3f((U.y * V.z) - (U.z * V.y),
                     (U.z * V.x) - (U.x * V.z),
                     (U.x * V.y) - (U.y * V.x));
    }

    inline float dot(const vec3f& a, const vec3f& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    inline vec3f normalize(const vec3f& v)
    {
        vec3f result = v;
        result /= v.length();
        return result;
    }


    // VEC3U ------------------------------------------------------------------
    class vec3u {
        // Members
    private:
    protected:
    public:
        union { uint32_t x, r; };
        union { uint32_t y, g; };
        union { uint32_t z, b; };

        // Functions
    private:
    protected:
    public:
        // TODO: more operators
        uint32_t& operator[](uint32_t idx);
        bool operator==(const vec3u& rhs);
        bool operator==(const vec3u& rhs) const;
        bool operator!=(const vec3u& rhs);

        vec3u();
        vec3u(uint32_t v);
        vec3u(uint32_t x, uint32_t y, uint32_t z);
        ~vec3u();
    };


    // VEC4F ------------------------------------------------------------------
    class vec4f {
        // Members
    private:
    protected:
    public:
        union { float x, r; };
        union { float y, g; };
        union { float z, b; };
        union { float w, a; };

        // Functions
    private:
    protected:
    public:
        vec4f& operator+=(const vec4f& rhs);
        vec4f& operator-=(const vec4f& rhs);
        vec4f& operator*=(const vec4f& rhs);
        vec4f& operator*=(float rhs);
        vec4f& operator/=(const vec4f& rhs);
        vec4f& operator/=(float rhs);
        bool operator==(const vec4f& other);
        bool operator!=(const vec4f& other);
        float& operator[](uint32_t idx);
        float operator[](uint32_t idx) const;

        vec4f& copy(const vec4f& v);
        vec4f& set(float x, float y, float z, float w);
        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        float dot(const vec4f& rhs) const;
        float length() const;
        vec4f& normalize();

        vec4f();
        vec4f(float v);
        vec4f(float x, float y, float z, float w);
        vec4f(const vec3f& vec);
        vec4f(const vec3f& vec, float w);
        vec4f(const vec4u& vec);
        vec4f(const vec4i& vec);
        vec4f(const vec5f& vec);
        ~vec4f();
    };

    inline vec4f operator+(vec4f lhs, const vec4f& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec4f operator+(vec4f lhs, float rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec4f operator-(vec4f lhs, const vec4f& rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline vec4f operator-(vec4f lhs)
    {
        return vec4f(-lhs.x, -lhs.y, -lhs.z, -lhs.w);
    }

    inline vec4f operator*(vec4f lhs, const vec4f& rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec4f operator*(vec4f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec4f operator/(vec4f lhs, const vec4f& rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline vec4f operator/(vec4f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    // result is perpendicular to U, V, and W
    inline vec4f cross4(const vec4f& U, const vec4f& V, const vec4f& W)
    {
        float A, B, C, D, E, F;

        A = (V.x * W.y) - (V.y * W.x);
        B = (V.x * W.z) - (V.z * W.x);
        C = (V.x * W.w) - (V.w * W.x);
        D = (V.y * W.z) - (V.z * W.y);
        E = (V.y * W.w) - (V.w * W.y);
        F = (V.z * W.w) - (V.w * W.z);

        vec4f result(0);
        result.x =  (U.y * F) - (U.z * E) + (U.w * D);
        result.y = -(U.x * F) + (U.z * C) - (U.w * B);
        result.z =  (U.x * E) - (U.y * C) + (U.w * A);
        result.w = -(U.x * D) + (U.y * B) - (U.z * A);

        return result;
    }

    inline vec4f round(const vec4f& v)
    {
        vec4f result = { std::roundf(v.x), std::roundf(v.y), std::roundf(v.z), std::roundf(v.w) };
        return result;
    }

    inline float dot(const vec4f& a, const vec4f& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }


    // VEC4I ------------------------------------------------------------------
    class vec4i {
        // Members
    private:
    protected:
    public:
        union { int32_t x, r; };
        union { int32_t y, g; };
        union { int32_t z, b; };
        union { int32_t w, a; };

        // Functions
    private:
    protected:
    public:
        // TODO: more operators
        int32_t& operator[](uint32_t idx);
        int32_t operator[](uint32_t idx) const;
        vec4i& operator+=(const vec4i& rhs);
        vec4i& operator-=(const vec4i& rhs);
        vec4i& operator+=(int value);
        bool operator==(const vec4i& other);
        bool operator!=(const vec4i& other);
        bool operator==(const vec4u& other);    // vec4i == vec4u

        vec4i();
        vec4i(int32_t v);
        vec4i(int32_t x, int32_t y, int32_t z, int32_t w);
        vec4i(const vec4f& fvec);
        vec4i(const vec4u& uvec);
        ~vec4i();
    };

    inline vec4i operator+(vec4i lhs, size_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4i operator+(vec4i lhs, const vec4i& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4i operator-(vec4i lhs, const vec4i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4i clamp(vec4i v, const vec4i& vMin, const vec4i& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        v.w = std::max(std::min(v.w, vMax.w), vMin.w);
        return v;
    }

    inline vec4i vecAbs(vec4i v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        v.w = std::abs(v.w);
        return v;
    }

    // TODO: move to utils file?
    inline int firstNonZeroComponent(const vec4i& v)
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

    // handles negative values in vec a
    inline vec4i mod(const vec4i& a, const vec4i& b)
    {
        vec4i result;
        result.x = (a.x + ((abs(a.x / b.x) + 1) * b.x)) % b.x;
        result.y = (a.y + ((abs(a.y / b.y) + 1) * b.y)) % b.y;
        result.z = (a.z + ((abs(a.z / b.z) + 1) * b.z)) % b.z;
        result.w = (a.w + ((abs(a.w / b.w) + 1) * b.w)) % b.w;
        return result;
    }


    // VEC4U ------------------------------------------------------------------
    class vec4u {
        // Members
    private:
    protected:
    public:
        union { uint32_t x, r; };
        union { uint32_t y, g; };
        union { uint32_t z, b; };
        union { uint32_t w, a; };

        // Functions
    private:
    protected:
    public:
        // TODO: more operators
        uint32_t& operator[](uint32_t idx);
        uint32_t operator[](uint32_t idx) const;
        bool operator==(const vec4u& other);
        bool operator==(const vec4i& other);    // vec4u == vec4i
        bool operator!=(const vec4u& other);
        vec4u& operator/=(size_t value);
        vec4u& operator%=(size_t value);
        vec4u& operator+=(size_t rhs);
        vec4u& operator+=(const vec4u& other);
        vec4u& operator-=(const vec4u& rhs);
        vec4u& operator-=(const int& rhs);

        vec4u();
        vec4u(uint32_t v);
        vec4u(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
        vec4u(const vec4i& v);
        ~vec4u();
    };

    inline vec4u operator/(vec4u lhs, size_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4u operator%(vec4u lhs, size_t rhs)
    {
        lhs %= rhs;
        return lhs;
    }

    inline vec4u operator+(vec4u lhs, size_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4u operator+(vec4u lhs, const vec4u& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4u operator-(vec4u lhs, const vec4u& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4u operator<<(vec4u lhs, size_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        lhs.z <<= rhs;
        lhs.w <<= rhs;
        return lhs;
    }

    inline vec4u operator>>(vec4u lhs, size_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        lhs.z >>= rhs;
        lhs.w >>= rhs;
        return lhs;
    }

    inline vec4u operator*(vec4u lhs, size_t rhs)
    {
        lhs.x *= rhs;
        lhs.y *= rhs;
        lhs.z *= rhs;
        lhs.w *= rhs;
        return lhs;
    }

    inline vec4u clamp(vec4u v, const vec4u& vMin, const vec4u& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        v.w = std::max(std::min(v.w, vMax.w), vMin.w);
        return v;
    }

    // TODO: move to a utils file?
    inline size_t countEqualComponents(const vec4u& a, const vec4u& b)
    {
        size_t result = 0;
        result += a.x == b.x ? 1 : 0;
        result += a.y == b.y ? 1 : 0;
        result += a.z == b.z ? 1 : 0;
        result += a.w == b.w ? 1 : 0;
        return result;
    }


    // VEC5F ------------------------------------------------------------------
    class vec5f {
        // Members
    private:
    protected:
    public:
        union { float x; };
        union { float y; };
        union { float z; };
        union { float w; };
        union { float v; };

        // Functions
    private:
    protected:
    public:
        vec5f& operator+=(const vec5f& rhs);
        vec5f& operator+=(float rhs);
        vec5f& operator-=(const vec5f& rhs);
        vec5f& operator-=(float rhs);
        vec5f& operator*=(const vec5f& rhs);
        vec5f& operator*=(float rhs);
        vec5f& operator/=(const vec5f& rhs);
        vec5f& operator/=(float rhs);
        bool operator==(const vec5f& other);
        bool operator!=(const vec5f& other);
        float& operator[](uint32_t idx);
        float operator[](uint32_t idx) const;

        vec5f& copy(const vec5f& v);
        vec5f& set(float x, float y, float z, float w, float v);
        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        float dot(const vec5f& rhs) const;
        float length() const;
        vec5f& normalize();

        vec5f();
        vec5f(float v);
        vec5f(float x, float y, float z, float w, float v);
        vec5f(const vec3f& vec);
        vec5f(const vec3f& vec, float w, float v);
        vec5f(const vec4f& vec, float v);
        vec5f(const vec4u& vec);
        vec5f(const vec4i& vec);
        vec5f(const vec5i& vec);
        ~vec5f();
    };

    inline vec5f operator+(vec5f lhs, const vec5f& rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec5f operator+(vec5f lhs, float rhs) {
        lhs += rhs;
        return lhs;
    }

    inline vec5f operator-(vec5f lhs, const vec5f& rhs) {
        lhs -= rhs;
        return lhs;
    }

    inline vec5f operator-(vec5f lhs)
    {
        return vec5f(-lhs.x, -lhs.y, -lhs.z, -lhs.w, -lhs.v);
    }

    inline vec5f operator*(vec5f lhs, const vec5f& rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec5f operator*(vec5f lhs, float rhs) {
        lhs *= rhs;
        return lhs;
    }

    inline vec5f operator/(vec5f lhs, const vec5f& rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline vec5f operator/(vec5f lhs, float rhs) {
        lhs /= rhs;
        return lhs;
    }

    inline vec5f round(const vec5f& v)
    {
        vec5f result = { std::roundf(v.x), std::roundf(v.y), std::roundf(v.z), std::roundf(v.w), std::roundf(v.v) };
        return result;
    }


    // VEC5I ------------------------------------------------------------------
    class vec5i {
        // Members
    private:
    protected:
    public:
        int32_t x;
        int32_t y;
        int32_t z;
        int32_t w;
        int32_t r;

        // Functions
    private:
    protected:
    public:
        int32_t& operator[](uint32_t idx);
        int32_t operator[](uint32_t idx) const;
        vec5i& operator+=(const vec5i& rhs);
        vec5i& operator-=(const vec5i& rhs);
        vec5i& operator+=(int value);
        bool operator==(const vec5i& other);
        bool operator!=(const vec5i& other);

        vec5i();
        vec5i(int32_t v);
        vec5i(int32_t x, int32_t y, int32_t z, int32_t w, int32_t r);
        ~vec5i();
    };    

    inline vec5i operator+(vec5i lhs, size_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5i operator+(vec5i lhs, const vec5i& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5i operator-(vec5i lhs, const vec5i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec5i clamp(vec5i v, const vec5i& vMin, const vec5i& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        v.w = std::max(std::min(v.w, vMax.w), vMin.w);
        v.r = std::max(std::min(v.r, vMax.r), vMin.r);
        return v;
    }

    inline vec5i vecAbs(vec5i v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        v.w = std::abs(v.w);
        v.r = std::abs(v.r);
        return v;
    }

    // TODO: move to a utils file?
    inline int firstNonZeroComponent(const vec5i& v)
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

    // handles negative values in vec a
    inline vec5i mod(const vec5i& a, const vec5i& b)
    {
        vec5i result;
        result.x = (a.x + ((abs(a.x / b.x) + 1) * b.x)) % b.x;
        result.y = (a.y + ((abs(a.y / b.y) + 1) * b.y)) % b.y;
        result.z = (a.z + ((abs(a.z / b.z) + 1) * b.z)) % b.z;
        result.w = (a.w + ((abs(a.w / b.w) + 1) * b.w)) % b.w;
        result.r = (a.r + ((abs(a.r / b.r) + 1) * b.r)) % b.r;
        return result;
    }
}