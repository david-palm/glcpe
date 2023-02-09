#pragma once
#include <iostream>
class Vec2 
{
public:
	float x;
	float y;

	Vec2();
	Vec2(float value);
	Vec2(float x, float y);

	Vec2 operator+(float value) const;
	Vec2 operator+(const Vec2& vec) const;
	Vec2 operator-(float value) const;
	Vec2 operator-(const Vec2& vec) const;
	Vec2 operator*(float value) const;
	Vec2 operator*(const Vec2& vec) const;
	Vec2 operator/(float value) const;
	Vec2 operator/(const Vec2& vec) const;

	void operator+=(float value);
	void operator+=(const Vec2& vec);
	void operator-=(float value);
	void operator-=(const Vec2& vec);
	void operator*=(float value);
	void operator*=(const Vec2& vec);
	void operator/=(float value);
	void operator/=(const Vec2& vec);

	void negate();
	float length() const;
	void normalize();
};
std::ostream& operator<<(std::ostream& stream, const Vec2& vec);