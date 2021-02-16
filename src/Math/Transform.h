#pragma once
#include "Vec3.h"
#include "Mat4.h"
#include "Mat3.h"

class Transform
{
public:
	Transform();
	virtual ~Transform();
	static Mat3 rotate(const float degrees, const Vec3& axis);
	static Mat4 scale(const float& sx, const float& sy, const float& sz);
	static Mat4 translate(const float& tx, const float& ty, const float& tz);
};

