#ifndef __DS_MATH_DEF_INC__
#define __DS_MATH_DEF_INC__

#include <math.h>

// 取绝对值、最大值、最小值
//////////////////////////////////////////////////////////////////////////
// 浮点数定义

// float 精度为 6 到 7 位
#ifndef ABS_FLOAT_0
#define ABS_FLOAT_0  1.1e-6f
#endif

// 取整
inline int float_to_int(IN float x)
{
	return (int)(x + ((x < 0.f) ? -0.5f : 0.5f)); 
}
// 比较
inline BOOL float_iszero(IN float x)
{
	return (x <= ABS_FLOAT_0 && x >= -ABS_FLOAT_0);
}
inline BOOL float_isequal(IN float x, IN float y)
{
	return float_iszero(x - y);
}

//////////////////////////////////////////////////////////////////////////
// 角度与弧度的定义

#ifndef PAI
#define PAI 3.14159265
#endif

#ifndef PAI_2
#define PAI_2 6.28318531
#endif

const int ANGLE_HALF_PI		= 90;
const int ANGLE_PI			= 180;
const int ANGLE_2_PI		= 360;
const float RADIAN_HALF_PI	= 1.5707963f;
const float RADIAN_PI		= 3.1415927f;
const float RADIAN_2_PI		= 6.2831853f;

const float RADIAN_2_PI_INV	= 0.1591549f;		// 0.5f / PI
const float ANGLE_2_PI_INV	= 0.0027778f;		// 1.f / 360
const float ANGLE_TO_RADIAN	= 0.0174533f;		// PI / 180
const float RADIAN_TO_ANGLE	= 57.2957795f;		// 180 / PI

const float POUND_TO_PIXELS = 1.3333f;           // 4.0 / 3.0
const float PIXELS_TO_POUND = 0.75f;           // 3.0 / 4.0

// 对角度与弧度进行裁减
inline float clampradian_pi_pn(IN float fRad)	// [-PI, PI]
{
	return (fRad - floorf((fRad + RADIAN_PI) * RADIAN_2_PI_INV) * RADIAN_2_PI);
}
inline float clampradian_pi_2(IN float fRad)		// [0, PI_2)
{
	return (fRad - floorf(fRad * RADIAN_2_PI_INV) * RADIAN_2_PI);
}
inline int clampangle_pi_pn(IN int nAngle)	// [-180, 180]
{
	return (nAngle - (int)floorf((nAngle + ANGLE_PI) * ANGLE_2_PI_INV) * ANGLE_2_PI);
}
inline int clampangle_pi_2(IN int nAngle)	// [0, 360)
{
	return (nAngle - (int)floorf(nAngle * ANGLE_2_PI_INV) * ANGLE_2_PI);
}

// 角度与弧度之间的变换
inline int radian_to_angle(IN float fRad)
{
	return float_to_int(fRad * RADIAN_TO_ANGLE);
}
inline float angle_to_radian(IN int nAngle)
{
	return (nAngle * ANGLE_TO_RADIAN);
}

// 磅与像素之间变换
inline float pound_to_piexls(IN float fPound)
{
	return (fPound * POUND_TO_PIXELS);
}

inline float piexls_to_pound(IN float fPiexls)
{
	return (fPiexls * PIXELS_TO_POUND);
}

#endif		// #ifndef __DS_MATH_DEF_INC__
//////////////////////////////////////////////////////////////////////////
// End of file.
