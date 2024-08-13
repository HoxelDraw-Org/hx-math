#pragma once

#include <iostream>
#include "vec.h"
//#include "mat.h"
//#include "hxMath.h"

#define MAX_ERROR 1e-5f
using namespace hxm;

bool isNear(float a, float b, float error = MAX_ERROR)
{
	return std::abs(a - b) <= error;
}

bool isNearVec4f(const vec4f& a, const vec4f& b, float error = MAX_ERROR)
{
	return std::abs(a.x - b.x) <= error && 
		   std::abs(a.y - b.y) <= error &&
		   std::abs(a.z - b.z) <= error &&
		   std::abs(a.w - b.w) <= error;
}

bool testVector()
{
	bool success = true;

	vec4f v4_0 = vec4f(1, 0, 0, 0);
	vec4f v4_1 = vec4f(0, 1, 0, 0);
	vec4f v4_2 = { 0, 0, 1, 0 };	// use list initializer if you so desire

	// initialize with a single float
	vec4f vFloat = vec4f(2.0f);
	if (vFloat != vec4f(2, 2, 2, 2))
	{
		std::printf("Vec4f scalar initializer failed!\n");
		success = false;
	}

	// initialize with a smaller vector
	vec4f vSmallerVec1 = vec3f(1, 2, 3);
	vec4f vSmallerVec2 = vec4f(vec3f(2, 3, 4), 1.0f);
	if (vSmallerVec1 != vec4f(1, 2, 3, 0) || vSmallerVec2 != vec4f(2, 3, 4, 1))
	{
		std::printf("Vec4f vec3 initializer failed!\n");
		success = false;
	}

	// basic component access
	float xVal0 = v4_0.x;

	// array accessor for vectors
	vec4f arrayVec = { 2, 3, 4, 5 };
	float xVal = arrayVec[0];
	float yVal = arrayVec[1];
	float zVal = arrayVec[2];
	float wVal = arrayVec[3];
	if (xVal != arrayVec[0] || yVal != arrayVec[1] || zVal != arrayVec[2] || wVal != arrayVec[3])
	{
		std::printf("Vector array accessor failed!\n");
		success = false;
	}

	// also modify vectors with square brackets
	arrayVec[0] = 6;
	if (arrayVec[0] != 6.0f)
	{
		std::printf("Vector array modifier failed!\n");
		success = false;
	}

	float dotProduct0 = dot(v4_0, v4_1);
	float dotProduct1 = v4_0.dot(v4_1);	// two ways to do the dot product (and many operators)
	if (dotProduct0 != 0.0f || dotProduct1 != 0.0f)
	{
		std::printf("Vec4f Dot product failed!\n");
		success = false;
	}

	// add/subtract vectors two ways
	vec4f sumVec1 = vec4f(6, 7, 8, 9) + vec4f(7, 8, 9, 10);
	vec4f sumVec2 = { 8, 9, 10, 11 };
	sumVec2 -= vec4f(9, 10, 11, 12);
	if (sumVec1 != vec4f(13, 15, 17, 19) || !(sumVec2 == vec4f(-1, -1, -1, -1)))
	{
		std::printf("Vec4f add failed!\n");
		success = false;
	}

	// also add/subtract scalar values
	vec4f sumVecScalar = vec4f(10, 11, 12, 13) + 2.0f;
	if (sumVecScalar != vec4f(12, 13, 14, 15))
	{
		std::printf("Vec4f add scalar failed!\n");
		success = false;
	}

	// multiply/divide vectors (component-wise)
	vec4f multVec = vec4f(1, 3, 5, 7) * vec4f(1, 2, 3, 4);
	if (!isNearVec4f(multVec, vec4f(1, 6, 15, 28)))
	{
		std::printf("Vec4f component-wise multiply failed!\n");
		success = false;
	}

	vec4f divVec = vec4f(1, 1, 1, 1) / vec4f(1, 2, 4, 8);
	if (!isNearVec4f(divVec, vec4f(1.0f, 0.5f, 0.25f, 0.125f)))
	{
		std::printf("Vec4f component-wise divide failed!\n");
		success = false;
	}

	// cross4 takes three 4D vectors and returns a 4D vector that is perpendicular to all of them
	//		(assuming the three vectors are not coplanar, degenerate, etc.)
	vec4f crossProduct4 = cross4(v4_0, v4_1, v4_2);
	if (crossProduct4.dot(v4_0) != 0.0f || crossProduct4.dot(v4_1) != 0.0f || crossProduct4.dot(v4_2) != 0.0f)
	{
		std::printf("Cross4 failed!\n");
		success = false;
	}

	vec4f nonNormalizedVec = { 1, 2, 3, 4 };
	nonNormalizedVec.normalize();	// "nonNormalizedVec" is now normalized
	if (!isNear(nonNormalizedVec.length(), 1.0f))
	{
		std::printf("Vec4f normalize failed!\n");
		success = false;
	}

	return success;
}

bool testMatrix()
{
	return false;
}

bool testAABB()
{
	return false;
}

bool testRay4()
{
	return false;
}

bool testEuler6()
{
	return false;
}

bool testMath()
{
	return false;
}