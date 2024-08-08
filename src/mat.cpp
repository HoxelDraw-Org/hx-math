/*
mat.cpp
September 27, 2022
Contributors:
Justin Jensen
*/

#include "mat.h"

// ---------------------------------------
// 
// NOTE: THESE ARE COLUMN-MAJOR MATRICES
// 
// ---------------------------------------

#define _USE_MATH_DEFINES
#include <cmath>

#define M_PI 3.14159265358979f

namespace hxm
{

	// MAT3 -----------------------------------------------------------------------
	Mat3 Mat3::operator*(const Mat3& b) const
	{
		Mat3 r = Mat3();

		// a[row][column]
		float a11 = el[0], a12 = el[3], a13 = el[6];
		float a21 = el[1], a22 = el[4], a23 = el[7];
		float a31 = el[2], a32 = el[5], a33 = el[8];

		// b[row][column]
		float b11 = b.el[0], b12 = b.el[3], b13 = b.el[6];
		float b21 = b.el[1], b22 = b.el[4], b23 = b.el[7];
		float b31 = b.el[2], b32 = b.el[5], b33 = b.el[8];

		r.el[0] = a11 * b11 + a12 * b21 + a13 * b31;
		r.el[3] = a11 * b12 + a12 * b22 + a13 * b32;
		r.el[6] = a11 * b13 + a12 * b23 + a13 * b33;

		r.el[1] = a21 * b11 + a22 * b21 + a23 * b31;
		r.el[4] = a21 * b12 + a22 * b22 + a23 * b32;
		r.el[7] = a21 * b13 + a22 * b23 + a23 * b33;

		r.el[2] = a31 * b11 + a32 * b21 + a33 * b31;
		r.el[5] = a31 * b12 + a32 * b22 + a33 * b32;
		r.el[8] = a31 * b13 + a32 * b23 + a33 * b33;

		return r;
	}

	vec3f Mat3::operator*(const vec3f& rhs) const
	{
		vec3f result;
		/*
		// Fun fact: this would be row-major
		result[0] = rhs[0] * el[0] + rhs[1] * el[1] + rhs[2] * el[2];
		result[1] = rhs[0] * el[3] + rhs[1] * el[4] + rhs[2] * el[5];
		result[2] = rhs[0] * el[6] + rhs[1] * el[7] + rhs[2] * el[8];
		*/
		result[0] = rhs[0] * el[0] + rhs[1] * el[3] + rhs[2] * el[6];
		result[1] = rhs[0] * el[1] + rhs[1] * el[4] + rhs[2] * el[7];
		result[2] = rhs[0] * el[2] + rhs[1] * el[5] + rhs[2] * el[8];
		return result;
	}

	float& Mat3::operator[](uint32_t idx)
	{
		return el[idx];
	}

	float Mat3::operator[](uint32_t idx) const
	{
		return el[idx];
	}

	bool Mat3::operator==(const Mat3& b) const
	{
		const size_t N_ELEMS = 9;
		for (size_t idx = 0; idx < N_ELEMS; idx++)
		{
			if (el[idx] != b.el[idx])
			{
				return false;
			}
		}

		return true;
	}

	const float* Mat3::data() const
	{
		return el;
	}

	void Mat3::transpose()
	{
		float tmp;
		tmp = el[1]; el[1] = el[3]; el[3] = tmp;  // 1-3
		tmp = el[2]; el[2] = el[6]; el[6] = tmp;  // 2-6
		tmp = el[5]; el[5] = el[7]; el[7] = tmp;  // 5-7
	}

	// nAB: the value at row A, column B
	void Mat3::set(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33)
	{
		el[0] = n11; el[3] = n12; el[6] = n13;	// row 0
		el[1] = n21; el[4] = n22; el[7] = n23;	// row 1
		el[2] = n31; el[5] = n32; el[8] = n33;	// row 2
	}

