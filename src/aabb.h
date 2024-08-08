/*
aabb.h
April 11, 2023
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"

namespace hxm
{
    // AABBI -------------------------------------------------------------------
    class aabbi
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
        
        void addAABB(const aabbi& other);

        aabbi intersect(const aabbi& other) const;
        aabbi intersect(const vec4i& otherStart, const vec4i& otherEnd) const;

        void reset();
    
        aabbi();
        aabbi(const vec4i& min, const vec4i& max);
        ~aabbi() {}
    };
    // END AABBI ---------------------------------------------------------------


    // AABB (float) ------------------------------------------------------------
    class aabb
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

        void addAABB(const aabb& other);

        aabb intersect(const aabb& other) const;

        vec4f centroid() const;

        void reset();

        aabb();
        aabb(const vec4f& min, const vec4f& max);
        aabb(const aabbi& otheri);
        ~aabb() {}
    };
    // END AABB ----------------------------------------------------------------

}
