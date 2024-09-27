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
        vec3f min;
        vec3f max;

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

        void padToMin();

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
        vec4i min;
        vec4i max;

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
        vec4f min;
        vec4f max;

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

        void padToMin();

        void reset();

        aabb4();
        aabb4(const vec4f& min, const vec4f& max);
        aabb4(const aabb4i& otheri);
        ~aabb4() {}
    };
    // END AABB4 ----------------------------------------------------------------

}
