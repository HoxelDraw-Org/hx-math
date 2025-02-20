#pragma once

#include <iostream>
#include "vec.h"
#include "aabb.h"
#include "mat.h"
#include "hxMath.h"
#include "rotor.h"

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

		Mat3 rot = Mat3::MakeRotation(rad90);
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
		Mat4 rotXY = Mat4::MakeRotationXY(rad90);
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
		Mat4 rotZX = Mat4::MakeRotationZX(rad90);
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
		Mat4 rotYZ = Mat4::MakeRotationYZ(rad90);
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
		Mat5 rotXY = Mat5::MakeRotationXY(rad90);
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
		Mat5 rotZX = Mat5::MakeRotationZX(rad90);
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
		Mat5 rotXW = Mat5::MakeRotationXW(rad90);
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
		Mat5 rotYZ = Mat5::MakeRotationYZ(rad90);
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
		Mat5 rotWY = Mat5::MakeRotationWY(rad90);
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
		Mat5 rotZW = Mat5::MakeRotationZW(rad90);
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
		Mat4 mat4x4 = Mat4::MakeTranslation(vec3f(1, 2, 3)) * Mat4::MakeRotationYZ(rad90);
		Mat5 mat5x5 = Mat5(mat4x4);
		
		vec5f ptY = vec5f(0, 1, 0, 0, 1);
		const vec5f expectedPt = vec5f(1, 2, 4, 0, 1);	// should rotate +Y to +Z, then translate by (1,2,3)

		vec5f transPtY = mat5x5 * ptY;

		if (!isNearVec5f(transPtY, expectedPt))
		{
			success = false;
			std::printf("Mat5 from Mat4 failed\n");
		}
	}

	return success;
}

bool testAABB()
{
	bool success = true;

	aabb3 b1 = aabb3(vec3f(0, 1, 2), vec3f(1, 3, 5));
	aabb3 b2 = { vec3f(2, 4, 6), vec3f(3, 5, 7) };
	aabb3 b3 = b1;
	aabb3 b4 = b2;

	// [] access
	vec3f min1 = b1.min;
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

		Mat5 mRotor = rotor.matrix();
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

						float sinj = std::sinf(angle);
						float cosj = std::cosf(angle);
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
						Mat5 mRotor = rotor.matrix();
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

		Mat5 mRotor = rotor.matrix();
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

	return success;
}