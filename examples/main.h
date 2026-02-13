#pragma once

#include <iostream>
#include "vec.h"
#include "aabb.h"
#include "mat.h"
#include "hxMath.h"
#include "rotor.h"
#include "onb.h"

#define MAX_ERROR 1e-5f
using namespace hxm;

bool isNear(float a, float b, float error = MAX_ERROR)
{
	return std::abs(a - b) <= error;
}

bool isNearVec3f(const vec3f& a, const vec3f& b, float error = MAX_ERROR)
{
	return std::abs(a.x - b.x) <= error &&
		std::abs(a.y - b.y) <= error &&
		std::abs(a.z - b.z) <= error;
}

bool isNearVec4f(const vec4f& a, const vec4f& b, float error = MAX_ERROR)
{
	return std::abs(a.x - b.x) <= error && 
		   std::abs(a.y - b.y) <= error &&
		   std::abs(a.z - b.z) <= error &&
		   std::abs(a.w - b.w) <= error;
}

bool isNearVec5f(const vec5f& a, const vec5f& b, float error = MAX_ERROR)
{
	return std::abs(a.x - b.x) <= error &&
		std::abs(a.y - b.y) <= error &&
		std::abs(a.z - b.z) <= error &&
		std::abs(a.w - b.w) <= error &&
		std::abs(a.v - b.v) <= error;
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

	// pointer access
	vec4f ptrVec = { 1, 2, 3, 4 };
	auto ptr = &(ptrVec.x);
	xVal = *(ptr + 0);
	yVal = *(ptr + 1);
	zVal = *(ptr + 2);
	wVal = *(ptr + 3);
	if (xVal != 1 || yVal != 2 || zVal != 3 || wVal != 4)
	{
		std::printf("Vector pointer accessor failed!\n");
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

	// test the inline normalize function
	vec4f nonNormalVec2 = { 2, 3, 4, 5 };
	vec4f normalVec2 = normalize(nonNormalVec2);
	if (!isNear(normalVec2.length(), 1.0f) || normalVec2 == nonNormalVec2)
	{
		std::printf("Vec4f inline normalize failed!\n");
		success = false;
	}

	return success;
}

bool testMatrix()
{
	bool success = true;

	float rad90 = toRad(90.0f);

	// Mat3 rotation tests
	{
		vec3f ptX = { 1, 0, 1 };
		vec3f ptY = { 0, 1, 1 };

		mat3 rot = mat3::MakeRotation(rad90);
		vec3f ptRot = rot * ptX;
		if (!isNearVec3f(ptRot, vec3f(0, 1, 1)))
		{
			success = false;
			std::printf("Mat3::Rot X failed\n");
		}

		ptRot = rot * ptY;
		if (!isNearVec3f(ptRot, vec3f(-1, 0, 1)))
		{
			success = false;
			std::printf("Mat3::Rot Y failed\n");
		}
	}

	// Mat4 rotation tests
	{
		vec4f ptX = { 1, 0, 0, 1 };
		vec4f ptY = { 0, 1, 0, 1 };
		vec4f ptZ = { 0, 0, 1, 1 };

		// XY
		mat4 rotXY = mat4::MakeRotationXY(rad90);
		vec4f ptRotXY = rotXY * ptX;
		if (!isNearVec4f(ptRotXY, vec4f(0, 1, 0, 1)))
		{
			success = false;
			std::printf("Mat4::RotXY X failed\n");
		}

		ptRotXY = rotXY * ptY;
		if (!isNearVec4f(ptRotXY, vec4f(-1, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat4::RotXY Y failed\n");
		}

		// ZX
		mat4 rotZX = mat4::MakeRotationZX(rad90);
		vec4f ptRotZX = rotZX * ptZ;
		if (!isNearVec4f(ptRotZX, vec4f(1, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat4::RotZX Z failed\n");
		}

		ptRotZX = rotZX * ptX;
		if (!isNearVec4f(ptRotZX, vec4f(0, 0, -1, 1)))
		{
			success = false;
			std::printf("Mat4::RotZX X failed\n");
		}

		// YZ
		mat4 rotYZ = mat4::MakeRotationYZ(rad90);
		vec4f ptRotYZ = rotYZ * ptY;
		if (!isNearVec4f(ptRotYZ, vec4f(0, 0, 1, 1)))
		{
			success = false;
			std::printf("Mat4::RotYZ Y failed\n");
		}

		ptRotYZ = rotYZ * ptZ;
		if (!isNearVec4f(ptRotYZ, vec4f(0, -1, 0, 1)))
		{
			success = false;
			std::printf("Mat4::RotYZ Z failed\n");
		}
	}


	// Mat5 rotation tests
	{
		vec5f ptX = { 1, 0, 0, 0, 1 };
		vec5f ptY = { 0, 1, 0, 0, 1 };
		vec5f ptZ = { 0, 0, 1, 0, 1 };
		vec5f ptW = { 0, 0, 0, 1, 1 };

		// XY
		mat5 rotXY = mat5::MakeRotationXY(rad90);
		vec5f ptRotXY = rotXY * ptX;
		if (!isNearVec5f(ptRotXY, vec5f(0, 1, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotXY X failed\n");
		}

		ptRotXY = rotXY * ptY;
		if (!isNearVec5f(ptRotXY, vec5f(-1, 0, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotXY Y failed\n");
		}

		// ZX
		mat5 rotZX = mat5::MakeRotationZX(rad90);
		vec5f ptRotZX = rotZX * ptZ;
		if (!isNearVec5f(ptRotZX, vec5f(1, 0, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotZX Z failed\n");
		}

		ptRotZX = rotZX * ptX;
		if (!isNearVec5f(ptRotZX, vec5f(0, 0, -1, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotZX X failed\n");
		}

		// XW
		mat5 rotXW = mat5::MakeRotationXW(rad90);
		vec5f ptRotXW = rotXW * ptX;
		if (!isNearVec5f(ptRotXW, vec5f(0, 0, 0, 1, 1)))
		{
			success = false;
			std::printf("Mat5::RotXW X failed\n");
		}

		ptRotXW = rotXW * ptW;
		if (!isNearVec5f(ptRotXW, vec5f(-1, 0, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotXW W failed\n");
		}

		// YZ
		mat5 rotYZ = mat5::MakeRotationYZ(rad90);
		vec5f ptRotYZ = rotYZ * ptY;
		if (!isNearVec5f(ptRotYZ, vec5f(0, 0, 1, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotYZ Y failed\n");
		}

		ptRotYZ = rotYZ * ptZ;
		if (!isNearVec5f(ptRotYZ, vec5f(0, -1, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotXY Z failed\n");
		}

		// WY
		mat5 rotWY = mat5::MakeRotationWY(rad90);
		vec5f ptRotWY = rotWY * ptW;
		if (!isNearVec5f(ptRotWY, vec5f(0, 1, 0, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotWY W failed\n");
		}

		ptRotWY = rotWY * ptY;
		if (!isNearVec5f(ptRotWY, vec5f(0, 0, 0, -1, 1)))
		{
			success = false;
			std::printf("Mat5::RotWY Y failed\n");
		}

		// ZW
		mat5 rotZW = mat5::MakeRotationZW(rad90);
		vec5f ptRotZW = rotZW * ptZ;
		if (!isNearVec5f(ptRotZW, vec5f(0, 0, 0, 1, 1)))
		{
			success = false;
			std::printf("Mat5::RotZW Z failed\n");
		}

		ptRotZW = rotZW * ptW;
		if (!isNearVec5f(ptRotZW, vec5f(0, 0, -1, 0, 1)))
		{
			success = false;
			std::printf("Mat5::RotZW W failed\n");
		}
	}

	// Test Mat4->Mat5 conversion
	{
		mat4 mat4x4 = mat4::MakeTranslation(vec3f(1, 2, 3)) * mat4::MakeRotationYZ(rad90);
		mat5 mat5x5 = mat5(mat4x4);
		
		vec5f ptY = vec5f(0, 1, 0, 0, 1);
		const vec5f expectedPt = vec5f(1, 2, 4, 0, 1);	// should rotate +Y to +Z, then translate by (1,2,3)

		vec5f transPtY = mat5x5 * ptY;

		if (!isNearVec5f(transPtY, expectedPt))
		{
			success = false;
			std::printf("Mat5 from Mat4 failed\n");
		}
	}

	// Matrix inversion
	{
		// Mat3
		{
			mat3 mTrans = mat3::MakeTranslation({ 1, -2 }) * mat3::MakeRotation(0.5f) * mat3::MakeScale(1.5f, 0.75f);
			mat3 mTransInv = mat3::Invert(mTrans);

			const vec3f pt = { 1.1f, 1.2f, 1.0f };
			const vec3f transInvPt = mTransInv * mTrans * pt;

			if (!isNearVec3f(transInvPt, pt))
			{
				success = false;
				std::printf("Mat3 invert failed\n");
			}
		}

		// Mat4
		{
			mat4 mTrans = mat4::MakeTranslation({ -1, 2, -3 }) *
				mat4::MakeRotationXY(0.1f) *
				mat4::MakeRotationZX(0.2f) *
				mat4::MakeRotationYZ(0.3f) *
				mat4::MakeScale({ 1.1f, 0.9f, 1.2f });
			mat4 mTransInv = mat4::Invert(mTrans);

			const vec4f pt = { 1.1f, 1.2f, 1.3f, 1.0f };
			const vec4f transInvPt = mTransInv * mTrans * pt;

			if (!isNearVec4f(transInvPt, pt))
			{
				success = false;
				std::printf("Mat4 invert failed\n");
			}
		}

		// Mat5
		{
			mat5 mTrans = mat5::MakeTranslation({ 1, -2, 3, -4 }) *
				mat5::MakeRotationXY(0.1f) *
				mat5::MakeRotationZX(0.2f) *
				mat5::MakeRotationXW(0.3f) *
				mat5::MakeRotationYZ(0.4f) *
				mat5::MakeRotationWY(0.5f) *
				mat5::MakeRotationZW(0.6f) *
				mat5::MakeScale({ 1.1f, 0.9f, 1.2f, 0.8f });
			mat5 mTransInv = mat5::Invert(mTrans);

			const vec5f pt = { 1.1f, 1.2f, 1.3f, 1.4f, 1.0f };
			const vec5f transInvPt = mTransInv * mTrans * pt;

			if (!isNearVec5f(transInvPt, pt))
			{
				success = false;
				std::printf("Mat5 invert failed\n");
			}
		}
	}

	// Matrix LookAt
	{
		// standard 3D coordinate frame, no rotation
		{
			vec3f to = { 0,0,-1 };
			vec3f from = { 0,0,0 };
			vec3f sceneUp = { 0,1,0 };

			const vec4f forwardPt = { 0, 0, -2, 1 };
			const vec4f backwardPt = { 0, 0, 3, 1 };
			const vec4f rightPt = { 4,0,0,1 };
			const vec4f leftPt = { -5,0,0,1 };
			const vec4f upPt = { 0,6,0,1 };
			const vec4f downPt = { 0,-7,0,1 };

			const mat4 lookedAt = mat4::LookAt(from, to, sceneUp);

			vec4f transForward = lookedAt * forwardPt;	// expect -Z
			vec4f transBackward = lookedAt * backwardPt;	// expect +Z
			vec4f transRight = lookedAt * rightPt;	// expect +X
			vec4f transLeft = lookedAt * leftPt;	// expect -X
			vec4f transUp = lookedAt * upPt;	// expect +Y
			vec4f transDown = lookedAt * downPt;	// expect -Y

			if (!isNearVec4f(transForward, vec4f(0, 0, -2, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt -Z forward failed\n");
			}

			if (!isNearVec4f(transBackward, vec4f(0, 0, 3, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt -Z backward failed\n");
			}

			if (!isNearVec4f(transRight, vec4f(4, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt -Z right failed\n");
			}

			if (!isNearVec4f(transLeft, vec4f(-5, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt -Z left failed\n");
			}

			if (!isNearVec4f(transUp, vec4f(0, 6, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt -Z up failed\n");
			}

			if (!isNearVec4f(transDown, vec4f(0, -7, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt -Z down failed\n");
			}
		}

		// looking toward +X
		{
			const vec3f to = { 1,0,0 };
			const vec3f from = { 0,0,0 };
			const vec3f sceneUp = { 0,1,0 };

			const vec4f forwardPt = { 2, 0, 0, 1 };
			const vec4f backwardPt = { -3, 0, 0, 1 };
			const vec4f rightPt = { 0,0,4,1 };
			const vec4f leftPt = { 0,0,-5,1 };
			const vec4f upPt = { 0,6,0,1 };
			const vec4f downPt = { 0,-7,0,1 };

			const mat4 lookedAt = mat4::LookAt(from, to, sceneUp);

			vec4f transForward = lookedAt * forwardPt;	// expect -Z
			vec4f transBackward = lookedAt * backwardPt;	// expect +Z
			vec4f transRight = lookedAt * rightPt;	// expect +X
			vec4f transLeft = lookedAt * leftPt;	// expect -X
			vec4f transUp = lookedAt * upPt;	// expect +Y
			vec4f transDown = lookedAt * downPt;	// expect -Y

			if (!isNearVec4f(transForward, vec4f(0, 0, -2, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt +X forward failed\n");
			}

			if (!isNearVec4f(transBackward, vec4f(0, 0, 3, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt +X backward failed\n");
			}

			if (!isNearVec4f(transRight, vec4f(4, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt +X right failed\n");
			}

			if (!isNearVec4f(transLeft, vec4f(-5, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt +X left failed\n");
			}

			if (!isNearVec4f(transUp, vec4f(0, 6, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt +X up failed\n");
			}

			if (!isNearVec4f(transDown, vec4f(0, -7, 0, 1)))
			{
				success = false;
				std::printf("Mat4 lookAt +X down failed\n");
			}
		}

		// standard 4D coordinate frame, no rotation
		{
			vec4f to = { 0,0,-1,0 };
			vec4f from = { 0,0,0,0 };
			vec4f sceneUp = { 0,1,0,0 };
			vec4f sceneOver = { 0,0,0,1 };

			const vec5f forwardPt = { 0,0,-2,0,1 };
			const vec5f backwardPt = { 0,0,3,0,1 };
			const vec5f rightPt = { 4,0,0,0,1 };
			const vec5f leftPt = { -5,0,0,0,1 };
			const vec5f upPt = { 0,6,0,0,1 };
			const vec5f downPt = { 0,-7,0,0,1 };
			const vec5f anaPt = { 0,0,0,8,1 };
			const vec5f kataPt = { 0,0,0,-9,1 };

			mat5 lookedAt = mat5::LookAt(from, to, sceneUp, sceneOver);

			vec5f transForward = lookedAt * forwardPt;	// expect -Z
			vec5f transBackward = lookedAt * backwardPt;	// expect +Z
			vec5f transRight = lookedAt * rightPt;	// expect +X
			vec5f transLeft = lookedAt * leftPt;	// expect -X
			vec5f transUp = lookedAt * upPt;	// expect +Y
			vec5f transDown = lookedAt * downPt;	// expect -Y
			vec5f transAna = lookedAt * anaPt;	// expect +W
			vec5f transKata = lookedAt * kataPt;	// expect -W

			if (!isNearVec5f(transForward, vec5f(0, 0, -2, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z forward failed\n");
			}

			if (!isNearVec5f(transBackward, vec5f(0, 0, 3, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z backward failed\n");
			}

			if (!isNearVec5f(transRight, vec5f(4, 0, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z right failed\n");
			}

			if (!isNearVec5f(transLeft, vec5f(-5, 0, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z left failed\n");
			}

			if (!isNearVec5f(transUp, vec5f(0, 6, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z up failed\n");
			}

			if (!isNearVec5f(transDown, vec5f(0, -7, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z down failed\n");
			}

			if (!isNearVec5f(transAna, vec5f(0, 0, 0, 8, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z ana failed\n");
			}

			if (!isNearVec5f(transKata, vec5f(0, 0, 0, -9, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -Z kata failed\n");
			}
		}

		// 4D coordinate frame, looking along +X
		{
			vec4f to = { 1,0,0,0 };
			vec4f from = { 0,0,0,0 };
			vec4f sceneUp = { 0,1,0,0 };
			vec4f sceneOver = { 0,0,0,1 };

			const vec5f forwardPt = { 2,0,0,0,1 };
			const vec5f backwardPt = { -3,0,0,0,1 };
			const vec5f rightPt = { 0,0,4,0,1 };
			const vec5f leftPt = { 0,0,-5,0,1 };
			const vec5f upPt = { 0,6,0,0,1 };
			const vec5f downPt = { 0,-7,0,0,1 };
			const vec5f anaPt = { 0,0,0,8,1 };
			const vec5f kataPt = { 0,0,0,-9,1 };

			mat5 lookedAt = mat5::LookAt(from, to, sceneUp, sceneOver);

			vec5f transForward = lookedAt * forwardPt;	// expect -Z
			vec5f transBackward = lookedAt * backwardPt;	// expect +Z
			vec5f transRight = lookedAt * rightPt;	// expect +X
			vec5f transLeft = lookedAt * leftPt;	// expect -X
			vec5f transUp = lookedAt * upPt;	// expect +Y
			vec5f transDown = lookedAt * downPt;	// expect -Y
			vec5f transAna = lookedAt * anaPt;	// expect +W
			vec5f transKata = lookedAt * kataPt;	// expect -W

			if (!isNearVec5f(transForward, vec5f(0, 0, -2, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X forward failed\n");
			}

			if (!isNearVec5f(transBackward, vec5f(0, 0, 3, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X backward failed\n");
			}

			if (!isNearVec5f(transRight, vec5f(4, 0, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X right failed\n");
			}

			if (!isNearVec5f(transLeft, vec5f(-5, 0, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X left failed\n");
			}

			if (!isNearVec5f(transUp, vec5f(0, 6, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X up failed\n");
			}

			if (!isNearVec5f(transDown, vec5f(0, -7, 0, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X down failed\n");
			}

			if (!isNearVec5f(transAna, vec5f(0, 0, 0, 8, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X ana failed\n");
			}

			if (!isNearVec5f(transKata, vec5f(0, 0, 0, -9, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt +X kata failed\n");
			}
		}

		// 4D coordinate frame, looking along -X, with some translation
		{
			vec4f to = { -1,0,0,0 };
			vec4f from = { 1,0,0,0 };
			vec4f sceneUp = { 0,1,0,0 };
			vec4f sceneOver = { 0,0,0,1 };

			const vec5f forwardPt = { -2.2f,0,0,0,1 };
			const vec5f backwardPt = { 3.3f,0,0,0,1 };
			const vec5f rightPt = { 0,0,-4,0,1 };
			const vec5f leftPt = { 0,0,5,0,1 };
			const vec5f upPt = { 0,6,0,0,1 };
			const vec5f downPt = { 0,-7,0,0,1 };
			const vec5f anaPt = { 0,0,0,8,1 };
			const vec5f kataPt = { 0,0,0,-9,1 };

			mat5 lookedAt = mat5::LookAt(from, to, sceneUp, sceneOver);

			vec5f transForward = lookedAt * forwardPt;	// expect -Z
			vec5f transBackward = lookedAt * backwardPt;	// expect +Z
			vec5f transRight = lookedAt * rightPt;	// expect +X
			vec5f transLeft = lookedAt * leftPt;	// expect -X
			vec5f transUp = lookedAt * upPt;	// expect +Y
			vec5f transDown = lookedAt * downPt;	// expect -Y
			vec5f transAna = lookedAt * anaPt;	// expect +W
			vec5f transKata = lookedAt * kataPt;	// expect -W

			if (!isNearVec5f(transForward, vec5f(0, 0, -3.2f, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated forward failed\n");
			}

			if (!isNearVec5f(transBackward, vec5f(0, 0, 2.3f, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated backward failed\n");
			}

			if (!isNearVec5f(transRight, vec5f(4, 0, -1, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated right failed\n");
			}

			if (!isNearVec5f(transLeft, vec5f(-5, 0, -1, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated left failed\n");
			}

			if (!isNearVec5f(transUp, vec5f(0, 6, -1, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated up failed\n");
			}

			if (!isNearVec5f(transDown, vec5f(0, -7, -1, 0, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated down failed\n");
			}

			if (!isNearVec5f(transAna, vec5f(0, 0, -1, 8, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated ana failed\n");
			}

			if (!isNearVec5f(transKata, vec5f(0, 0, -1, -9, 1)))
			{
				success = false;
				std::printf("Mat5 lookAt -X translated kata failed\n");
			}
		}
	}

	return success;
}

bool testAABB()
{
	bool success = true;

	// AABB3F
	{
		aabb3f b1 = aabb3f(vec3f(0, 1, 2), vec3f(1, 3, 5));
		aabb3f b2 = { vec3f(2, 4, 6), vec3f(3, 5, 7) };
		aabb3f b3 = b1;
		aabb3f b4 = b2;

		// [] access
		vec3f min1 = b1.min();
		vec3f min2 = b2[0];
		vec3f max2 = { b2._v[3], b2._v[4], b2._v[5] };

		// [] modifying
		b1[0] = { 7, 8, 9 };
		if (b1[0] != vec3f(7, 8, 9))
		{
			std::printf("AABB3 [] operator failed\n");
			success = false;
		}

		// centroid
		vec3f centroid3 = b3.centroid();
		if (centroid3 != vec3f(0.5f, 2.0f, 3.5f))
		{
			std::printf("AABB3 centroid failed\n");
			success = false;
		}

		float centroid4axis0 = b4.centroid(0);
		if (centroid4axis0 != 2.5f)
		{
			std::printf("AABB3 centroid axis failed\n");
			success = false;
		}
	}

	// AABB4F
	{
		// surface volume
		aabb4f b1 = aabb4f(vec4f(0), vec4f(1, 2, 3, 4));
		const float expectedVolumeB1 = 100.f;	// 2 * ((1 * 2 * 3) + (1 * 2 * 4) + (1 * 3 * 4) + (2 * 3 * 4))
		const float volumeB1 = b1.volume();
		if (volumeB1 != expectedVolumeB1)
		{
			std::printf("AABB4F surface volume failed\n");
			success = false;
		}
	}


	return success;
}

bool testRay()
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

bool testRotor()
{
	bool success = true;

	// basic principal planes
	{
		vec4f fromVec = { 1, 0, 0, 0 };
		vec4f toVec = { 0, 1, 0, 0 };
		rotor4 rotor;
		rotor.fromTo(fromVec, toVec);

		vec4f testPt = { 2, 0, 0, 0 };
		const vec4f expectedResult = { 0, 2, 0, 0 };
		vec4f rotoredPt = rotor.transform(testPt);

		if (!isNearVec4f(rotoredPt, expectedResult))
		{
			success = false;
			std::printf("XY rotor rotation failed\n");
		}

		mat5 mRotor = rotor.matrix();
		vec4f matrixedPt = mRotor * vec5f(testPt, 1.0f);
		if (!isNearVec4f(matrixedPt, expectedResult))
		{
			success = false;
			std::printf("XY rotor matrix rotation failed\n");
		}
	}

	// all principal planes, 45 and 90 degrees
	{
		const size_t NUM_DIMENSIONS = 4;
		const size_t NUM_ANGLES = 10;
		const size_t NUM_SCALES = 3;
		for (size_t j = 0; j < NUM_DIMENSIONS; j++)
		{
			for (size_t i = 0; i < NUM_DIMENSIONS; i++)
			{
				if (i == j) continue;
				for (size_t a = 0; a < NUM_ANGLES; a++)
				{
					for (size_t s = 0; s < NUM_SCALES; s++)
					{
						float scale = (s * 0.25f) + 0.75f;	// 0.75, 1.0, 1.25
						float angleDegrees = (a * 15.0f) + 30.0f;
						float angle = toRad(angleDegrees);	// 30, 45, 60, 75, 90, 105, 120, 135, 150, 165

						vec4f fromVec = 0;
						fromVec[i] = 1.0f;

						float sinj = std::sin(angle);
						float cosj = std::cos(angle);
						vec4f toVec = 0;
						toVec[i] = cosj;
						toVec[j] = sinj;

						const vec4f testPt = fromVec * scale;
						const vec4f expectedResult = toVec * scale;

						// regular fromTo
						rotor4 rotor = rotor4(fromVec, toVec);
						vec4f resultPt = rotor.transform(testPt);
						if (!isNearVec4f(resultPt, expectedResult))
						{
							success = false;
							std::printf("Principal plane (%i, %i) at angle %f and scale %f failed\n", int(i), int(j), angleDegrees, scale);
						}

						// trig fromTo
						rotor4 rotorTrig;
						rotorTrig.fromToTrig(fromVec, toVec);
						resultPt = rotorTrig.transform(testPt);
						if (!isNearVec4f(resultPt, expectedResult))
						{
							success = false;
							std::printf("Principal plane (%i, %i) at angle %f and scale % f using trig failed\n", int(i), int(j), angleDegrees, scale);
						}

						// matrix
						mat5 mRotor = rotor.matrix();
						const vec4f matrixedPt = mRotor * vec5f(testPt, 1.0f);
						if (!isNearVec4f(matrixedPt, expectedResult))
						{
							success = false;
							std::printf("Principal plane (%i, %i) at angle %f and scale %f using matrix rotation failed\n", int(i), int(j), angleDegrees, scale);
						}
					}
				}
			}
		}
	}

	// test trig version
	{
		vec4f fromVec = { 0, 0, 1, 0 };
		vec4f toVec = { 0, 0, 0, -1 };
		rotor4 rotor;
		rotor.fromToTrig(fromVec, toVec);

		vec4f testPt = { 0, 0, 1, 0 };
		const vec4f expectedResult = { 0, 0, 0, -1 };
		vec4f rotoredPt = rotor.transform(testPt);

		if (!isNearVec4f(rotoredPt, expectedResult))
		{
			success = false;
			std::printf("Trig fromTo rotation failed\n");
		}

		mat5 mRotor = rotor.matrix();
		vec4f matrixedPt = mRotor * vec5f(testPt, 1.0f);
		if (!isNearVec4f(matrixedPt, expectedResult))
		{
			success = false;
			std::printf("Trig fromTo matix rotation failed\n");
		}
	}

	// test combining rotors
	{
		vec4f fromVec1 = { 1, 0, 0, 0 };
		vec4f toVec1 = { 0, 1, 0, 0 };
		vec4f fromVec2 = { 0, 1, 0, 0 };
		vec4f toVec2 = { 0, 0, 1, 0 };

		rotor4 rotor1;
		rotor1.fromTo(fromVec1, toVec1);

		rotor4 rotor2;
		rotor2.fromTo(fromVec2, toVec2);

		// NOTE: combination order is similar to column-major matrix multiplication, right to left
		// i.e. "rotor2 * rotor1 * pt"  means rotate pt by rotor1 first, then by rotor2 second
		rotor4 rCombined = rotor2 * rotor1;

		// this would be the combination of these rotors in reverse order
		//rotor4 rCombined2 = rotor1 * rotor2;

		// expected result: x -> y -> z
		const vec4f testPt = { 1, 0, 0, 0 };

		vec4f ptRotoredSequential = rotor2.transform(rotor1.transform(testPt));
		vec4f ptRotoredCombined = rCombined.transform(testPt);

		if (!isNearVec4f(ptRotoredSequential, ptRotoredCombined))
		{
			success = false;
			std::printf("Rotor combining failed\n");
		}

		// test the operator*() also
		ptRotoredSequential = rotor2 * (rotor1 * testPt);
		ptRotoredCombined = rCombined * testPt;

		if (!isNearVec4f(ptRotoredSequential, ptRotoredCombined))
		{
			success = false;
			std::printf("Rotor combining operator*() failed\n");
		}
	}

	// test reverse directions
	{
		vec4f fromVec = { 1, 0, 0, 0 };
		vec4f toVec = { 0, 1, 0, 0 };
		rotor4 rotorForward;
		rotorForward.fromTo(fromVec, toVec);

		rotor4 rotorReverse = rotorForward;
		rotorReverse.reverse();

		vec4f testPt = { 1, 0, 0, 0 };
		const vec4f expectedPt = { 0, -1, 0, 0 };
		vec4f reverseRotoredPt = rotorReverse.transform(testPt);

		if (!isNearVec4f(reverseRotoredPt, expectedPt))
		{
			success = false;
			std::printf("Reverse rotor transform failed\n");
		}
	}

	// test non-principal planes
	{
		vec4f fromVec = { 1, 2, 3, 4 };
		vec4f toVec = { 4, 3, 2, 1 };

		vec4f fromVecNorm = normalize(fromVec);
		vec4f toVecNorm = normalize(toVec);

		// for this test, test point should be colinear with fromVec
		vec4f testPt = fromVec * 2.0f;
		float testPtLen = testPt.length();

		// the result will be colinear with toVec, but should retain its length
		const vec4f expectedResult = toVecNorm * testPtLen;

		rotor4 rotor = rotor4(fromVec, toVec);

		vec4f resultPt = rotor.transform(testPt);

		float resultPtLen = resultPt.length();
		

		if (!isNearVec4f(resultPt, expectedResult))
		{
			success = false;
			std::printf("Non-principal plane rotation failed\n");
		}
	}

	// test 180 and 360 degree rotation
	{
		vec4f fromVec = { 1, 0, 0, 0 };
		vec4f toVec45 = { 1.0f / std::sqrt(2.0f), 1.0f / std::sqrt(2.0f), 0, 0 };
		vec4f toVec90 = { 0, 1, 0, 0 };

		rotor4 rotor45xy = rotor4(fromVec, toVec45);
		rotor4 rotor4545xy = rotor45xy * rotor45xy;
		rotor4 rotor90xy = rotor4(fromVec, toVec90);
		rotor4 rotor9090xy = rotor90xy * rotor90xy;

		vec4f testPt = { 1, 0, 0, 0 };
		vec4f resultPt45 = rotor45xy * testPt;
		vec4f resultPt4545 = rotor4545xy * testPt;
		vec4f resultPt90 = rotor90xy * testPt;
		vec4f resultPt9090 = rotor9090xy * testPt;
		vec4f resultPt360 = rotor9090xy * rotor9090xy * testPt;

		if (!isNearVec4f(resultPt4545, resultPt90))
		{
			success = false;
			std::printf("Double 45 not equal to 90\n");
		}

		if (!isNearVec4f(resultPt9090, -fromVec))
		{
			success = false;
			std::printf("Double 90 not equal to 180\n");
		}

		if (!isNearVec4f(resultPt360, testPt))
		{
			success = false;
			std::printf("Quadruple 90 not equal to original point\n");
		}
	}

	// test near 180 degree rotation
	{
		vec4f fromVec = { 0, 0, 0, 1 };
		vec4f toVecAlmost180 = { 0.01f, 0, 0, -1 };
		rotor4 rotAlmost180XW = rotor4(fromVec, toVecAlmost180);

		vec4f ptX = { 1, 0, 0, 0 };
		vec4f ptY = { 0, 1, 0, 0 };
		vec4f ptZ = { 0, 0, 1, 0 };
		vec4f ptW = { 0, 0, 0, 1 };

		vec4f transX = rotAlmost180XW * ptX;
		vec4f transY = rotAlmost180XW * ptY;
		vec4f transZ = rotAlmost180XW * ptZ;
		vec4f transW = rotAlmost180XW * ptW;

		int todoremove = 2;
	}

	return success;
}

double dotDouble(const hxm::vec4f& a, const hxm::vec4f& b)
{
	return double(a.x) * double(b.x) +
		double(a.y) * double(b.y) +
		double(a.z) * double(b.z) +
		double(a.w) * double(b.w);
}

double lengthDouble(const hxm::vec4f& v)
{
	return std::sqrt(dotDouble(v, v));
}

double onbError(hxm::vec4f v0, hxm::vec4f v1, hxm::vec4f v2, hxm::vec4f v3)
{
	// each vector should be unit-length
	double lenErr0 = std::pow(lengthDouble(v0) - 1.0, 2.0);
	double lenErr1 = std::pow(lengthDouble(v1) - 1.0, 2.0);
	double lenErr2 = std::pow(lengthDouble(v2) - 1.0, 2.0);
	double lenErr3 = std::pow(lengthDouble(v3) - 1.0, 2.0);

	// the dot product between each vector should be zero
	double dotV0V1err = std::pow(dotDouble(v0, v1), 2.0);
	double dotV0V2err = std::pow(dotDouble(v0, v2), 2.0);
	double dotV0V3err = std::pow(dotDouble(v0, v3), 2.0);
	double dotV1V2err = std::pow(dotDouble(v1, v2), 2.0);
	double dotV1V3err = std::pow(dotDouble(v1, v3), 2.0);
	double dotV2V3err = std::pow(dotDouble(v2, v3), 2.0);

	return (lenErr0 + lenErr1 + lenErr2 + lenErr3 + dotV0V1err + dotV0V2err + dotV0V3err + dotV1V2err + dotV1V3err + dotV2V3err) / 10.0;
}

bool testONB()
{
	{
		hxm::vec4f inVecX = { 1, 0, 0, 0 };
		hxm::vec4f inVecY = { 0, 1, 0, 0 };
		hxm::vec4f inVecZ = { 0, 0, 1, 0 };
		hxm::vec4f inVecW = { 0, 0, 0, 1 };
		hxm::vec4f onb0, onb1, onb2, onb3;

		{
			makeONB4(inVecX, onb0, onb1, onb2, onb3);

			// just x and w should have changed
		}

		{
			makeONB4(inVecY, onb0, onb1, onb2, onb3);

			// just y and w should have changed
		}

		{
			makeONB4(inVecZ, onb0, onb1, onb2, onb3);

			// just z and w should have changed
		}

		{
			makeONB4(inVecW, onb0, onb1, onb2, onb3);

			// nothing should have changed
		}

		{
			hxm::vec4f inVecAlmostNegW = { 0.001f, 0.001f, 0.001f, -1.0f };
			makeONB4(inVecAlmostNegW, onb0, onb1, onb2, onb3);
			int todoremove = 2;
		}
	}

	// TODO:
	// test all positive axes
	// test all negative axes
	// test a handful of other vectors
	{
		const uint32_t gridSize = 72;
		double maxError = -1.0;
		double totalError = 0.0;

		// maybe just check that it produces a valid orthonormal basis, not necessarily looking for one specific one
		hxm::vec4u idx;
		for (idx.w = 0; idx.w < gridSize; idx.w++)
		{
			for (idx.z = 0; idx.z < gridSize; idx.z++)
			{
				for (idx.y = 0; idx.y < gridSize; idx.y++)
				{
					for (idx.x = 0; idx.x < gridSize; idx.x++)
					{
						hxm::vec4f idxFactor = hxm::vec4f(idx) / hxm::vec4f(gridSize - 1);
						hxm::vec4f toPt = (idxFactor * 2.0f) - 1.0f;

						hxm::vec4f onb0, onb1, onb2, onb3;
						makeONB4(toPt, onb0, onb1, onb2, onb3);

						double err = onbError(onb0, onb1, onb2, onb3);

						if (err != err)
						{
							int todoremove = 2;
						}

						//std::printf("(%i, %i, %i, %i) error: %f\n", idx.x, idx.y, idx.z, idx.w, err * 1e12);

						maxError = std::max(maxError, err);
						totalError += err;
					}
				}
			}
		}

		double avgError = totalError / double(gridSize * gridSize * gridSize * gridSize);

		std::printf("trials: %i\n", int(gridSize * gridSize * gridSize * gridSize));
		std::printf("maxError: %f * 10^14\n", maxError * 1e14);
		std::printf("avgError: %f * 10^14\n", avgError * 1e14);
	}

	return false;
}