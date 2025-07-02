/*
vec.cpp
Janury 2021
Contributors:
Justin Jensen
*/

#include "vec.h"
#include <algorithm>

namespace hxm
{
    // VEC2F ----------------------------------------------------------------------
    vec2f& vec2f::operator+=(const vec2f& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2f& vec2f::operator-=(const vec2f& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    vec2f& vec2f::operator*=(const vec2f& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    vec2f& vec2f::operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    vec2f& vec2f::operator/=(const vec2f& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    vec2f& vec2f::operator/=(float rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    bool vec2f::operator==(const vec2f& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    bool vec2f::operator!=(const vec2f& rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    float& vec2f::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    float vec2f::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    uint32_t vec2f::minCompIdx() const
    {
        uint32_t minIdx = 0;
        float minVal = x;
        if (y < minVal)
        {
            minIdx = 1;
            minVal = y;
        }

        return minIdx;
    }

    float vec2f::dot(const vec2f& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y);
    }

    float vec2f::length() const
    {
        return sqrt(this->dot(*this));
    }

    vec2f& vec2f::normalize()
    {
        return (*this) /= (length());
    }

    vec2f::vec2f() : x(0), y(0) {}
    vec2f::vec2f(float v) : x(v), y(v) {}
    vec2f::vec2f(float x, float y) : x(x), y(y) {}
    vec2f::vec2f(const vec3f& v) : x(v.x), y(v.y) {}
    vec2f::vec2f(const vec2i& v) : x(v.x), y(v.y) {}
    vec2f::vec2f(const vec2u& v) : x(float(v.x)), y(float(v.y)) {}

    vec2f::~vec2f() {}


    // VEC2I ----------------------------------------------------------------------
    vec2i& vec2i::operator+=(const vec2i& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2i& vec2i::operator-=(const vec2i& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    bool vec2i::operator==(const vec2i& other) const
    {
        return x == other.x && y == other.y;
    }

    bool vec2i::operator!=(const vec2i& rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    int32_t& vec2i::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    int32_t vec2i::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    vec2i::vec2i() : x(0), y(0) {}
    vec2i::vec2i(int32_t v) : x(v), y(v) {}
    vec2i::vec2i(int32_t x, int32_t y) : x(x), y(y) {}
    vec2i::vec2i(const vec2f& fvec) : x(int32_t(fvec.x)), y(int32_t(fvec.y)) {}
    vec2i::vec2i(const vec2u& v) : x(int32_t(v.x)), y(int32_t(v.y)) {}
    vec2i::~vec2i() {}


    // VEC2U ----------------------------------------------------------------------
    uint32_t& vec2u::operator[](uint32_t idx) {
        return _v[idx];
    }

    uint32_t vec2u::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    vec2u& vec2u::operator+=(const vec2u& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2u& vec2u::operator-=(const vec2u& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    bool vec2u::operator==(const vec2u& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    bool vec2u::operator!=(const vec2u& rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

    vec2u::vec2u() : x(0), y(0) {}
    vec2u::vec2u(uint32_t v) : x(v), y(v) {}
    vec2u::vec2u(uint32_t x, uint32_t y) : x(x), y(y) {}
    vec2u::vec2u(const vec2f& v)
    {
        x = uint32_t(std::max(0.0f, v.x));
        y = uint32_t(std::max(0.0f, v.y));
    }
    vec2u::vec2u(const vec2i& v)
    {
        x = std::max(0, v.x);
        y = std::max(0, v.y);
    }
    vec2u::~vec2u() {}


    // VEC3F ----------------------------------------------------------------------
    vec3f& vec3f::operator+=(const vec3f& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vec3f& vec3f::operator-=(const vec3f& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    vec3f& vec3f::operator*=(const vec3f& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    vec3f& vec3f::operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    vec3f& vec3f::operator/=(const vec3f& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    vec3f& vec3f::operator/=(float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    float& vec3f::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    float vec3f::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec3f::operator==(const vec3f& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool vec3f::operator!=(const vec3f& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    uint32_t vec3f::minCompIdx() const
    {
        uint32_t minIdx = 0;
        float minVal = x;
        if (y < minVal)
        {
            minIdx = 1;
            minVal = y;
        }

        if (z < minVal)
        {
            minIdx = 2;
            minVal = z;
        }

        return minIdx;
    }

    float vec3f::dot(const vec3f& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
    }

    float vec3f::length() const
    {
        return sqrt(this->dot(*this));
    }

    vec3f& vec3f::normalize()
    {
        return (*this) /= (length());
    }

    vec3f::vec3f() : x(0), y(0), z(0) {}
    vec3f::vec3f(float v) : x(v), y(v), z(v) {}
    vec3f::vec3f(float x, float y, float z) : x(x), y(y), z(z) {}
    vec3f::vec3f(const vec2f& v, float z) : x(v.x), y(v.y), z(z) {}
    vec3f::vec3f(const vec3u& v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}
    vec3f::vec3f(const vec3i& v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}
    vec3f::vec3f(const vec4f& v) : x(v.x), y(v.y), z(v.z) {}
    vec3f::vec3f(const vec4u& v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}
    vec3f::~vec3f() {}


    // VEC3I ----------------------------------------------------------------------
    vec3i& vec3i::operator+=(const vec3i& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vec3i& vec3i::operator-=(const vec3i& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    bool vec3i::operator==(const vec3i& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

    bool vec3i::operator!=(const vec3i& rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    int32_t& vec3i::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    int32_t vec3i::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    vec3i::vec3i() : x(0), y(0), z(0) {}
    vec3i::vec3i(int32_t v) : x(v), y(v), z(v) {}
    vec3i::vec3i(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
    vec3i::vec3i(const vec3f& fvec) : x(int32_t(fvec.x)), y(int32_t(fvec.y)), z(int32_t(fvec.z)) {}
    vec3i::vec3i(const vec3u& v) : x(int32_t(v.x)), y(int32_t(v.y)), z(int32_t(v.z)) {}
    vec3i::~vec3i() {}


    // VEC3U ----------------------------------------------------------------------
    uint32_t& vec3u::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    uint32_t vec3u::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec3u::operator==(const vec3u& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool vec3u::operator!=(const vec3u& rhs) const
    {
        return !(x == rhs.x && y == rhs.y && z == rhs.z);
    }

    vec3u::vec3u() : x(0), y(0), z(0) {}
    vec3u::vec3u(uint32_t v) : x(v), y(v), z(v) {}
    vec3u::vec3u(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) {}
    vec3u::vec3u(const vec3f& v)
    {
        x = uint32_t(std::max(0.0f, v.x));
        y = uint32_t(std::max(0.0f, v.y));
        z = uint32_t(std::max(0.0f, v.z));
    }
    vec3u::vec3u(const vec3i& v)
    {
        x = std::max(0, v.x);
        y = std::max(0, v.y);
        z = std::max(0, v.z);
    }
    vec3u::~vec3u() {}


    // VEC3U8 ---------------------------------------------------------------------
    uint8_t& vec3u8::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    uint8_t vec3u8::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec3u8::operator==(const vec3u8& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool vec3u8::operator!=(const vec3u8& rhs) const
    {
        return !(x == rhs.x && y == rhs.y && z == rhs.z);
    }

    vec3u8::vec3u8() : x(0), y(0), z(0) {}
    vec3u8::vec3u8(uint8_t v) : x(v), y(v), z(v) {}
    vec3u8::vec3u8(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) {}
    vec3u8::vec3u8(const vec3f& v)
    {
        x = uint8_t(std::max(0.0f, v.x));
        y = uint8_t(std::max(0.0f, v.y));
        z = uint8_t(std::max(0.0f, v.z));
    }
    vec3u8::vec3u8(const vec3i& v)
    {
        x = std::max(0, v.x);
        y = std::max(0, v.y);
        z = std::max(0, v.z);
    }
    vec3u8::vec3u8(const vec3u& v)
    {
        x = uint8_t(std::max(0u, v.x));
        y = uint8_t(std::max(0u, v.y));
        z = uint8_t(std::max(0u, v.z));
    }
    vec3u8::~vec3u8() {}


    // VEC4F ----------------------------------------------------------------------
    vec4f& vec4f::operator+=(const vec4f& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    vec4f& vec4f::operator-=(const vec4f& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    vec4f& vec4f::operator*=(const vec4f& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        return *this;
    }

    vec4f& vec4f::operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    vec4f& vec4f::operator/=(const vec4f& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    vec4f& vec4f::operator/=(float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    bool vec4f::operator==(const vec4f& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4f::operator!=(const vec4f& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    float& vec4f::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    float vec4f::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    vec4f& vec4f::copy(const vec4f& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    vec4f& vec4f::set(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        return *this;
    }

    uint32_t vec4f::minCompIdx() const
    {
        uint32_t minIdx = 0;
        float minVal = FLT_MAX;

        // don't consider components with -infinity values
        if (!isinf(x) && x < minVal)
        {
            minIdx = 0;
            minVal = x;
        }

        if (!isinf(y) && y < minVal)
        {
            minIdx = 1;
            minVal = y;
        }

        if (!isinf(z) && z < minVal)
        {
            minIdx = 2;
            minVal = z;
        }

        if (!isinf(w) && w < minVal)
        {
            minIdx = 3;
            minVal = w;
        }

        return minIdx;
    }

    float vec4f::dot(const vec4f& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
    }

    float vec4f::length() const
    {
        return sqrt(this->dot(*this));
    }

    vec4f& vec4f::normalize()
    {
        return (*this) /= (length());
    }



    vec4f::vec4f() : x(0), y(0), z(0), w(0) {}
    vec4f::vec4f(float v) : x(v), y(v), z(v), w(v) {}
    vec4f::vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    vec4f::vec4f(const vec3f& vec) : x(vec.x), y(vec.y), z(vec.z), w(0) {}
    vec4f::vec4f(const vec3f& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}
    vec4f::vec4f(const vec4u& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    vec4f::vec4f(const vec4i& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    vec4f::vec4f(const vec5f& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    vec4f::~vec4f() {}

    // VEC4I ----------------------------------------------------------------------
    vec4i& vec4i::operator+=(const vec4i& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    vec4i& vec4i::operator-=(const vec4i& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    vec4i& vec4i::operator+=(int value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }

    int32_t& vec4i::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    int32_t vec4i::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec4i::operator==(const vec4i& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4i::operator!=(const vec4i& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    bool vec4i::operator==(const vec4u& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    vec4i::vec4i() : x(0), y(0), z(0), w(0) {}
    vec4i::vec4i(int32_t v) : x(v), y(v), z(v), w(v) {}
    vec4i::vec4i(int32_t x, int32_t y, int32_t z, int32_t w) : x(x), y(y), z(z), w(w) {}
    vec4i::vec4i(const vec4f& fvec)
    {
        x = (int32_t)fvec.x;
        y = (int32_t)fvec.y;
        z = (int32_t)fvec.z;
        w = (int32_t)fvec.w;
    }
    vec4i::vec4i(const vec4u& uvec)
    {
        x = (int32_t)uvec.x;
        y = (int32_t)uvec.y;
        z = (int32_t)uvec.z;
        w = (int32_t)uvec.w;
    }
    vec4i::~vec4i() {}

    // VEC4U ----------------------------------------------------------------------
    uint32_t& vec4u::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    uint32_t vec4u::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec4u::operator==(const vec4u& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4u::operator==(const vec4i& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4u::operator!=(const vec4u& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    // integer division
    vec4u& vec4u::operator/=(size_t value)
    {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    vec4u& vec4u::operator%=(size_t value)
    {
        x %= value;
        y %= value;
        z %= value;
        w %= value;
        return *this;
    }

    vec4u& vec4u::operator+=(size_t rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        w += rhs;
        return *this;
    }

    vec4u& vec4u::operator+=(const vec4u& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    vec4u& vec4u::operator-=(const vec4u& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    vec4u& vec4u::operator-=(const int& rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        w -= rhs;
        return *this;
    }

    vec4u::vec4u() : x(0), y(0), z(0), w(0) {}
    vec4u::vec4u(uint32_t v) : x(v), y(v), z(v), w(v) {}
    vec4u::vec4u(uint32_t x, uint32_t y, uint32_t z, uint32_t w) : x(x), y(y), z(z), w(w) {}
    vec4u::vec4u(const vec4f& v)
    {
        x = uint32_t(std::max(0.0f, v.x));
        y = uint32_t(std::max(0.0f, v.y));
        z = uint32_t(std::max(0.0f, v.z));
        w = uint32_t(std::max(0.0f, v.w));
    }
    vec4u::vec4u(const vec4i& v)
    {
        x = std::max(0, v.x);
        y = std::max(0, v.y);
        z = std::max(0, v.z);
        w = std::max(0, v.w);
    }
    vec4u::~vec4u() {}


    // VEC4U8 ---------------------------------------------------------------------
    uint8_t& vec4u8::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    uint8_t vec4u8::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec4u8::operator==(const vec4u8& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4u8::operator!=(const vec4u8& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    vec4u8& vec4u8::operator+=(size_t rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        w += rhs;
        return *this;
    }

    vec4u8& vec4u8::operator+=(const vec4u8& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    vec4u8& vec4u8::operator-=(const vec4u8& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    vec4u8& vec4u8::operator-=(const int& rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        w -= rhs;
        return *this;
    }

    vec4u8::vec4u8() : x(0), y(0), z(0), w(0) {}
    vec4u8::vec4u8(uint8_t v) : x(v), y(v), z(v), w(v) {}
    vec4u8::vec4u8(uint8_t x, uint8_t y, uint8_t z, uint8_t w) : x(x), y(y), z(z), w(w) {}
    vec4u8::vec4u8(const vec4f& v)
    {
        x = uint8_t(std::max(0.0f, v.x));
        y = uint8_t(std::max(0.0f, v.y));
        z = uint8_t(std::max(0.0f, v.z));
        w = uint8_t(std::max(0.0f, v.w));
    }
    vec4u8::vec4u8(const vec4i& v)
    {
        x = uint8_t(std::max(0, v.x));
        y = uint8_t(std::max(0, v.y));
        z = uint8_t(std::max(0, v.z));
        w = uint8_t(std::max(0, v.w));
    }
    vec4u8::vec4u8(const vec4u& v)
    {
        x = uint8_t(std::max(0u, v.x));
        y = uint8_t(std::max(0u, v.y));
        z = uint8_t(std::max(0u, v.z));
        w = uint8_t(std::max(0u, v.w));
    }
    vec4u8::~vec4u8() {}


    // VEC5F ----------------------------------------------------------------------
    vec5f& vec5f::operator+=(const vec5f& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        v += rhs.v;
        return *this;
    }

    vec5f& vec5f::operator+=(float rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        w += rhs;
        v += rhs;
        return *this;
    }

    vec5f& vec5f::operator-=(const vec5f& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        v -= rhs.v;
        return *this;
    }

    vec5f& vec5f::operator-=(float rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        w -= rhs;
        v -= rhs;
        return *this;
    }

    vec5f& vec5f::operator*=(const vec5f& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        v *= rhs.v;
        return *this;
    }

    vec5f& vec5f::operator*=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        v *= rhs;
        return *this;
    }

    vec5f& vec5f::operator/=(const vec5f& rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        v /= rhs.v;
        return *this;
    }

    vec5f& vec5f::operator/=(float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        v /= rhs;
        return *this;
    }

    bool vec5f::operator==(const vec5f& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w && v == other.v;
    }

    bool vec5f::operator!=(const vec5f& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w || v != other.v;
    }

    float& vec5f::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    float vec5f::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    vec5f& vec5f::copy(const vec5f& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
        this->v = v.v;
        return *this;
    }

    vec5f& vec5f::set(float x, float y, float z, float w, float v)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->v = v;
        return *this;
    }

    uint32_t vec5f::minCompIdx() const
    {
        uint32_t minIdx = 0;
        float minVal = FLT_MAX;

        // don't consider components with -infinity values
        if (!isinf(x) && x < minVal)
        {
            minIdx = 0;
            minVal = x;
        }

        if (!isinf(y) && y < minVal)
        {
            minIdx = 1;
            minVal = y;
        }

        if (!isinf(z) && z < minVal)
        {
            minIdx = 2;
            minVal = z;
        }

        if (!isinf(w) && w < minVal)
        {
            minIdx = 3;
            minVal = w;
        }

        if (!isinf(v) && v < minVal)
        {
            minIdx = 4;
            minVal = v;
        }

        return minIdx;
    }

    float vec5f::dot(const vec5f& rhs) const
    {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w) + (v * rhs.v);
    }

    float vec5f::length() const
    {
        return sqrt(this->dot(*this));
    }

    vec5f& vec5f::normalize()
    {
        return (*this) /= (length());
    }

    vec5f::vec5f() : x(0), y(0), z(0), w(0), v(0) {}
    vec5f::vec5f(float v) : x(v), y(v), z(v), w(v), v(v) {}
    vec5f::vec5f(float x, float y, float z, float w, float v) : x(x), y(y), z(z), w(w), v(v) {}
    vec5f::vec5f(const vec3f& vec) : x(vec.x), y(vec.y), z(vec.z), w(0), v(0) {}
    vec5f::vec5f(const vec3f& vec, float w, float v) : x(vec.x), y(vec.y), z(vec.z), w(w), v(v) {}
    vec5f::vec5f(const vec4f& vec, float v) : x(vec.x), y(vec.y), z(vec.z), w(vec.w), v(v) {}
    vec5f::vec5f(const vec4u& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w), v(0) {}
    vec5f::vec5f(const vec4i& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w), v(0) {}
    vec5f::vec5f(const vec5i& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w), v(vec.v) {}
    vec5f::~vec5f() {}


    // VEC5I ----------------------------------------------------------------------
    vec5i& vec5i::operator+=(const vec5i& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        v += rhs.v;
        return *this;
    }

    vec5i& vec5i::operator-=(const vec5i& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        v -= rhs.v;
        return *this;
    }

    vec5i& vec5i::operator+=(int value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        v += value;
        return *this;
    }

    int32_t& vec5i::operator[](uint32_t idx)
    {
        return _v[idx];
    }

    int32_t vec5i::operator[](uint32_t idx) const
    {
        return _v[idx];
    }

    bool vec5i::operator==(const vec5i& other) const
    {
        return x == other.x && y == other.y && z == other.z && w == other.w && v == other.v;
    }

    bool vec5i::operator!=(const vec5i& other) const
    {
        return x != other.x || y != other.y || z != other.z || w != other.w || v != other.v;
    }

    vec5i::vec5i() : x(0), y(0), z(0), w(0), v(0) {}
    vec5i::vec5i(int32_t v) : x(v), y(v), z(v), w(v), v(v) {}
    vec5i::vec5i(int32_t x, int32_t y, int32_t z, int32_t w, int32_t v) : x(x), y(y), z(z), w(w), v(v) {}
    vec5i::~vec5i() {}
}