	void Mat3::makeTranslation(float x, float y)
	{
		set(1, 0, x,
			0, 1, y,
			0, 0, 1);
	}

	void Mat3::makeTranslation(const vec2f& v)
	{
		set(1, 0, v.x,
			0, 1, v.y,
			0, 0, 1);
	}

	void Mat3::makeScale(float x, float y)
	{
		set(x, 0, 0,
			0, y, 0,
			0, 0, 1);
	}

	void Mat3::makeScale(const vec2f& v)
	{
		set(v.x, 0,   0,
			0,   v.y, 0,
			0,   0,   1);
	}

	void Mat3::makeRotation(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set( c, s, 0,
			-s, c, 0,
			 0, 0, 1);
	}

	vec2f Mat3::right() const
	{
		return vec2f(el[0], el[3]);
	}

	vec2f Mat3::up() const
	{
		return vec2f(el[1], el[4]);
	}

	Mat3 Mat3::MakeTranslation(float x, float y)
	{
		Mat3 mat = Mat3();
		mat.makeTranslation(x, y);
		return mat;
	}

	Mat3 Mat3::MakeTranslation(const vec2f& v)
	{
		Mat3 mat = Mat3();
		mat.makeTranslation(v);
		return mat;
	}

	Mat3 Mat3::MakeRotation(float theta)
	{
		Mat3 mat = Mat3();
		mat.makeRotation(theta);
		return mat;
	}

	Mat3 Mat3::MakeScale(float x, float y)
	{
		Mat3 mat;
		mat.makeScale(x, y);
		return mat;
	}

	Mat3 Mat3::MakeScale(const vec2f& v)
	{
		Mat3 mat;
		mat.makeScale(v);
		return mat;
	}

	Mat3::Mat3()
	{
		set(1, 0, 0, 0, 1, 0, 0, 0, 1);
	}

	Mat3::~Mat3()
	{
	}

