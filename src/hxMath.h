/*
hxMath.h
July 18, 2024
Contributors:
Justin Jensen
*/

#pragma once

namespace hxm
{
	// 3.1415926535 8979323846 2643383279
#define HX_PI_D 3.141592653589793
#define HX_PI 3.14159265f
#define INVALID64 SIZE_MAX
#define INVALID32 UINT_MAX

	inline float toRad(float thetaDeg)
	{
		return (thetaDeg / 180.0f) * HX_PI;
	}

	inline float toDeg(float thetaRad)
	{
		return (thetaRad / HX_PI) * 180.0f;
	}
}