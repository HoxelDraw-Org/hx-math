/*
aabb.h
April 11, 2023
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"

#define AABB_MIN 1e-4f

namespace hxm
{
    // Forward declarations of classes here
    class aabb3f;
    class aabb4f;
    class aabb4i;

    typedef aabb3f aabb3;
    typedef aabb4f aabb4;

    // AABB3F -------------------------------------------------------------------
    class aabb3f
    {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
    public:
        union
        {
            float _v[6];                // { min_x, min_y, min_z, max_x, max_y, max_z }
            struct { vec3f _b[2]; };    // { min, max }
            struct { vec3f min, max; }; // min, max
        };

        // Functions
    private:
    protected:
    public:
        void addPoint(const vec3f& pt);

        vec3f dim() const;

        bool empty() const;
        bool isValid() const;

        void addAABB(const aabb3f& other);

        aabb3f intersect(const aabb3f& other) const;

        float area() const; // surface area
        float volume() const;

        vec3f centroid() const;
        float centroid(uint32_t axis) const;    // the centroid of a single axis

        void padToMin(float pad = AABB_MIN);

        vec3f& operator[](uint32_t idx);        // 0: min, 1: max
        vec3f operator[](uint32_t idx) const;
        aabb3f& operator+=(const aabb3f& other);
        aabb3f& operator+=(const vec3f& v);

        void reset();

        aabb3f();
        aabb3f(const vec3f& min, const vec3f& max);
        ~aabb3f() {}
    };
    // END AABB3 ----------------------------------------------------------------

    // AABB4I -------------------------------------------------------------------
    class aabb4i
    {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
    public:
        union
        {
            int32_t _v[8];              // { min_x, min_y, min_z, min_w, max_x, max_y, max_z, max_w }
            struct { vec4i _b[2]; };    // { min, max }
            struct { vec4i min, max; }; // min, max
        };

        // Functions
    private:
    protected:
    public:
        // halfOpenInterval means the AABB includes _min and includes _max-1, but does not include _max
        void addPoint(const vec4i& pt, bool halfOpenInterval = false);

        vec4i dim() const;

        bool empty() const;
        bool isValid(bool halfOpenInterval = true) const;
        
        void addAABB(const aabb4i& other);

        aabb4i intersect(const aabb4i& other) const;
        aabb4i intersect(const vec4i& otherStart, const vec4i& otherEnd) const;
        
        int volume(bool halfOpenInterval = true) const; // surface volume
        int bulk(bool halfOpenInterval = true) const;

        void reset();

        vec4i& operator[](uint32_t idx);        // 0: min, 1: max
        vec4i operator[](uint32_t idx) const;
        aabb4i& operator+=(const aabb4i& other);
    
        aabb4i();
        aabb4i(const vec4i& min, const vec4i& max);
        ~aabb4i() {}
    };
    // END AABBI ---------------------------------------------------------------


    // AABB4F -------------------------------------------------------------------
    class aabb4f
    {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
    public:
        union
        {
            float _v[8];              // { min_x, min_y, min_z, min_w, max_x, max_y, max_z, max_w }
            struct { vec4f _b[2]; };    // { min, max }
            struct { vec4f min, max; }; // min, max
        };

        // Functions
    private:
    protected:
    public:
        void addPoint(const vec4f& pt);

        vec4f dim() const;

        bool empty() const;
        bool isValid() const;

        void addAABB(const aabb4f& other);

        aabb4f intersect(const aabb4f& other) const;
        
        float volume() const; // surface volume
        float bulk() const;

        vec4f centroid() const;
        float centroid(uint32_t axis) const;    // the centroid of a single axis

        void padToMin(float pad = AABB_MIN);

        void reset();

        vec4f& operator[](uint32_t idx);        // 0: min, 1: max
        vec4f operator[](uint32_t idx) const;
        aabb4f& operator+=(const aabb4f& other);
        aabb4f& operator+=(const vec4f& v);

        aabb4f();
        aabb4f(const vec4f& min, const vec4f& max);
        aabb4f(const aabb4i& otheri);
        ~aabb4f() {}
    };
    // END AABB4 ----------------------------------------------------------------

}
