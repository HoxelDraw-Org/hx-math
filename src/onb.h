/*
onb.h
October 2024
Copyright Justin Jensen
*/

#pragma once

#include "vec.h"
#include <cmath>

namespace hxm
{
    class onb
    {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
        vec4f _u, _v, _s, _t;
    public:

        // Functions
    private:
    protected:
        inline vec4u sortAbsAsc(const vec4f& v) const;
        inline void makeTwoNonParallel(const vec4f& v, vec4f& out_a, vec4f& out_b) const;
        inline void init(const vec4f& n, const vec4f& np1, const vec4f& np2);
    public:
        const vec4f& u() const { return _u; }
        const vec4f& v() const { return _v; }
        const vec4f& s() const { return _s; }
        const vec4f& t() const { return _t; }

        vec4f transform(const vec4f& v) const;

        void init_Shirley(const vec4f& norm);  // Pete Shirley's method from Ray Tracing in One Weekend

        onb(const vec4f& norm);
        onb();
    };
}
