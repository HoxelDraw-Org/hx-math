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
    class Mat3;
    class Mat4;
    class Mat5;
    
    // MAT3 -------------------------------------------------------------------
    class Mat3 {
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

        Mat3 operator*(const Mat3& b) const;
        vec3f operator*(const vec3f& rhs) const;
        float& operator[](uint32_t idx);        // for setting values and non-const Mat4's
        float operator[](uint32_t idx) const;   // for reading values from const Mat4's
        bool operator==(const Mat3& b) const;

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

        static Mat3 MakeTranslation(float x, float y);
        static Mat3 MakeTranslation(const vec2f& v);
        static Mat3 MakeRotation(float theta);  // radians
        static Mat3 MakeScale(float x, float y);
        static Mat3 MakeScale(const vec2f& v);
        static Mat3 MakeScale(const float& v);
        static Mat3 Transpose(const Mat3& m);
        static Mat3 Invert(const Mat3& m);

        Mat3();
        ~Mat3();
    };

	// MAT4 -------------------------------------------------------------------
    class Mat4 {
        // Defines
    private:
    protected:
    public:

        // Members
    private:
    protected:
        union
        {
            float el[16];
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
        Mat4 operator*(const Mat4& b) const;
        vec4f operator*(const vec4f& rhs) const;
        float& operator[](uint32_t idx);        // for setting values and non-const Mat4's
        float operator[](uint32_t idx) const;   // for reading values from const Mat4's
        bool operator==(const Mat4& b) const;

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

        static Mat4 MakeTranslation(float x, float y, float z);
        static Mat4 MakeTranslation(const vec3f& v);
        static Mat4 MakeRotationXY(float theta);    // radians
        static Mat4 MakeRotationZX(float theta);    // radians
        static Mat4 MakeRotationYZ(float theta);    // radians
        static Mat4 Rotate(const Mat4& m, float theta, const vec3f& axis);  // radians
        static Mat4 MakeScale(float x, float y, float z);
        static Mat4 MakeScale(const vec3f& v);
        static Mat4 MakeScale(float v);
        static Mat4 MakePerspective(float fovy, float aspect, float near, float far);   // fovy in radians
        static Mat4 Transpose(const Mat4& m);
        static Mat4 Invert(const Mat4& m);

        Mat4();
        Mat4(const Mat3& m);
        ~Mat4();
    };


	// MAT5 -------------------------------------------------------------------
    class Mat5 {
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

        Mat5 operator*(const Mat5& b) const;
        vec5f operator*(const vec5f v) const;
        float& operator[](uint32_t idx);        // for setting values and non-const Mat5's
        float operator[](uint32_t idx) const;   // for reading values from const Mat5's
        bool operator==(const Mat5& b) const;

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

        static Mat5 MakeTranslation(float x, float y, float z, float w);
        static Mat5 MakeTranslation(vec4f v);
        static Mat5 MakeScale(float x, float y, float z, float w);
        static Mat5 MakeScale(const vec4f& v);
        static Mat5 MakeScale(float v);
        static Mat5 MakeRotationXY(float theta);    // radians
        static Mat5 MakeRotationZX(float theta);    // radians
        static Mat5 MakeRotationXW(float theta);    // radians
        static Mat5 MakeRotationYZ(float theta);    // radians
        static Mat5 MakeRotationWY(float theta);    // radians
        static Mat5 MakeRotationZW(float theta);    // radians
        static Mat5 MakeRotationEuler(euler6 theta);    // TODO
        static Mat5 MakeInvRotationEuler(euler6 theta); // TODO
        static Mat5 MakePerspectiveProjection(float dist);
        static Mat5 MakeParallelProjection();
        static Mat5 Transpose(const Mat5& m);
        static Mat5 Invert(const Mat5& m);

        Mat5();
        Mat5(const Mat3& m4);
        Mat5(const Mat4& m4);
        ~Mat5();
    };
}