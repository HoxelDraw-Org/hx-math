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
    // AABB3 (float) ------------------------------------------------------------
    class aabb3
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

        void addAABB(const aabb3& other);

        aabb3 intersect(const aabb3& other) const;

        float volume() const;

        vec3f centroid() const;
        float centroid(uint32_t axis) const;    // the centroid of a single axis

        void padToMin(float pad = AABB_MIN);

        vec3f& operator[](uint32_t idx);        // 0: min, 1: max
        vec3f operator[](uint32_t idx) const;
        aabb3& operator+=(const aabb3& other);
        aabb3& operator+=(const vec3f& v);

        void reset();

        aabb3();
        aabb3(const vec3f& min, const vec3f& max);
        ~aabb3() {}
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


    // AABB4 (float) ------------------------------------------------------------
    class aabb4
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

        void addAABB(const aabb4& other);

        aabb4 intersect(const aabb4& other) const;
        
        float bulk() const;

        vec4f centroid() const;
        float centroid(uint32_t axis) const;    // the centroid of a single axis

        void padToMin(float pad = AABB_MIN);

        void reset();

        vec4f& operator[](uint32_t idx);        // 0: min, 1: max
        vec4f operator[](uint32_t idx) const;
        aabb4& operator+=(const aabb4& other);
        aabb4& operator+=(const vec4f& v);

        aabb4();
        aabb4(const vec4f& min, const vec4f& max);
        aabb4(const aabb4i& otheri);
        ~aabb4() {}
    };
    // END AABB4 ----------------------------------------------------------------

}
