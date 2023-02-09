#pragma once
#include "Vec2.h"
#include <iostream>
class Vec4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vec4();
	Vec4(float value);
	Vec4(float x, float y);
	Vec4(const Vec2& vec);
	Vec4(float x, float y, float z, float w);

	Vec4 operator+(float value) const;
	Vec4 operator+(const Vec2& vec) const;
	Vec4 operator+(const Vec4& vec) const;
	Vec4 operator-(float value) const;
	Vec4 operator-(const Vec2& vec) const;
	Vec4 operator-(const Vec4& vec) const;
	Vec4 operator*(float value) const;
	Vec4 operator*(const Vec2& vec) const;
	Vec4 operator*(const Vec4& vec) const;
	Vec4 operator/(float value) const;
	Vec4 operator/(const Vec2& vec) const;
	Vec4 operator/(const Vec4& vec) const;

	void operator+=(float value);
	void operator+=(const Vec2& vec);
	void operator+=(const Vec4& vec);
	void operator-=(float value);
	void operator-=(const Vec2& vec);
	void operator-=(const Vec4& vec);
	void operator*=(float value);
	void operator*=(const Vec2& vec);
	void operator*=(const Vec4& vec);
	void operator/=(float value);
	void operator/=(const Vec2& vec);
	void operator/=(const Vec4& vec);

	void negate();
	float length() const;
	void normalize();
};
std::ostream& operator<<(std::ostream& stream, const Vec4& vec);