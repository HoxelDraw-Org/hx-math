/*
mat.h
September 27, 2022
Contributors:
Justin Jensen
*/

#pragma once

#include "vec.h"
#include "euler6.h"

// ---------------------------------------
// 
// NOTE: THESE ARE COLUMN-MAJOR MATRICES
// 
// ---------------------------------------

namespace hxm
{
    // Forward declarations
    class mat3;
    class mat4;
    class mat5;

    // MAT3 -------------------------------------------------------------------
    class mat3 {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
        union
        {
            float el[9];
            struct {
                float   m00, m10, m20, // column 0
                        m01, m11, m21, // column 1
                        m02, m12, m22; // column 2
            };
        };
    public:

        // Functions
    private:
    protected:
    public:

        mat3 operator*(const mat3& b) const;
        vec3f operator*(const vec3f& rhs) const;
        float& operator[](uint32_t idx);        // for setting values and non-const Mat4's
        float operator[](uint32_t idx) const;   // for reading values from const Mat4's
        bool operator==(const mat3& b) const;

        const float* data() const;

        void transpose();
        bool invert();

        // n[row][column]
        //  n23 == second row, third column
        void set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33);

        void makeTranslation(float x, float y);
        void makeTranslation(const vec2f& v);
        void makeScale(float x, float y);
        void makeScale(const vec2f& v);
        void makeScale(const float& v);
        void makeRotation(float theta);    // angle in radians

        vec2f right() const;
        vec2f up() const;

        float Determinant() const;

        static mat3 MakeTranslation(float x, float y);
        static mat3 MakeTranslation(const vec2f& v);
        static mat3 MakeRotation(float theta);  // radians
        static mat3 MakeScale(float x, float y);
        static mat3 MakeScale(const vec2f& v);
        static mat3 MakeScale(const float& v);
        static mat3 Transpose(const mat3& m);
        static mat3 Invert(const mat3& m);

        void setRows(const vec3f& r0, const vec3f& r1, const vec3f& r2);
        void setColumns(const vec3f& c0, const vec3f& c1, const vec3f& c2);