	// MAT4 -----------------------------------------------------------------------
	Mat4 Mat4::operator*(const Mat4& b) const
	{
		Mat4 r = Mat4();

		float a11 = el[0], a12 = el[4], a13 = el[8], a14 = el[12];
		float a21 = el[1], a22 = el[5], a23 = el[9], a24 = el[13];
		float a31 = el[2], a32 = el[6], a33 = el[10], a34 = el[14];
		float a41 = el[3], a42 = el[7], a43 = el[11], a44 = el[15];

		float b11 = b.el[0], b12 = b.el[4], b13 = b.el[8], b14 = b.el[12];
		float b21 = b.el[1], b22 = b.el[5], b23 = b.el[9], b24 = b.el[13];
		float b31 = b.el[2], b32 = b.el[6], b33 = b.el[10], b34 = b.el[14];
		float b41 = b.el[3], b42 = b.el[7], b43 = b.el[11], b44 = b.el[15];

		r.el[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		r.el[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		r.el[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		r.el[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

		r.el[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		r.el[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		r.el[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		r.el[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

		r.el[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		r.el[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		r.el[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		r.el[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

		r.el[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
		r.el[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
		r.el[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
		r.el[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

		return r;
	}

	// TODO: check calling code
	vec4f Mat4::operator*(const vec4f& rhs) const
	{
		vec4f result;
		/*result[0] = rhs[0] * el[0] + rhs[1] * el[1] + rhs[2] * el[2] + rhs[3] * el[3];
		result[1] = rhs[0] * el[4] + rhs[1] * el[5] + rhs[2] * el[6] + rhs[3] * el[7];
		result[2] = rhs[0] * el[8] + rhs[1] * el[9] + rhs[2] * el[10] + rhs[3] * el[11];
		result[3] = rhs[0] * el[12] + rhs[1] * el[13] + rhs[2] * el[14] + rhs[3] * el[15];*/
		result[0] = rhs[0] * el[0] + rhs[1] * el[4] + rhs[2] * el[8] + rhs[3] * el[12];
		result[1] = rhs[0] * el[1] + rhs[1] * el[5] + rhs[2] * el[9] + rhs[3] * el[13];
		result[2] = rhs[0] * el[2] + rhs[1] * el[6] + rhs[2] * el[10] + rhs[3] * el[14];
		result[3] = rhs[0] * el[3] + rhs[1] * el[7] + rhs[2] * el[11] + rhs[3] * el[15];
		return result;
	}

	float& Mat4::operator[](uint32_t idx)
	{
		return el[idx];
	}

	float Mat4::operator[](uint32_t idx) const
	{
		return el[idx];
	}

	bool Mat4::operator==(const Mat4& b) const
	{
		const size_t N_ELEMS = 16;
		for (size_t idx = 0; idx < N_ELEMS; idx++)
		{
			if (el[idx] != b.el[idx])
			{
				return false;
			}
		}

		return true;
	}

	const float* Mat4::data() const
	{
		return el;
	}

	void Mat4::transpose()
	{
		float tmp;
		tmp = el[1]; el[1] = el[4]; el[4] = tmp;  // 1-4
		tmp = el[2]; el[2] = el[8]; el[8] = tmp;  // 2-8
		tmp = el[6]; el[6] = el[9]; el[9] = tmp;  // 6-9
		tmp = el[3]; el[3] = el[12]; el[12] = tmp;  // 3-12
		tmp = el[7]; el[7] = el[13]; el[13] = tmp;  // 7-13
		tmp = el[11]; el[11] = el[14]; el[14] = tmp;  // 11-14
	}

	// nAB: the value at row A, column B
	void Mat4::set(float n11, float n12, float n13, float n14, float n21, float n22, float n23, float n24, float n31, float n32, float n33, float n34, float n41, float n42, float n43, float n44)
	{
		el[0] = n11; el[4] = n12; el[8] = n13; el[12] = n14;	// row 0
		el[1] = n21; el[5] = n22; el[9] = n23; el[13] = n24;	// row 1
		el[2] = n31; el[6] = n32; el[10] = n33; el[14] = n34;	// row 2
		el[3] = n41; el[7] = n42; el[11] = n43; el[15] = n44;	// row 3
	}

	void Mat4::makeTranslation(float x, float y, float z)
	{
		set(1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
	}

	void Mat4::makeTranslation(const vec3f& v)
	{
		set(1, 0, 0, v.x,
			0, 1, 0, v.y,
			0, 0, 1, v.z,
			0, 0, 0, 1);
	}

	// transforms (+1,0,0) to (0,+1,0) using a +90 degree rotation
	// transforms (0,+1,0) to (-1,0,0) using a +90 degree rotation
	void Mat4::makeRotationXY(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set( c, s, 0, 0,
			-s, c, 0, 0,
			 0, 0, 1, 0,
			 0, 0, 0, 1);
	}

	// transforms (0,0,+1) to (+1,0,0) using a +90 degree rotation
	// transforms (+1,0,0) to (0,0,-1) using a +90 degree rotation
	void Mat4::makeRotationZX(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set( c, 0, s, 0,
			 0, 1, 0, 0,
			-s, 0, c, 0,
			 0, 0, 0, 1);
	}

	// transforms (0,+1,0) to (0,0,+1) using a +90 degree rotation
	// transforms (0,0,+1) to (0,-1,0) using a +90 degree rotation
	void Mat4::makeRotationYZ(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(1, 0,  0, 0,
			0, c, -s, 0,
			0, s,  c, 0,
			0, 0,  0, 1);
	}

	void Mat4::makeScale(float x, float y, float z)
	{
		set(x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}

	void Mat4::makeScale(const vec3f& s)
	{
		set(s.x, 0,   0,   0,
			0,   s.y, 0,   0,
			0,   0,   s.z, 0,
			0,   0,   0,   1);
	}

	void Mat4::makeScale(const float& s)
	{
		set(s, 0, 0, 0,
			0, s, 0, 0,
			0, 0, s, 0,
			0, 0, 0, 1);
	}

	void Mat4::lookAt(const vec3f& eye, const vec3f& center, const vec3f& up)
	{
		// calculate forward
		vec3f fN = normalize(center - eye);

		// calculate right
		vec3f rN = normalize(cross(fN, up));

		// calculate new up
		vec3f uN = cross(rN, fN);

		// pre-transform the eye position (I don't know why, this is just what glm does)
		// see https://github.com/g-truc/glm/blob/1.0.1/glm/ext/matrix_transform.inl#L153
		float transX = -((rN.x * eye.x) + (rN.y * eye.y) + (rN.z * eye.z));
		float transY = -((uN.x * eye.x) + (uN.y * eye.y) + (uN.z * eye.z));
		float transZ =  ((fN.x * eye.x) + (fN.y * eye.y) + (fN.z * eye.z));
		
		set( rN.x,  rN.y,  rN.z, transX,
			 uN.x,  uN.y,  uN.z, transY,
			-fN.x, -fN.y, -fN.z, transZ,
			 0,     0,     0,    1);
	}

	void Mat4::makePerspective(float fovy, float aspect, float near, float far)
	{
		// calculate top, bottom, left and right
		// top = tan(fov/2) * near
		float t = tanf(fovy * 0.5f) * near;

		// bottom = -top
		float b = -t;

		// right = top * aspect ratio
		float r = t * aspect;

		// left = -top * aspect ratio
		float l = -r;

		float _r_l = 1.0f / (r - l);
		float _t_b = 1.0f / (t - b);
		float _f_n = 1.0f / (far - near);
		float n2 = near * 2.0f;

		set(n2 * _r_l, 0,         (r + l) * _r_l,         0,
			0,         n2 * _t_b, (t + b) * _t_b,         0,
			0,         0,         -((far + near) * _f_n), -((n2 * far) * _f_n),
			0,         0,         -1,                     0);
	}

	vec3f Mat4::right() const
	{
		return vec3f(el[0], el[4], el[8]);
	}

	vec3f Mat4::up() const
	{
		return vec3f(el[1], el[5], el[9]);
	}

	vec3f Mat4::forward() const
	{
		return vec3f(el[2], el[6], el[10]);
	}

	Mat4 Mat4::MakeTranslation(float x, float y, float z)
	{
		Mat4 mat = Mat4();
		mat.makeTranslation(x, y, z);
		return mat;
	}

	Mat4 Mat4::MakeTranslation(const vec3f& v)
	{
		Mat4 mat = Mat4();
		mat.makeTranslation(v);
		return mat;
	}

	Mat4 Mat4::MakeRotationXY(float theta)
	{
		Mat4 mat = Mat4();
		mat.makeRotationXY(theta);
		return mat;
	}

	// https://github.com/g-truc/glm/blob/b3f87720261d623986f164b2a7f6a0a938430271/glm/ext/matrix_transform.inl#L18
	Mat4 Mat4::Rotate(const Mat4& m, float theta, const vec3f& axis)
	{
		const float a = theta;
		const float c = cosf(a);
		const float s = sinf(a);

		// normalize the axis
		vec3f axisNorm = normalize(axis);

		// make some weird temp axis
		vec3f temp = (1.0f - c) * axisNorm;

		// create a rotation matrix
		Mat4 rotate;

		// first row
		rotate[0] = c + temp[0] * axisNorm[0];
		rotate[4] = temp[0] * axisNorm[1] + s * axisNorm[2];
		rotate[8] = temp[0] * axisNorm[2] - s * axisNorm[1];

		// second row
		rotate[1] = temp[1] * axisNorm[0] - s * axisNorm[2];
		rotate[5] = c + temp[1] * axisNorm[1];
		rotate[9] = temp[1] * axisNorm[2] + s * axisNorm[0];

		// third row
		rotate[2] = temp[2] * axisNorm[0] + s * axisNorm[1];
		rotate[6] = temp[2] * axisNorm[1] - s * axisNorm[0];
		rotate[10] = c + temp[2] * axisNorm[2];

		// create a result matrix
		Mat4 result;

		// multiply m by the rotation matrix, store in result
		result = m * rotate;

		return result;
	}

	Mat4 Mat4::MakeScale(float x, float y, float z)
	{
		Mat4 r;
		r.makeScale(x, y, z);
		return r;
	}

	Mat4 Mat4::MakeScale(const vec3f& v)
	{
		Mat4 r;
		r.makeScale(v);
		return r;
	}

	Mat4 Mat4::MakeScale(float v)
	{
		Mat4 r;
		r.makeScale(v);
		return r;
	}

	Mat4 Mat4::MakePerspective(float fovy, float aspect, float near, float far)
	{
		Mat4 r;
		r.makePerspective(fovy, aspect, near, far);
		return r;
	}

	Mat4::Mat4()
	{
		set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}

	Mat4::~Mat4()
	{
	}


	// MAT5 -----------------------------------------------------------------------
	Mat5 Mat5::operator*(const Mat5& b) const
	{
		Mat5 r = Mat5();

		float a11 = el[0], a12 = el[5], a13 = el[10], a14 = el[15], a15 = el[20];
		float a21 = el[1], a22 = el[6], a23 = el[11], a24 = el[16], a25 = el[21];
		float a31 = el[2], a32 = el[7], a33 = el[12], a34 = el[17], a35 = el[22];
		float a41 = el[3], a42 = el[8], a43 = el[13], a44 = el[18], a45 = el[23];
		float a51 = el[4], a52 = el[9], a53 = el[14], a54 = el[19], a55 = el[24];

		float b11 = b.el[0], b12 = b.el[5], b13 = b.el[10], b14 = b.el[15], b15 = b.el[20];
		float b21 = b.el[1], b22 = b.el[6], b23 = b.el[11], b24 = b.el[16], b25 = b.el[21];
		float b31 = b.el[2], b32 = b.el[7], b33 = b.el[12], b34 = b.el[17], b35 = b.el[22];
		float b41 = b.el[3], b42 = b.el[8], b43 = b.el[13], b44 = b.el[18], b45 = b.el[23];
		float b51 = b.el[4], b52 = b.el[9], b53 = b.el[14], b54 = b.el[19], b55 = b.el[24];

		r.el[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41 + a15 * b51;
		r.el[5] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42 + a15 * b52;
		r.el[10] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43 + a15 * b53;
		r.el[15] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44 + a15 * b54;
		r.el[20] = a11 * b15 + a12 * b25 + a13 * b35 + a14 * b45 + a15 * b55;

		r.el[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41 + a25 * b51;
		r.el[6] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42 + a25 * b52;
		r.el[11] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43 + a25 * b53;
		r.el[16] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44 + a25 * b54;
		r.el[21] = a21 * b15 + a22 * b25 + a23 * b35 + a24 * b45 + a25 * b55;

		r.el[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41 + a35 * b51;
		r.el[7] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42 + a35 * b52;
		r.el[12] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43 + a35 * b53;
		r.el[17] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44 + a35 * b54;
		r.el[22] = a31 * b15 + a32 * b25 + a33 * b35 + a34 * b45 + a35 * b55;

		r.el[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41 + a45 * b51;
		r.el[8] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42 + a45 * b52;
		r.el[13] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43 + a45 * b53;
		r.el[18] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44 + a45 * b54;
		r.el[23] = a41 * b15 + a42 * b25 + a43 * b35 + a44 * b45 + a45 * b55;

		r.el[4] = a51 * b11 + a52 * b21 + a53 * b31 + a54 * b41 + a55 * b51;
		r.el[9] = a51 * b12 + a52 * b22 + a53 * b32 + a54 * b42 + a55 * b52;
		r.el[14] = a51 * b13 + a52 * b23 + a53 * b33 + a54 * b43 + a55 * b53;
		r.el[19] = a51 * b14 + a52 * b24 + a53 * b34 + a54 * b44 + a55 * b54;
		r.el[24] = a51 * b15 + a52 * b25 + a53 * b35 + a54 * b45 + a55 * b55;

		return r;
	}

	vec5f Mat5::operator*(const vec5f v) const
	{
		vec5f r;
		r.x = (el[0] * v.x) + (el[5] * v.y) + (el[10] * v.z) + (el[15] * v.w) + (el[20] * v.v);
		r.y = (el[1] * v.x) + (el[6] * v.y) + (el[11] * v.z) + (el[16] * v.w) + (el[21] * v.v);
		r.z = (el[2] * v.x) + (el[7] * v.y) + (el[12] * v.z) + (el[17] * v.w) + (el[22] * v.v);
		r.w = (el[3] * v.x) + (el[8] * v.y) + (el[13] * v.z) + (el[18] * v.w) + (el[23] * v.v);
		r.v = (el[4] * v.x) + (el[9] * v.y) + (el[14] * v.z) + (el[19] * v.w) + (el[24] * v.v);

		return r;
	}

	float& Mat5::operator[](uint32_t idx)
	{
		return el[idx];
	}

	float Mat5::operator[](uint32_t idx) const
	{
		return el[idx];
	}

	bool Mat5::operator==(const Mat5& b) const
	{
		const size_t N_ELEMS = 25;
		for (size_t idx = 0; idx < N_ELEMS; idx++)
		{
			if (el[idx] != b.el[idx])
			{
				return false;
			}
		}

		return true;
	}

	const float* Mat5::data() const
	{
		return el;
	}

	void Mat5::transpose()
	{
		float tmp;
		tmp = el[1]; el[1] = el[5]; el[5] = tmp;  // 1-5
		tmp = el[2]; el[2] = el[10]; el[10] = tmp;  // 2-10
		tmp = el[3]; el[3] = el[15]; el[15] = tmp;  // 3-15
		tmp = el[4]; el[4] = el[20]; el[20] = tmp;  // 4-20
		tmp = el[7]; el[7] = el[11]; el[11] = tmp;  // 7-11
		tmp = el[8]; el[8] = el[16]; el[16] = tmp;  // 8-16
		tmp = el[9]; el[9] = el[21]; el[21] = tmp;  // 9-21
		tmp = el[13]; el[13] = el[17]; el[17] = tmp;  // 13-17
		tmp = el[14]; el[14] = el[22]; el[22] = tmp;  // 14-22
		tmp = el[19]; el[19] = el[23]; el[23] = tmp;  // 19-23
	}

	// nAB: value at row A, column B
	void Mat5::set(float n11, float n12, float n13, float n14, float n15, float n21, float n22, float n23, float n24, float n25, float n31, float n32, float n33, float n34, float n35, float n41, float n42, float n43, float n44, float n45, float n51, float n52, float n53, float n54, float n55)
	{
		el[0] = n11; el[5] = n12; el[10] = n13; el[15] = n14; el[20] = n15;
		el[1] = n21; el[6] = n22; el[11] = n23; el[16] = n24; el[21] = n25;
		el[2] = n31; el[7] = n32; el[12] = n33; el[17] = n34; el[22] = n35;
		el[3] = n41; el[8] = n42; el[13] = n43; el[18] = n44; el[23] = n45;
		el[4] = n51; el[9] = n52; el[14] = n53; el[19] = n54; el[24] = n55;
	}

	void Mat5::makeTranslation(float x, float y, float z, float w)
	{
		set(1, 0, 0, 0, x,
			0, 1, 0, 0, y,
			0, 0, 1, 0, z,
			0, 0, 0, 1, w,
			0, 0, 0, 0, 1);
	}

	void Mat5::makeTranslation(const vec4f& v)
	{
		set(1, 0, 0, 0, v.x,
			0, 1, 0, 0, v.y,
			0, 0, 1, 0, v.z,
			0, 0, 0, 1, v.w,
			0, 0, 0, 0, 1);
	}

	void Mat5::makeScale(float x, float y, float z, float w)
	{
		set(x, 0, 0, 0, 0,
			0, y, 0, 0, 0,
			0, 0, z, 0, 0,
			0, 0, 0, w, 0,
			0, 0, 0, 0, 1);
	}

	void Mat5::makeScale(const vec4f& s)
	{
		set(s.x, 0,   0,   0,   0,
			0,   s.y, 0,   0,   0,
			0,   0,   s.z, 0,   0,
			0,   0,   0,   s.w, 0,
			0,   0,   0,   0,   1);
	}

	void Mat5::makeScale(const float& s)
	{
		set(s, 0, 0, 0, 0,
			0, s, 0, 0, 0,
			0, 0, s, 0, 0,
			0, 0, 0, s, 0,
			0, 0, 0, 0, 1);
	}

	// transforms (+1,0,0,0) to (0,+1,0,0) using a +90 degree rotation
	// transforms (0,+1,0,0) to (-1,0,0,0) using a +90 degree rotation
	void Mat5::makeRotationXY(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(c, -s, 0, 0, 0,
			s, c, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 0, 1);
	}

	// transforms (0,0,+1,0) to (+1,0,0,0) using a +90 degree rotation
	// transforms (+1,0,0,0) to (0,0,-1,0) using a +90 degree rotation
	void Mat5::makeRotationZX(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(c, 0, s, 0, 0,
			0, 1, 0, 0, 0,
			-s, 0, c, 0, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 0, 1);
	}

	// transforms (+1,0,0,0) to (0,0,0,+1) using a +90 degree rotation
	// transforms (0,0,0,+1) to (-1,0,0,0) using a +90 degree rotation
	void Mat5::makeRotationXW(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(c, 0, 0, -s, 0,
			0, 1, 0, 0, 0,
			0, 0, 1, 0, 0,
			s, 0, 0, c, 0,
			0, 0, 0, 0, 1);
	}

	// transforms (0,+1,0,0) to (0,0,+1,0) using a +90 degree rotation
	// transforms (0,0,+1,0) to (0,-1,0,0) using a +90 degree rotation
	void Mat5::makeRotationYZ(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(1, 0, 0, 0, 0,
			0, c, -s, 0, 0,
			0, s, c, 0, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, 0, 1);
	}

	// transforms (0,0,0,+1) to (0,+1,0,0) using a +90 degree rotation
	// transforms (0,+1,0,0) to (0,0,0,-1) using a +90 degree rotation
	void Mat5::makeRotationWY(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(1, 0, 0, 0, 0,
			0, c, 0, s, 0,
			0, 0, 1, 0, 0,
			0, -s, 0, c, 0,
			0, 0, 0, 0, 1);
	}

	// transforms (0,0,+1,0) to (0,0,0,+1) using a +90 degree rotation
	// transforms (0,0,0,+1) to (0,0,-1,0) using a +90 degree rotation
	void Mat5::makeRotationZW(float theta)
	{
		float c = cosf(theta);
		float s = sinf(theta);
		set(1, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, c, -s, 0,
			0, 0, s, c, 0,
			0, 0, 0, 0, 1);
	}

	void Mat5::makePerspectiveProjectionSimple(float dist)
	{
		float f = 1.0f / dist;
		set(1, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 1, 0,
			0, 0, 0, f, 1);
	}

	void Mat5::makeParallelProjectionSimple()
	{
		// simply dropping the W-coordinate
		set(1, 0, 0, 0, 0,
			0, 1, 0, 0, 0,
			0, 0, 1, 0, 0,
			0, 0, 0, 0, 0,
			0, 0, 0, 0, 1);
	}

	void Mat5::lookAt(const vec4f& eye, const vec4f& center, const vec4f& up, const vec4f& over)
	{
		// calculate forwardNorm
		vec4f fN = normalize(center - eye);

		// calculate rightNorm (cross4(up, over, forward))
		vec4f rN = normalize(cross4(up, over, fN));

		// calculate upNorm (cross4(over, forward, right))
		vec4f uN = normalize(cross4(over, fN, rN));

		// calculate overNorm (cross4(forward, right, upNorm))
		vec4f oN = cross4(fN, rN, uN);

		// TODO: make sure the basis vectors are pointed the right way
		// TODO: add the translation but pre-rotate it (see Mat4::lookAt)
		set(rN.x, rN.y, rN.z, rN.w, 0,
			uN.x, uN.y, uN.z, uN.w, 0,
			fN.x, fN.y, fN.z, fN.w, 0,
			oN.x, oN.y, oN.z, oN.w, 0,
			0,    0,    0,    0,    1);
	}

	vec4f Mat5::right() const
	{
		return vec4f(el[0], el[5], el[10], el[15]);
	}

	vec4f Mat5::up() const
	{
		return vec4f(el[1], el[6], el[11], el[16]);
	}

	vec4f Mat5::forward() const
	{
		return vec4f(el[2], el[7], el[12], el[17]);
	}

	vec4f Mat5::over() const
	{
		return vec4f(el[3], el[8], el[13], el[18]);
	}

	Mat5 Mat5::MakeTranslation(float x, float y, float z, float w)
	{
		Mat5 mat = Mat5();
		mat.makeTranslation(x, y, z, w);
		return mat;
	}

	Mat5 Mat5::MakeTranslation(vec4f v)
	{
		Mat5 mat = Mat5();
		mat.makeTranslation(v.x, v.y, v.z, v.w);
		return mat;
	}

	Mat5 Mat5::MakeScale(float x, float y, float z, float w)
	{
		Mat5 mat;
		mat.makeScale(x, y, z, w);
		return mat;
	}

	Mat5 Mat5::MakeScale(const vec4f& v)
	{
		Mat5 mat;
		mat.makeScale(v);
		return mat;
	}

	Mat5 Mat5::MakeScale(float v)
	{
		Mat5 mat;
		mat.makeScale(v);
		return mat;
	}

	Mat5 Mat5::MakeRotationXY(float theta)
	{
		Mat5 mat = Mat5();
		mat.makeRotationXY(theta);
		return mat;
	}

	Mat5 Mat5::MakeRotationZX(float theta)
	{
		Mat5 mat = Mat5();
		mat.makeRotationZX(theta);
		return mat;
	}

	Mat5 Mat5::MakeRotationXW(float theta)
	{
		Mat5 mat = Mat5();
		mat.makeRotationXW(theta);
		return mat;
	}

	Mat5 Mat5::MakeRotationYZ(float theta)
	{
		Mat5 mat = Mat5();
		mat.makeRotationYZ(theta);
		return mat;
	}

	Mat5 Mat5::MakeRotationWY(float theta)
	{
		Mat5 mat = Mat5();
		mat.makeRotationWY(theta);
		return mat;
	}

	Mat5 Mat5::MakeRotationZW(float theta)
	{
		Mat5 mat = Mat5();
		mat.makeRotationZW(theta);
		return mat;
	}

	Mat5 Mat5::MakePerspectiveProjection(float dist)
	{
		Mat5 mat;
		mat.makePerspectiveProjectionSimple(dist);
		return mat;
	}

	Mat5 Mat5::MakeParallelProjection()
	{
		Mat5 mat;
		mat.makeParallelProjectionSimple();
		return mat;
	}

	Mat5::Mat5()
	{
		set(1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1);
	}

	Mat5::~Mat5()
	{
	}
}