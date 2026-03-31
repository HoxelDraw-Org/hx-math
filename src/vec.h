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
    class vec3i;
    class vec3u;
    class vec3u8;
    class vec4f;
    class vec4i;
    class vec4u;
    class vec4u8;
    class vec5f;
    class vec5i;
    class vec5u;

    typedef vec3f colorRGB;
    typedef vec4f colorRGBA;
    typedef vec2f vec2;
    typedef vec3f vec3;
    typedef vec4f vec4;
    typedef vec5f vec5;

    // VEC2F ------------------------------------------------------------------
    class vec2f {
        // Members
    private:
    protected:
    public:
        union
        {
            float _v[2];
            struct { float x, y; };
            struct { float u, v; };
        };

        // Functions
    private:
    protected:
    public:
        vec2f& operator+=(const vec2f& rhs);
        vec2f& operator+=(const float rhs);
        vec2f& operator-=(const vec2f& rhs);
        vec2f& operator-=(const float rhs);
        vec2f& operator*=(const vec2f& rhs);
        vec2f& operator*=(const float rhs);
        vec2f& operator/=(const vec2f& rhs);
        vec2f& operator/=(const float rhs);
        bool operator==(const vec2f& rhs) const;
        bool operator!=(const vec2f& rhs) const;
        float& operator[](uint32_t idx);
        float operator[](uint32_t idx) const;

        float dot(const vec2f& rhs) const;
        float length() const;
        float normalize();  // returns the length before normalization

        // TODO: move to utils file
        uint32_t minCompIdx() const;    // the index of the smallest component of this vector

        vec2f();
        vec2f(float v);
        vec2f(float x, float y);
        vec2f(const vec3f& fvec3);
        vec2f(const vec2i& ivec);
        vec2f(const vec2u& uvec);
    };

    inline vec2f operator+(vec2f lhs, const vec2f& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec2f operator+(vec2f lhs, const float rhs)
    {
        lhs += rhs; // TODO: would it be faster to unroll += ?
        return lhs;
    }

    inline vec2f operator-(vec2f lhs, const vec2f& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec2f operator-(vec2f lhs, const float rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec2f operator-(const vec2f& rhs)
    {
        return vec2f(-rhs.x, -rhs.y);
    }

    inline vec2f operator*(vec2f lhs, const vec2f& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec2f operator*(vec2f lhs, float rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec2f operator/(vec2f lhs, const vec2f& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec2f operator/(vec2f lhs, float rhs)
    {
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
        result /= v.length();   // TODO: would it be faster to inline length()?
        return result;
    }

    inline vec2f clamp(vec2f v, const vec2f& vMin, const vec2f& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        return v;
    }

    inline vec2f clamp(vec2f v, const float vMin, const float vMax)
    {
        v.x = std::max(std::min(v.x, vMax), vMin);
        v.y = std::max(std::min(v.y, vMax), vMin);
        return v;
    }

    inline vec2f round(const vec2f& v)
    {
        return vec2f(std::roundf(v.x), std::roundf(v.y));
    }

    inline vec2f vabs(vec2f v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        return v;
    }


    // VEC2I ------------------------------------------------------------------
    class vec2i {
        // Members
    private:
    protected:
    public:
        union
        {
            int32_t _v[2];
            struct { int32_t x, y; };
        };

        // Functions
    private:
    protected:
    public:
        vec2i& operator+=(const vec2i& rhs);
        vec2i& operator+=(const int32_t rhs);
        vec2i& operator-=(const vec2i& rhs);
        vec2i& operator-=(const int32_t rhs);
        vec2i& operator*=(const vec2i& rhs);
        vec2i& operator*=(const int32_t rhs);
        vec2i& operator/=(const vec2i& rhs);
        vec2i& operator/=(const int32_t rhs);
        bool operator==(const vec2i& other) const;
        bool operator!=(const vec2i& rhs) const;
        int32_t& operator[](uint32_t idx);
        int32_t operator[](uint32_t idx) const;

        vec2i();
        vec2i(int32_t v);
        vec2i(int32_t x, int32_t y);
        vec2i(const vec2f& fvec);
        vec2i(const vec2u& uvec);
    };

    inline vec2i operator+(vec2i lhs, const vec2i& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec2i operator+(vec2i lhs, const int32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec2i operator-(vec2i lhs, const vec2i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec2i operator-(vec2i lhs, const int32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec2i operator-(vec2i rhs)
    {
        return vec2i(-rhs.x, -rhs.y);
    }

    inline vec2i operator*(vec2i lhs, const vec2i& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec2i operator*(vec2i lhs, const int32_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec2i operator/(vec2i lhs, const vec2i& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec2i operator/(vec2i lhs, const int32_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec2i clamp(vec2i v, const vec2i& vMin, const vec2i& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        return v;
    }

    inline vec2i clamp(vec2i v, const int32_t vmin, const int32_t vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        return v;
    }

    inline vec2i vabs(vec2i v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        return v;
    }

    // handles negative values in vec a
    inline vec2i mod(const vec2i& a, const vec2i& b)
    {
        vec2i result;
        result.x = (a.x + ((abs(a.x / b.x) + 1) * b.x)) % b.x;
        result.y = (a.y + ((abs(a.y / b.y) + 1) * b.y)) % b.y;
        return result;
    }

    inline vec2i operator<<(vec2i lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        return lhs;
    }

    inline vec2i operator>>(vec2i lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        return lhs;
    }


    // VEC2U ------------------------------------------------------------------
    class vec2u {
        // Members
    private:
    protected:
    public:
        union
        {
            uint32_t _v[2];
            struct { uint32_t x, y; };
        };

        // Functions
    private:
    protected:
    public:
        vec2u& operator+=(const vec2u& rhs);
        vec2u& operator+=(const uint32_t rhs);
        vec2u& operator-=(const vec2u& rhs);
        vec2u& operator-=(const uint32_t rhs);
        vec2u& operator*=(const vec2u& rhs);
        vec2u& operator*=(const uint32_t rhs);
        vec2u& operator/=(const vec2u& rhs);
        vec2u& operator/=(const uint32_t rhs);
        bool operator==(const vec2u& rhs) const;
        bool operator!=(const vec2u& rhs) const;
        uint32_t& operator[](uint32_t idx);
        uint32_t operator[](uint32_t idx) const;

        vec2u();
        vec2u(uint32_t v);
        vec2u(uint32_t x, uint32_t y);
        vec2u(const vec2i& ivec);
        vec2u(const vec2f& fvec);
    };

    inline vec2u operator+(vec2u lhs, const vec2u& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec2u operator+(vec2u lhs, const uint32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec2u operator-(vec2u lhs, const vec2u& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec2u operator-(vec2u lhs, const uint32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec2u operator*(vec2u lhs, const vec2u& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec2u operator*(vec2u lhs, const uint32_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec2u operator/(vec2u lhs, const vec2u& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec2u operator/(vec2u lhs, const uint32_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec2u clamp(vec2u v, const vec2u& vMin, const vec2u& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        return v;
    }

    inline vec2u clamp(vec2u v, const uint32_t vMin, const uint32_t vMax)
    {
        v.x = std::max(std::min(v.x, vMax), vMin);
        v.y = std::max(std::min(v.y, vMax), vMin);
        return v;
    }

    inline vec2u operator<<(vec2u lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        return lhs;
    }

    inline vec2u operator>>(vec2u lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        return lhs;
    }


    // VEC3F ------------------------------------------------------------------
    class vec3f {
        // Members
    private:
    protected:
    public:
        union
        {
            float _v[3];
            struct { float x, y, z; };
            struct { float r, g, b; };
            struct { float u, v, w; };
        };

        // Functions
    private:
    protected:
    public:
        vec3f& operator+=(const vec3f& rhs);
        vec3f& operator+=(const float rhs);
        vec3f& operator-=(const vec3f& rhs);
        vec3f& operator-=(const float rhs);
        vec3f& operator*=(const vec3f& rhs);
        vec3f& operator*=(const float rhs);
        vec3f& operator/=(const vec3f& rhs);
        vec3f& operator/=(const float rhs);
        bool   operator==(const vec3f& rhs) const;
        bool   operator!=(const vec3f& rhs) const;
        float& operator[](uint32_t idx);
        float  operator[](uint32_t idx) const;

        // TODO move to utils file
        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        
        float dot(const vec3f& rhs) const;
        float length() const;
        float normalize(); // returns the length before normalization

        vec3f();
        vec3f(float v);
        vec3f(float x, float y, float z);
        vec3f(const vec2f&, float z);
        vec3f(const vec3u& uvec);
        vec3f(const vec3i& ivec);
        vec3f(const vec4f& fvec4);
        vec3f(const vec4u& uvec4);
    };

    inline vec3f operator+(vec3f lhs, const vec3f& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec3f operator+(vec3f lhs, const float rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec3f operator-(vec3f lhs, const vec3f& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec3f operator-(vec3f lhs, const float rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec3f operator-(const vec3f& rhs)
    {
        return vec3f(-rhs.x, -rhs.y, -rhs.z);
    }

    inline vec3f operator*(vec3f lhs, const vec3f& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec3f operator*(vec3f lhs, const float rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec3f operator/(vec3f lhs, const vec3f& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec3f operator/(vec3f lhs, const float rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    // result is perpendicular to U and V
    inline vec3f cross(const vec3f& U, const vec3f& V)
    {
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
    
    inline vec3f clamp(vec3f v, const vec3f& vmin, const vec3f& vmax)
    {
        v.x = std::max(std::min(v.x, vmax.x), vmin.x);
        v.y = std::max(std::min(v.y, vmax.y), vmin.y);
        v.z = std::max(std::min(v.z, vmax.z), vmin.z);
        return v;
    }

    inline vec3f clamp(vec3f v, const float vmin, const float vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        return v;
    }

    inline vec3f round(const vec3f& v)
    {
        return vec3f(std::roundf(v.x), std::roundf(v.y), std::roundf(v.z));
    }

    inline vec3f vabs(vec3f v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        return v;
    }


    // VEC3I ------------------------------------------------------------------
    class vec3i {
        // Members
    private:
    protected:
    public:
        union
        {
            int32_t _v[3];
            struct { int32_t x, y, z; };
        };

        // Functions
    private:
    protected:
    public:
        vec3i& operator+=(const vec3i& rhs);
        vec3i& operator+=(const int32_t rhs);
        vec3i& operator-=(const vec3i& rhs);
        vec3i& operator-=(const int32_t rhs);
        vec3i& operator*=(const vec3i& rhs);
        vec3i& operator*=(const int32_t rhs);
        vec3i& operator/=(const vec3i& rhs);
        vec3i& operator/=(const int32_t rhs);
        bool operator==(const vec3i& rhs) const;
        bool operator!=(const vec3i& rhs) const;
        int32_t& operator[](uint32_t idx);
        int32_t operator[](uint32_t idx) const;

        vec3i();
        vec3i(int32_t v);
        vec3i(int32_t x, int32_t y, int32_t z);
        vec3i(const vec3f& fvec);
        vec3i(const vec3u& uvec);
    };

    inline vec3i operator+(vec3i lhs, const vec3i& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec3i operator+(vec3i lhs, const float rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec3i operator-(vec3i lhs, const vec3i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec3i operator-(vec3i lhs, const float rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec3i operator-(const vec3i& rhs)
    {
        return vec3i(-rhs.x, -rhs.y, -rhs.z);
    }

    inline vec3i operator*(vec3i lhs, const vec3i& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec3i operator*(vec3i lhs, const int32_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec3i operator/(vec3i lhs, const vec3i& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec3i operator/(vec3i lhs, const int32_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec3i clamp(vec3i v, const vec3i& vMin, const vec3i& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        return v;
    }

    inline vec3i clamp(vec3i v, const int32_t vmin, const int32_t vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        return v;
    }

    inline vec3i vabs(vec3i v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        return v;
    }

    // handles negative values in vec a
    inline vec3i mod(const vec3i& a, const vec3i& b)
    {
        vec3i result;
        result.x = (a.x + ((std::abs(a.x / b.x) + 1) * b.x)) % b.x;
        result.y = (a.y + ((std::abs(a.y / b.y) + 1) * b.y)) % b.y;
        result.z = (a.z + ((std::abs(a.z / b.z) + 1) * b.z)) % b.z;
        return result;
    }

    inline vec3i operator<<(vec3i lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        lhs.z <<= rhs;
        return lhs;
    }

    inline vec3i operator>>(vec3i lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        lhs.z >>= rhs;
        return lhs;
    }


    // VEC3U ------------------------------------------------------------------
    class vec3u {
        // Members
    private:
    protected:
    public:
        union
        {
            uint32_t _v[3];
            struct { uint32_t x, y, z; };
            struct { uint32_t r, g, b; };
        };

        // Functions
    private:
    protected:
    public:
        vec3u& operator+=(const vec3u& rhs);
        vec3u& operator+=(const uint32_t rhs);
        vec3u& operator-=(const vec3u& rhs);
        vec3u& operator-=(const uint32_t rhs);
        vec3u& operator*=(const vec3u& rhs);
        vec3u& operator*=(const uint32_t rhs);
        vec3u& operator/=(const vec3u& rhs);
        vec3u& operator/=(const uint32_t rhs);
        bool operator==(const vec3u& rhs) const;
        bool operator!=(const vec3u& rhs) const;
        uint32_t& operator[](uint32_t idx);
        uint32_t operator[](uint32_t idx) const;

        vec3u();
        vec3u(uint32_t v);
        vec3u(uint32_t x, uint32_t y, uint32_t z);
        vec3u(const vec3f& fvec);
        vec3u(const vec3i& ivec);
    };


    // VEC3U8 -----------------------------------------------------------------
    class vec3u8 {
        // Members
    private:
    protected:
    public:
        union
        {
            uint8_t _v[3];
            struct { uint8_t x, y, z; };
            struct { uint8_t r, g, b; };
        };

        // Functions
    private:
    protected:
    public:
        vec3u8& operator+=(const vec3u8& rhs);
        vec3u8& operator+=(const uint8_t rhs);
        vec3u8& operator-=(const vec3u8& rhs);
        vec3u8& operator-=(const uint8_t rhs);
        vec3u8& operator*=(const vec3u8& rhs);
        vec3u8& operator*=(const uint8_t rhs);
        vec3u8& operator/=(const vec3u8& rhs);
        vec3u8& operator/=(const uint8_t rhs);
        bool operator==(const vec3u8& rhs) const;
        bool operator!=(const vec3u8& rhs) const;
        uint8_t& operator[](uint32_t idx);
        uint8_t operator[](uint32_t idx) const;

        vec3u8();
        vec3u8(uint8_t v);
        vec3u8(uint8_t x, uint8_t y, uint8_t z);
        vec3u8(const vec3f& fvec);
        vec3u8(const vec3i& ivec);
        vec3u8(const vec3u& uvec32);
    };

    inline vec3u8 operator+(vec3u8 lhs, const vec3u8& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec3u8 operator+(vec3u8 lhs, const uint8_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec3u8 operator-(vec3u8 lhs, const vec3u8& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec3u8 operator-(vec3u8 lhs, const uint8_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec3u8 operator*(vec3u8 lhs, const vec3u8& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec3u8 operator*(vec3u8 lhs, const uint8_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec3u8 operator/(vec3u8 lhs, const vec3u8& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec3u8 operator/(vec3u8 lhs, const uint8_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec3u8 clamp(vec3u8 v, const vec3u8& vMin, const vec3u8& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        return v;
    }

    inline vec3u8 clamp(vec3u8 v, const uint8_t vmin, const uint8_t vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        return v;
    }

    // VEC4F ------------------------------------------------------------------
    class vec4f {
        // Members
    private:
    protected:
    public:
        union
        {
            float _v[4];
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
        };

        // Functions
    private:
    protected:
    public:
        vec4f& operator+=(const vec4f& rhs);
        vec4f& operator+=(const float rhs);
        vec4f& operator-=(const vec4f& rhs);
        vec4f& operator-=(const float rhs);
        vec4f& operator*=(const vec4f& rhs);
        vec4f& operator*=(const float rhs);
        vec4f& operator/=(const vec4f& rhs);
        vec4f& operator/=(const float rhs);
        bool operator==(const vec4f& rhs) const;
        bool operator!=(const vec4f& rhs) const;
        float& operator[](uint32_t idx);
        float operator[](uint32_t idx) const;

        // TODO jjensen: remove copy and set
        vec4f& copy(const vec4f& v);
        vec4f& set(float x, float y, float z, float w);

        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        float dot(const vec4f& rhs) const;
        float length() const;
        float normalize();  // returns length before normalization

        vec4f();
        vec4f(float v);
        vec4f(float x, float y, float z, float w);
        vec4f(const vec3f& fvec3);
        vec4f(const vec3f& fvec3, float w);
        vec4f(const vec4u& uvec);
        vec4f(const vec4i& ivec);
        vec4f(const vec5f& fvec5);
    };

    inline vec4f operator+(vec4f lhs, const vec4f& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4f operator+(vec4f lhs, const float rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4f operator-(vec4f lhs, const vec4f& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4f operator-(vec4f lhs, const float rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec4f operator-(const vec4f& lhs)
    {
        return vec4f(-lhs.x, -lhs.y, -lhs.z, -lhs.w);
    }

    inline vec4f operator*(vec4f lhs, const vec4f& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4f operator*(vec4f lhs, const float rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4f operator/(vec4f lhs, const vec4f& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4f operator/(vec4f lhs, const float rhs)
    {
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
        result.x = (U.y * F) - (U.z * E) + (U.w * D);
        result.y = -(U.x * F) + (U.z * C) - (U.w * B);
        result.z = (U.x * E) - (U.y * C) + (U.w * A);
        result.w = -(U.x * D) + (U.y * B) - (U.z * A);

        return result;
    }

    inline float dot(const vec4f& a, const vec4f& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }

    inline vec4f normalize(const vec4f& v)
    {
        vec4f result = v;
        result /= v.length();
        return result;
    }
    
    inline vec4f clamp(vec4f v, const vec4f& vmin, const vec4f& vmax)
    {
        v.x = std::max(std::min(v.x, vmax.x), vmin.x);
        v.y = std::max(std::min(v.y, vmax.y), vmin.y);
        v.z = std::max(std::min(v.z, vmax.z), vmin.z);
        v.w = std::max(std::min(v.w, vmax.w), vmin.w);
        return v;
    }

    inline vec4f clamp(vec4f v, const float vmin, const float vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        v.w = std::max(std::min(v.w, vmax), vmin);
        return v;
    }

    inline vec4f round(const vec4f& v)
    {
        return vec4f(std::roundf(v.x), std::roundf(v.y), std::roundf(v.z), std::roundf(v.w));
    }

    inline vec4f vabs(vec4f v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        v.w = std::abs(v.w);
        return v;
    }


    // VEC4I ------------------------------------------------------------------
    class vec4i {
        // Members
    private:
    protected:
    public:
        union
        {
            int32_t _v[4];
            struct { int32_t x, y, z, w; };
            struct { int32_t r, g, b, a; };
        };

        // Functions
    private:
    protected:
    public:
        vec4i& operator+=(const vec4i& rhs);
        vec4i& operator+=(const int32_t rhs);
        vec4i& operator-=(const vec4i& rhs);
        vec4i& operator-=(const int32_t rhs);
        vec4i& operator*=(const vec4i& rhs);
        vec4i& operator*=(const int32_t rhs);
        vec4i& operator/=(const vec4i& rhs);
        vec4i& operator/=(const int32_t rhs);
        bool operator==(const vec4i& rhs) const;
        bool operator==(const vec4u& rhs) const;    // vec4i == vec4u
        bool operator!=(const vec4i& rhs) const;
        int32_t& operator[](uint32_t idx);
        int32_t operator[](uint32_t idx) const;

        vec4i();
        vec4i(int32_t v);
        vec4i(int32_t x, int32_t y, int32_t z, int32_t w);
        vec4i(const vec4f& fvec);
        vec4i(const vec4u& uvec);
    };

    inline vec4i operator+(vec4i lhs, const vec4i& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4i operator+(vec4i lhs, const int32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4i operator-(vec4i lhs, const vec4i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4i operator-(vec4i lhs, const int32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec4i operator-(const vec4i& lhs)
    {
        return vec4i(-lhs.x, -lhs.y, -lhs.z, -lhs.w);
    }

    inline vec4i operator*(vec4i lhs, const vec4i& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4i operator*(vec4i lhs, const int32_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4i operator/(vec4i lhs, const vec4i& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4i operator/(vec4i lhs, const int32_t rhs)
    {
        lhs /= rhs;
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

    inline vec4i clamp(vec4i v, const int32_t vmin, const int32_t vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        v.w = std::max(std::min(v.w, vmax), vmin);
        return v;
    }

    inline vec4i vabs(vec4i v)
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

    inline vec4i operator<<(vec4i lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        lhs.z <<= rhs;
        lhs.w <<= rhs;
        return lhs;
    }

    inline vec4i operator>>(vec4i lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        lhs.z >>= rhs;
        lhs.w >>= rhs;
        return lhs;
    }


    // VEC4U ------------------------------------------------------------------
    class vec4u {
        // Members
    private:
    protected:
    public:
        union
        {
            uint32_t _v[4];
            struct { uint32_t x, y, z, w; };
            struct { uint32_t r, g, b, a; };
        };

        // Functions
    private:
    protected:
    public:
        vec4u& operator+=(const vec4u& rhs);
        vec4u& operator+=(const uint32_t rhs);
        vec4u& operator-=(const vec4u& rhs);
        vec4u& operator-=(const uint32_t rhs);
        vec4u& operator*=(const vec4u& rhs);
        vec4u& operator*=(const uint32_t rhs);
        vec4u& operator/=(const vec4u& rhs);
        vec4u& operator/=(const uint32_t rhs);
        vec4u& operator%=(const uint32_t rhs);
        bool operator==(const vec4u& rhs) const;
        bool operator==(const vec4i& rhs) const;    // vec4u == vec4i
        bool operator!=(const vec4u& rhs) const;
        uint32_t& operator[](uint32_t idx);
        uint32_t operator[](uint32_t idx) const;

        vec4u();
        vec4u(uint32_t v);
        vec4u(uint32_t x, uint32_t y, uint32_t z, uint32_t w);
        vec4u(const vec4f& fvec);
        vec4u(const vec4i& ivec);
    };

    inline vec4u operator+(vec4u lhs, const vec4u& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4u operator+(vec4u lhs, const uint32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4u operator-(vec4u lhs, const vec4u& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4u operator-(vec4u lhs, const uint32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4u operator*(vec4u lhs, const vec4u& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4u operator*(vec4u lhs, const uint32_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4u operator/(vec4u lhs, const vec4u& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4u operator/(vec4u lhs, const uint32_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4u operator%(vec4u lhs, const uint32_t rhs)
    {
        lhs %= rhs;
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

    inline vec4u clamp(vec4u v, const uint32_t vMin, const uint32_t vMax)
    {
        v.x = std::max(std::min(v.x, vMax), vMin);
        v.y = std::max(std::min(v.y, vMax), vMin);
        v.z = std::max(std::min(v.z, vMax), vMin);
        v.w = std::max(std::min(v.w, vMax), vMin);
        return v;
    }

    inline vec4u operator<<(vec4u lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        lhs.z <<= rhs;
        lhs.w <<= rhs;
        return lhs;
    }

    inline vec4u operator>>(vec4u lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        lhs.z >>= rhs;
        lhs.w >>= rhs;
        return lhs;
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


    // VEC4U8 -----------------------------------------------------------------
    class vec4u8 {
        // Members
    private:
    protected:
    public:
        union
        {
            uint8_t _v[4];
            struct { uint8_t x, y, z, w; };
            struct { uint8_t r, g, b, a; };
        };

        // Functions
    private:
    protected:
    public:
        vec4u8& operator+=(const vec4u8& rhs);
        vec4u8& operator+=(const uint8_t rhs);
        vec4u8& operator-=(const vec4u8& rhs);
        vec4u8& operator-=(const uint8_t rhs);
        vec4u8& operator*=(const vec4u8& rhs);
        vec4u8& operator*=(const uint8_t rhs);
        vec4u8& operator/=(const vec4u8& rhs);
        vec4u8& operator/=(const uint8_t rhs);
        vec4u8& operator%=(const uint8_t rhs);
        bool operator==(const vec4u8& rhs) const;
        bool operator!=(const vec4u8& rhs) const;
        uint8_t& operator[](uint32_t idx);
        uint8_t operator[](uint32_t idx) const;

        vec4u8();
        vec4u8(uint8_t v);
        vec4u8(uint8_t x, uint8_t y, uint8_t z, uint8_t w);
        vec4u8(const vec4f& fvec);
        vec4u8(const vec4i& ivec);
        vec4u8(const vec4u& uvec32);
    };

    inline vec4u8 operator+(vec4u8 lhs, const vec4u8& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4u8 operator+(vec4u8 lhs, const uint8_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec4u8 operator-(vec4u8 lhs, const vec4u8& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4u8 operator-(vec4u8 lhs, const uint8_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec4u8 operator*(vec4u8 lhs, const vec4u8& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4u8 operator*(vec4u8 lhs, const uint8_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec4u8 operator/(vec4u8 lhs, const vec4u8& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4u8 operator/(vec4u8 lhs, const uint8_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec4u8 clamp(vec4u8 v, const vec4u8& vMin, const vec4u8& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        v.w = std::max(std::min(v.w, vMax.w), vMin.w);
        return v;
    }

    inline vec4u8 clamp(vec4u8 v, const uint8_t vmin, const uint8_t vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        v.w = std::max(std::min(v.w, vmax), vmin);
        return v;
    }


    // VEC5F ------------------------------------------------------------------
    class vec5f {
        // Members
    private:
    protected:
    public:
        union
        {
            float _v[5];
            struct { float x, y, z, w, v; };
        };

        // Functions
    private:
    protected:
    public:
        vec5f& operator+=(const vec5f& rhs);
        vec5f& operator+=(const float rhs);
        vec5f& operator-=(const vec5f& rhs);
        vec5f& operator-=(const float rhs);
        vec5f& operator*=(const vec5f& rhs);
        vec5f& operator*=(const float rhs);
        vec5f& operator/=(const vec5f& rhs);
        vec5f& operator/=(const float rhs);
        bool operator==(const vec5f& other) const;
        bool operator!=(const vec5f& other) const;
        float& operator[](uint32_t idx);
        float operator[](uint32_t idx) const;

        // TODO jjensen: remove copy and set
        vec5f& copy(const vec5f& v);
        vec5f& set(float x, float y, float z, float w, float v);

        uint32_t minCompIdx() const;    // the index of the smallest component of this vector
        float dot(const vec5f& rhs) const;
        float length() const;
        float normalize();  // returns length before normalization

        vec5f();
        vec5f(float v);
        vec5f(float x, float y, float z, float w, float v);
        vec5f(const vec3f& fvec3);
        vec5f(const vec3f& fvec3, float w, float v);
        vec5f(const vec4f& fvec4, float v);
        vec5f(const vec4u& uvec4);
        vec5f(const vec4i& ivec4);
        vec5f(const vec5i& ivec5);
    };

    inline vec5f operator+(vec5f lhs, const vec5f& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5f operator+(vec5f lhs, const float rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5f operator-(vec5f lhs, const vec5f& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec5f operator-(vec5f lhs, const float rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec5f operator-(const vec5f& lhs)
    {
        return vec5f(-lhs.x, -lhs.y, -lhs.z, -lhs.w, -lhs.v);
    }

    inline vec5f operator*(vec5f lhs, const vec5f& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec5f operator*(vec5f lhs, const float rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec5f operator/(vec5f lhs, const vec5f& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec5f operator/(vec5f lhs, const float rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline float dot(const vec5f& a, const vec5f& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w) + (a.v * b.v);
    }

    inline vec5f clamp(vec5f v, const vec5f& vmin, const vec5f& vmax)
    {
        v.x = std::max(std::min(v.x, vmax.x), vmin.x);
        v.y = std::max(std::min(v.y, vmax.y), vmin.y);
        v.z = std::max(std::min(v.z, vmax.z), vmin.z);
        v.w = std::max(std::min(v.w, vmax.w), vmin.w);
        v.v = std::max(std::min(v.v, vmax.v), vmin.v);
        return v;
    }

    inline vec5f clamp(vec5f v, const float vmin, const float vmax)
    {
        v.x = std::max(std::min(v.x, vmax), vmin);
        v.y = std::max(std::min(v.y, vmax), vmin);
        v.z = std::max(std::min(v.z, vmax), vmin);
        v.w = std::max(std::min(v.w, vmax), vmin);
        v.v = std::max(std::min(v.v, vmax), vmin);
        return v;
    }

    inline vec5f normalize(const vec5f& v)
    {
        vec5f result = v;
        result /= v.length();
        return result;
    }

    inline vec5f round(const vec5f& v)
    {
        return vec5f(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w), std::round(v.v));
    }

    inline vec5f vabs(vec5f v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        v.w = std::abs(v.w);
        v.v = std::abs(v.v);
        return v;
    }


    // VEC5I ------------------------------------------------------------------
    class vec5i {
        // Members
    private:
    protected:
    public:
        union
        {
            int32_t _v[5];
            struct { int32_t x, y, z, w, v; };
        };

        // Functions
    private:
    protected:
    public:
        vec5i& operator+=(const vec5i& rhs);
        vec5i& operator+=(const int32_t rhs);
        vec5i& operator-=(const vec5i& rhs);
        vec5i& operator-=(const int32_t rhs);
        vec5i& operator*=(const vec5i& rhs);
        vec5i& operator*=(const int32_t rhs);
        vec5i& operator/=(const vec5i& rhs);
        vec5i& operator/=(const int32_t rhs);
        bool operator==(const vec5i& other) const;
        bool operator!=(const vec5i& other) const;
        int32_t& operator[](uint32_t idx);
        int32_t operator[](uint32_t idx) const;

        vec5i();
        vec5i(int32_t v);
        vec5i(int32_t x, int32_t y, int32_t z, int32_t w, int32_t v);
    };

    inline vec5i operator+(vec5i lhs, const vec5i& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5i operator+(vec5i lhs, const int32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5i operator-(vec5i lhs, const vec5i& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec5i operator-(vec5i lhs, const int32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    // negation operator
    inline vec5i operator-(const vec5i& lhs)
    {
        return vec5i(-lhs.x, -lhs.y, -lhs.z, -lhs.w, -lhs.v);
    }

    inline vec5i operator*(vec5i lhs, const vec5i& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec5i operator*(vec5i lhs, const float rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec5i operator/(vec5i lhs, const vec5i& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec5i operator/(vec5i lhs, const float rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec5i clamp(vec5i v, const vec5i& vMin, const vec5i& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        v.w = std::max(std::min(v.w, vMax.w), vMin.w);
        v.v = std::max(std::min(v.v, vMax.v), vMin.v);
        return v;
    }

    inline vec5i clamp(vec5i v, const int32_t vMin, const int32_t vMax)
    {
        v.x = std::max(std::min(v.x, vMax), vMin);
        v.y = std::max(std::min(v.y, vMax), vMin);
        v.z = std::max(std::min(v.z, vMax), vMin);
        v.w = std::max(std::min(v.w, vMax), vMin);
        v.v = std::max(std::min(v.v, vMax), vMin);
        return v;
    }

    inline vec5i vabs(vec5i v)
    {
        v.x = std::abs(v.x);
        v.y = std::abs(v.y);
        v.z = std::abs(v.z);
        v.w = std::abs(v.w);
        v.v = std::abs(v.v);
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
        result.v = (a.v + ((abs(a.v / b.v) + 1) * b.v)) % b.v;
        return result;
    }

    inline vec5i operator<<(vec5i lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        lhs.z <<= rhs;
        lhs.w <<= rhs;
        lhs.v <<= rhs;
        return lhs;
    }

    inline vec5i operator>>(vec5i lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        lhs.z >>= rhs;
        lhs.w >>= rhs;
        lhs.v >>= rhs;
        return lhs;
    }


    // VEC5U ------------------------------------------------------------------
    class vec5u {
        // Members
    private:
    protected:
    public:
        union
        {
            uint32_t _v[5];
            struct { uint32_t x, y, z, w, v; };
        };

        // Functions
    private:
    protected:
    public:
        vec5u& operator+=(const vec5u& rhs);
        vec5u& operator+=(const uint32_t rhs);
        vec5u& operator-=(const vec5u& rhs);
        vec5u& operator-=(const uint32_t rhs);
        vec5u& operator*=(const vec5u& rhs);
        vec5u& operator*=(const uint32_t rhs);
        vec5u& operator/=(const vec5u& rhs);
        vec5u& operator/=(const uint32_t rhs);
        bool operator==(const vec5u& rhs) const;
        bool operator!=(const vec5u& rhs) const;
        uint32_t& operator[](uint32_t idx);
        uint32_t operator[](uint32_t idx) const;

        vec5u();
        vec5u(uint32_t v);
        vec5u(uint32_t x, uint32_t y, uint32_t z, uint32_t w, uint32_t v);
        vec5u(const vec5f& fvec);
        vec5u(const vec5i& ivec);
    };

    inline vec5u operator+(vec5u lhs, const vec5u& rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5u operator+(vec5u lhs, const uint32_t rhs)
    {
        lhs += rhs;
        return lhs;
    }

    inline vec5u operator-(vec5u lhs, const vec5u& rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec5u operator-(vec5u lhs, const uint32_t rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    inline vec5u operator*(vec5u lhs, const vec5u& rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec5u operator*(vec5u lhs, const uint32_t rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    inline vec5u operator/(vec5u lhs, const vec5u& rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec5u operator/(vec5u lhs, const uint32_t rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    inline vec5u clamp(vec5u v, const vec5u& vMin, const vec5u& vMax)
    {
        v.x = std::max(std::min(v.x, vMax.x), vMin.x);
        v.y = std::max(std::min(v.y, vMax.y), vMin.y);
        v.z = std::max(std::min(v.z, vMax.z), vMin.z);
        v.w = std::max(std::min(v.w, vMax.w), vMin.w);
        v.v = std::max(std::min(v.v, vMax.v), vMin.v);
        return v;
    }

    inline vec5u clamp(vec5u v, const uint32_t vMin, const uint32_t vMax)
    {
        v.x = std::max(std::min(v.x, vMax), vMin);
        v.y = std::max(std::min(v.y, vMax), vMin);
        v.z = std::max(std::min(v.z, vMax), vMin);
        v.w = std::max(std::min(v.w, vMax), vMin);
        v.v = std::max(std::min(v.v, vMax), vMin);
        return v;
    }

    inline vec5u operator<<(vec5u lhs, const uint32_t rhs)
    {
        lhs.x <<= rhs;
        lhs.y <<= rhs;
        lhs.z <<= rhs;
        lhs.w <<= rhs;
        lhs.v <<= rhs;
        return lhs;
    }

    inline vec5u operator>>(vec5u lhs, const uint32_t rhs)
    {
        lhs.x >>= rhs;
        lhs.y >>= rhs;
        lhs.z >>= rhs;
        lhs.w >>= rhs;
        lhs.v >>= rhs;
        return lhs;
    }
}