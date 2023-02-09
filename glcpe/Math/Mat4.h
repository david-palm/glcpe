#pragma once

#include "Vec2.h"
#include "Vec4.h"
class Mat4
{
public:
	//values are store in column order
	float values[16];

	Mat4();
	Mat4(float value);
	Mat4(Vec2& scale);
	Mat4(Vec4& scale);
	Mat4(Vec4& col1, Vec4& col2, Vec4& col3, Vec4& col4);
	Mat4(float values[16]);
	Mat4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4);

	Mat4 operator+(Mat4& mat) const;
	Mat4 operator-(Mat4& mat) const;
	Mat4 operator*(float scale) const;
	Vec4 operator*(Vec4& vec) const;
	Mat4 operator*(Mat4& mat) const;

	float determinant() const;

};
std::ostream& operator<<(std::ostream& stream, const Mat4& mat);