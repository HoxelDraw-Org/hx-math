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
    vec2f& vec2f::operator+=(const vec2f& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2f& vec2f::operator-=(const vec2f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    vec2f& vec2f::operator*=(const vec2f& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    vec2f& vec2f::operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    vec2f& vec2f::operator/=(const vec2f& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    vec2f& vec2f::operator/=(float rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    float& vec2f::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw "index out of bounds";
        }
    }

    vec2f vec2f::operator-() const {
        return vec2f(-x, -y);
    }

    uint32_t vec2f::minCompIdx() const {
        uint32_t minIdx = 0;
        float minVal = x;
        if (y < minVal)
        {
            minIdx = 1;
            minVal = y;
        }

        return minIdx;
    }

    float vec2f::dot(const vec2f& rhs) const {
        return (x * rhs.x) + (y * rhs.y);
    }

    float vec2f::length() const {
        return sqrt(this->dot(*this));
    }

    vec2f& vec2f::normalize() {
        return (*this) /= (length());
    }

    vec2f::vec2f() : x(0), y(0) {}
    vec2f::vec2f(float v) : x(v), y(v) {}
    vec2f::vec2f(float x, float y) : x(x), y(y) {}
    vec2f::vec2f(const vec3f& v) : x(v.x), y(v.y) {}

    vec2f::vec2f(const vec2u& v) : x(float(v.x)), y(float(v.y)) {}

    vec2f::~vec2f() {}


    // VEC2I ----------------------------------------------------------------------
    vec2i& vec2i::operator+=(const vec2i& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2i& vec2i::operator-=(const vec2i& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    bool vec2i::operator==(const vec2i& other)
    {
        return x == other.x && y == other.y;
    }

    bool vec2i::operator!=(const vec2i& rhs)
    {
        return x != rhs.x || y != rhs.y;
    }

    int32_t& vec2i::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw "index out of bounds";
        }
    }

    vec2i::vec2i() : x(0), y(0) {}
    vec2i::vec2i(int32_t v) : x(v), y(v) {}
    vec2i::vec2i(int32_t x, int32_t y) : x(x), y(y) {}
    vec2i::vec2i(const vec2f& fvec) : x(int32_t(fvec.x)), y(int32_t(fvec.y)) {}
    vec2i::vec2i(const vec2u& v) : x(int32_t(v.x)), y(int32_t(v.y)) {}
    vec2i::~vec2i() {}


    // VEC2U ----------------------------------------------------------------------
    uint32_t& vec2u::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw "index out of bounds";
        }
    }

    uint32_t vec2u::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        default:
            throw "index out of bounds";
        }
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

    bool vec2u::operator==(const vec2u& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }

    bool vec2u::operator!=(const vec2u& rhs)
    {
        return x != rhs.x || y != rhs.y;
    }

    vec2u::vec2u() : x(0), y(0) {}
    vec2u::vec2u(uint32_t v) : x(v), y(v) {}
    vec2u::vec2u(uint32_t x, uint32_t y) : x(x), y(y) {}
    vec2u::vec2u(const vec2i& v) : x(v.x), y(v.y) {}
    vec2u::~vec2u() {}


    // VEC3F ----------------------------------------------------------------------
    vec3f& vec3f::operator+=(const vec3f& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    vec3f& vec3f::operator-=(const vec3f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    vec3f& vec3f::operator*=(const vec3f& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    vec3f& vec3f::operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    vec3f& vec3f::operator/=(const vec3f& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    vec3f& vec3f::operator/=(float rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    vec3f vec3f::operator-() const {
        return vec3f(-x, -y, -z);
    }

    float& vec3f::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw "index out of bounds";
        }
    }

    float vec3f::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw "index out of bounds";
        }
    }

    bool vec3f::operator==(const vec3f& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    uint32_t vec3f::minCompIdx() const {
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

    float vec3f::dot(const vec3f& rhs) const {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
    }

    float vec3f::length() const {
        return sqrt(this->dot(*this));
    }

    vec3f& vec3f::normalize() {
        return (*this) /= (length());
    }

    vec3f::vec3f() : x(0), y(0), z(0) {}
    vec3f::vec3f(float v) : x(v), y(v), z(v) {}
    vec3f::vec3f(float x, float y, float z) : x(x), y(y), z(z) {}
    vec3f::vec3f(const vec2f& v, float z) : x(v.x), y(v.y), z(z) {}
    vec3f::vec3f(const vec4f& v) : x(v.x), y(v.y), z(v.z) {}
    vec3f::vec3f(const vec3u& v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}
    vec3f::vec3f(const vec4u& v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}
    vec3f::~vec3f() {}


    // VEC3U ----------------------------------------------------------------------
    uint32_t& vec3u::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw "index out of bounds";
        }
    }

    bool vec3u::operator==(const vec3u& rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool vec3u::operator==(const vec3u& rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool vec3u::operator!=(const vec3u& rhs)
    {
        return !(x == rhs.x && y == rhs.y && z == rhs.z);
    }

    vec3u::vec3u() : x(0), y(0), z(0) {}
    vec3u::vec3u(uint32_t v) : x(v), y(v), z(v) {}
    vec3u::vec3u(uint32_t x, uint32_t y, uint32_t z) : x(x), y(y), z(z) {}
    vec3u::~vec3u() {}


    // VEC4F ----------------------------------------------------------------------
    vec4f& vec4f::operator+=(const vec4f& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    vec4f& vec4f::operator-=(const vec4f& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    vec4f& vec4f::operator*=(const vec4f& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        return *this;
    }

    vec4f& vec4f::operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    vec4f& vec4f::operator/=(const vec4f& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    vec4f& vec4f::operator/=(float rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        return *this;
    }

    bool vec4f::operator==(const vec4f& other)
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4f::operator!=(const vec4f& other)
    {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    float& vec4f::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw "index out of bounds";
        }
    }

    float vec4f::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw "index out of bounds";
        }
    }

    vec4f vec4f::operator-() const {
        return vec4f(-x, -y, -z, -w);
    }

    vec4f& vec4f::copy(const vec4f& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }

    vec4f& vec4f::set(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        return *this;
    }

    uint32_t vec4f::minCompIdx() const {
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

    float vec4f::dot(const vec4f& rhs) const {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w);
    }

    float vec4f::length() const {
        return sqrt(this->dot(*this));
    }

    vec4f& vec4f::normalize() {
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

    int32_t& vec4i::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw "index out of bounds";
        }
    }

    int32_t vec4i::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw "index out of bounds";
        }
    }

    bool vec4i::operator==(const vec4i& other) {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4i::operator!=(const vec4i& other) {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    bool vec4i::operator==(const vec4u& other)
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

    //vec4i operator+(vec4i lhs, const vec4i& rhs) {
    //    lhs += rhs;
    //    return lhs;
    //}
    //
    //vec4i operator-(vec4i lhs, const vec4i& rhs)
    //{
    //    lhs -= rhs;
    //    return lhs;
    //}


    // VEC4U ----------------------------------------------------------------------
    uint32_t& vec4u::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw "index out of bounds";
        }
    }

    uint32_t vec4u::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw "index out of bounds";
        }
    }

    bool vec4u::operator==(const vec4u& other) {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4u::operator==(const vec4i& other)
    {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    bool vec4u::operator!=(const vec4u& other)
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
    vec4u::vec4u(const vec4i& v)
    {
        x = std::max(0, v.x);
        y = std::max(0, v.y);
        z = std::max(0, v.z);
        w = std::max(0, v.w);
    }
    vec4u::~vec4u() {}

    //vec4u operator/(vec4u lhs, size_t rhs)
    //{
    //    lhs /= rhs;
    //    return lhs;
    //}
    //
    //vec4u operator%(vec4u lhs, size_t rhs)
    //{
    //    lhs %= rhs;
    //    return lhs;
    //}

    // VEC5F ----------------------------------------------------------------------
    vec5f& vec5f::operator+=(const vec5f& rhs) {
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

    vec5f& vec5f::operator-=(const vec5f& rhs) {
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

    vec5f& vec5f::operator*=(const vec5f& rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        v *= rhs.v;
        return *this;
    }

    vec5f& vec5f::operator*=(float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        v *= rhs;
        return *this;
    }

    vec5f& vec5f::operator/=(const vec5f& rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        v /= rhs.v;
        return *this;
    }

    vec5f& vec5f::operator/=(float rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
        v /= rhs;
        return *this;
    }

    bool vec5f::operator==(const vec5f& other)
    {
        return x == other.x && y == other.y && z == other.z && w == other.w && v == other.v;
    }

    bool vec5f::operator!=(const vec5f& other)
    {
        return x != other.x || y != other.y || z != other.z || w != other.w || v != other.v;
    }

    float& vec5f::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        case 4:
            return v;
        default:
            throw "index out of bounds";
        }
    }

    float vec5f::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        case 4:
            return v;
        default:
            throw "index out of bounds";
        }
    }

    vec5f vec5f::operator-() const {
        return vec5f(-x, -y, -z, -w, -v);
    }

    vec5f& vec5f::copy(const vec5f& v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;
        this->v = v.v;
        return *this;
    }

    vec5f& vec5f::set(float x, float y, float z, float w, float v) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->v = v;
        return *this;
    }

    uint32_t vec5f::minCompIdx() const {
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

    float vec5f::dot(const vec5f& rhs) const {
        return (x * rhs.x) + (y * rhs.y) + (z * rhs.z) + (w * rhs.w) + (v * rhs.v);
    }

    float vec5f::length() const {
        return sqrt(this->dot(*this));
    }

    vec5f& vec5f::normalize() {
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
    vec5f::vec5f(const vec5i& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w), v(vec.r) {}
    vec5f::~vec5f() {}


    // VEC5I ----------------------------------------------------------------------
    vec5i& vec5i::operator+=(const vec5i& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        r += rhs.r;
        return *this;
    }

    vec5i& vec5i::operator-=(const vec5i& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        r -= rhs.r;
        return *this;
    }

    vec5i& vec5i::operator+=(int value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        r += value;
        return *this;
    }

    int32_t& vec5i::operator[](uint32_t idx) {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        case 4:
            return r;
        default:
            throw "index out of bounds";
        }
    }

    int32_t vec5i::operator[](uint32_t idx) const
    {
        switch (idx)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        case 4:
            return r;
        default:
            throw "index out of bounds";
        }
    }

    bool vec5i::operator==(const vec5i& other) {
        return x == other.x && y == other.y && z == other.z && w == other.w && r == other.r;
    }

    bool vec5i::operator!=(const vec5i& other) {
        return x != other.x || y != other.y || z != other.z || w != other.w || r != other.r;
    }

    vec5i::vec5i() : x(0), y(0), z(0), w(0), r(0) {}
    vec5i::vec5i(int32_t v) : x(v), y(v), z(v), w(v), r(v) {}
    vec5i::vec5i(int32_t x, int32_t y, int32_t z, int32_t w, int32_t r) : x(x), y(y), z(z), w(w), r(r) {}
    vec5i::~vec5i() {}
}
