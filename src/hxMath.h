/*
hxMath.h
July 18, 2024
Contributors:
Justin Jensen
*/

#pragma once

#include "euler6.h"

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

	inline euler6 toRad(const euler6& eDeg)
	{
		euler6 result;
		result.xy = toRad(eDeg.xy);
		result.zx = toRad(eDeg.zx);
		result.xw = toRad(eDeg.xw);
		result.yz = toRad(eDeg.yz);
		result.wy = toRad(eDeg.wy);
		result.zw = toRad(eDeg.zw);
		return result;
	}

	inline euler6 toDeg(const euler6& eRad)
	{
		euler6 result;
		result.xy = toDeg(eRad.xy);
		result.zx = toDeg(eRad.zx);
		result.xw = toDeg(eRad.xw);
		result.yz = toDeg(eRad.yz);
		result.wy = toDeg(eRad.wy);
		result.zw = toDeg(eRad.zw);
		return result;
	}
}