        mat3();
        ~mat3();
    };

    inline float Determinant(const mat3& m)
    {
        return m.Determinant();
    }

    // MAT4 -------------------------------------------------------------------
    class mat4 {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
        union
        {
            float el[16];   // column-major
            struct {
                float   m00, m10, m20, m30, // column 0
                        m01, m11, m21, m31, // column 1
                        m02, m12, m22, m32, // column 2
                        m03, m13, m23, m33; // column 3
            };
        };
    public:

        // Functions
    private:
    protected:
    public:
        mat4 operator*(const mat4& b) const;
        vec4f operator*(const vec4f& rhs) const;
        float& operator[](uint32_t idx);        // for setting values and non-const Mat4's
        float operator[](uint32_t idx) const;   // for reading values from const Mat4's
        bool operator==(const mat4& b) const;

        const float* data() const;

        void transpose();
        bool invert();

        // n[row][column]
        //  n23 == second row, third column
        void set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44);

        void makeTranslation(float x, float y, float z);
        void makeTranslation(const vec3f& v);

        void makeRotationXY(float theta);   // radians
        void makeRotationZX(float theta);   // radians
        void makeRotationYZ(float theta);   // radians
        void makeScale(float x, float y, float z);
        void makeScale(const vec3f& s);
        void makeScale(const float& s);
        void lookAt(const vec3f& eye, const vec3f& center, const vec3f& up);
        void makePerspective(float fovy, float aspect, float near, float far);

        vec3f right() const;
        vec3f up() const;
        vec3f forward() const;

        float Determinant() const;

        static mat4 MakeTranslation(float x, float y, float z);
        static mat4 MakeTranslation(const vec3f& v);
        static mat4 MakeRotationXY(float theta);    // radians
        static mat4 MakeRotationZX(float theta);    // radians
        static mat4 MakeRotationYZ(float theta);    // radians
        static mat4 Rotate(const mat4& m, float theta, const vec3f& axis);  // radians
        static mat4 MakeScale(float x, float y, float z);
        static mat4 MakeScale(const vec3f& v);
        static mat4 MakeScale(float v);
        static mat4 LookAt(const vec3f& eye, const vec3f& center, const vec3f& up);
        static mat4 MakePerspective(float fovy, float aspect, float near, float far);   // fovy in radians
        static mat4 MakeBasis(const vec4f& i, const vec4f& j, const vec4f& k, const vec4f& l);
        static mat4 Transpose(const mat4& m);
        static mat4 Invert(const mat4& m);

        void setRows(const vec4f& r0, const vec4f& r1, const vec4f& r2, const vec4f& r3);
        void setColumns(const vec4f& c0, const vec4f& c1, const vec4f& c2, const vec4f& c3);

        mat4();
        mat4(const mat3& m);
        ~mat4();
    };

    inline float Determinant(const mat4& m)
    {
        return m.Determinant();
    }

    // MAT5 -------------------------------------------------------------------
    class mat5 {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
        union
        {
            float el[25];
            struct {
                float   m00, m10, m20, m30, m40, // column 0
                        m01, m11, m21, m31, m41, // column 1
                        m02, m12, m22, m32, m42, // column 2
                        m03, m13, m23, m33, m43, // column 3
                        m04, m14, m24, m34, m44; // column 4
            };
        };
    public:

        // Functions
    private:
    protected:
    public:

        mat5 operator*(const mat5& b) const;
        vec5f operator*(const vec5f v) const;
        float& operator[](uint32_t idx);        // for setting values and non-const Mat5's
        float operator[](uint32_t idx) const;   // for reading values from const Mat5's
        bool operator==(const mat5& b) const;

        const float* data() const;

        void transpose();
        bool invert();

        // n[row][column]
        //  n23 == second row, third column
        void set(float n11, float n12, float n13, float n14, float n15, float n21, float n22, float n23, float n24, float n25, float n31, float n32, float n33, float n34, float n35, float n41, float n42, float n43, float n44, float n45, float n51, float n52, float n53, float n54, float n55);

        void makeTranslation(float x, float y, float z, float w);
        void makeTranslation(const vec4f& v);

        void makeScale(float x, float y, float z, float w);
        void makeScale(const vec4f& s);
        void makeScale(const float& s);

        void makeRotationXY(float theta);   // radians
        void makeRotationZX(float theta);   // radians
        void makeRotationXW(float theta);   // radians
        void makeRotationYZ(float theta);   // radians
        void makeRotationWY(float theta);   // radians
        void makeRotationZW(float theta);   // radians

        void makePerspectiveProjectionSimple(float dist);
        void makeParallelProjectionSimple();

        void lookAt(const vec4f& eye, const vec4f& center, const vec4f& up, const vec4f& over);
        vec4f right() const;
        vec4f up() const;
        vec4f forward() const;
        vec4f over() const;

        float Determinant() const;

        static mat5 MakeTranslation(float x, float y, float z, float w);
        static mat5 MakeTranslation(vec4f v);
        static mat5 MakeScale(float x, float y, float z, float w);
        static mat5 MakeScale(const vec4f& v);
        static mat5 MakeScale(float v);
        static mat5 LookAt(const vec4f& eye, const vec4f& center, const vec4f& up, const vec4f& over);
        static mat5 MakeRotationXY(float theta);    // radians
        static mat5 MakeRotationZX(float theta);    // radians
        static mat5 MakeRotationXW(float theta);    // radians
        static mat5 MakeRotationYZ(float theta);    // radians
        static mat5 MakeRotationWY(float theta);    // radians
        static mat5 MakeRotationZW(float theta);    // radians
        static mat5 MakeRotationEuler(euler6 theta);    // TODO
        static mat5 MakeInvRotationEuler(euler6 theta); // TODO
        static mat5 MakePerspectiveProjection(float dist);
        static mat5 MakeParallelProjection();
        static mat5 Transpose(const mat5& m);
        static mat5 Invert(const mat5& m);

        void setRows(const vec5f& r0, const vec5f& r1, const vec5f& r2, const vec5f& r3, const vec5f& r4);
        void setColumns(const vec5f& c0, const vec5f& c1, const vec5f& c2, const vec5f& c3, const vec5f& c4);

        mat5();
        mat5(const mat3& m4);
        mat5(const mat4& m4);
        ~mat5();
    };

    inline float Determinant(const mat5& m)
    {
        return m.Determinant();
    }
}