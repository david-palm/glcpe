#include <iostream>
#include "Mat4.h"
#include "Vec2.h"
#include "Vec4.h"

Mat4::Mat4()
	: values{ 1, 0, 0, 0, 
			  0, 1, 0, 0, 
			  0, 0, 1, 0,
			  0, 0, 0, 1 }
{
	std::cout << "Created Matrix with empty constructor \n";
}

Mat4::Mat4(float value)
	: values{ value, 0, 0, 0,
			  0, value, 0, 0,
			  0, 0, value, 0,
			  0, 0, 0, value }
{
	std::cout << "Created Matrix with float constructor \n";
}

Mat4::Mat4(Vec2& scale)
	: values{ scale.x, 0, 0, 0,
			  0, scale.y, 0, 0,
			  0, 0, 1, 0,
			  0, 0, 0, 1 }
{
	std::cout << "Created Matrix with Vec2 constructor \n";
}

Mat4::Mat4(Vec4& scale)
	: values{ scale.x, 0, 0, 0,
			  0, scale.y, 0, 0,
			  0, 0, scale.z, 0,
			  0, 0, 0, scale.w }
{
	std::cout << "Created Matrix with Vec4 constructor \n";
}

Mat4::Mat4(Vec4& col1, Vec4& col2, Vec4& col3, Vec4& col4)
	: values{ col1.x, col1.y, col1.z, col1.w,
			  col2.x, col2.y, col2.z, col2.w,
			  col3.x, col3.y, col3.z, col3.w,
			  col4.x, col4.y, col4.z, col4.w }
{
	std::cout << "Created Matrix with 4 times Vec4 constructor \n";
}


Mat4::Mat4(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2, float x3, float y3, float z3, float w3, float x4, float y4, float z4, float w4)
	: values{ x1, y1, z1, w1,
			  x2, y2, z2, w2,
			  x3, y3, z3, w3,
			  x4, y4, z4, w4}
{
	std::cout << "Created Matrix with 16 times float constructor \n";
}


Mat4 Mat4::operator+(Mat4& mat) const
{
	return Mat4(values[0] + mat.values[0], values[1] + mat.values[1], values[2] + mat.values[2], values[3] + mat.values[3],
				values[4] + mat.values[4], values[5] + mat.values[5], values[6] + mat.values[6], values[7] + mat.values[7],
				values[8] + mat.values[8], values[9] + mat.values[9], values[10] + mat.values[10], values[11] + mat.values[11],
				values[12] + mat.values[12], values[13] + mat.values[13], values[14] + mat.values[14], values[15] + mat.values[15]);
}

Mat4 Mat4::operator-(Mat4& mat) const
{
	return Mat4(values[0] - mat.values[0], values[1] - mat.values[1], values[2] - mat.values[2], values[3] - mat.values[3],
				values[4] - mat.values[4], values[5] - mat.values[5], values[6] - mat.values[6], values[7] - mat.values[7],
				values[8] - mat.values[8], values[9] - mat.values[9], values[10] - mat.values[10], values[11] - mat.values[11],
				values[12] - mat.values[12], values[13] - mat.values[13], values[14] - mat.values[14], values[15] - mat.values[15]);
}

Mat4 Mat4::operator*(float scale) const
{
	return Mat4(values[0] * scale, values[1] * scale, values[2] * scale, values[3] * scale,
				values[4] * scale, values[5] * scale, values[6] * scale, values[7] * scale,
				values[8] * scale, values[9] * scale, values[10] * scale, values[11] * scale,
				values[12] * scale, values[13] * scale, values[14] * scale, values[15] * scale);
}

Vec4 Mat4::operator*(Vec4& vec) const
{
	return Vec4(values[0] * vec.x + values[4] * vec.y + values[8] * vec.z + values[12] * vec.w,
				values[1] * vec.x + values[5] * vec.y + values[9] * vec.z + values[13] * vec.w,
				values[2] * vec.x + values[6] * vec.y + values[10] * vec.z + values[14] * vec.w,
				values[3] * vec.x + values[7] * vec.y + values[11] * vec.z + values[15] * vec.w);
}

Mat4 Mat4::operator*(Mat4& mat) const
{
	return Mat4(values[0] * mat.values[0] + values[4] * mat.values[1] + values[8] * mat.values[2] + values[12] * mat.values[3],
		values[1] * mat.values[0] + values[5] * mat.values[1] + values[9] * mat.values[2] + values[13] * mat.values[3],
		values[2] * mat.values[0] + values[6] * mat.values[1] + values[10] * mat.values[2] + values[14] * mat.values[3],
		values[3] * mat.values[0] + values[7] * mat.values[1] + values[11] * mat.values[2] + values[15] * mat.values[3],

		values[0] * mat.values[4] + values[4] * mat.values[5] + values[8] * mat.values[6] + values[12] * mat.values[7],
		values[1] * mat.values[4] + values[5] * mat.values[5] + values[9] * mat.values[6] + values[13] * mat.values[7],
		values[2] * mat.values[4] + values[6] * mat.values[5] + values[10] * mat.values[6] + values[14] * mat.values[7],
		values[3] * mat.values[4] + values[7] * mat.values[5] + values[11] * mat.values[6] + values[15] * mat.values[7],

		values[0] * mat.values[8] + values[4] * mat.values[9] + values[8] * mat.values[10] + values[12] * mat.values[11],
		values[1] * mat.values[8] + values[5] * mat.values[9] + values[9] * mat.values[10] + values[13] * mat.values[11],
		values[2] * mat.values[8] + values[6] * mat.values[9] + values[10] * mat.values[10] + values[14] * mat.values[11],
		values[3] * mat.values[8] + values[7] * mat.values[9] + values[11] * mat.values[10] + values[15] * mat.values[11],

		values[0] * mat.values[12] + values[4] * mat.values[13] + values[8] * mat.values[14] + values[12] * mat.values[15],
		values[1] * mat.values[12] + values[5] * mat.values[13] + values[9] * mat.values[14] + values[13] * mat.values[15],
		values[2] * mat.values[12] + values[6] * mat.values[13] + values[10] * mat.values[14] + values[14] * mat.values[15],
		values[3] * mat.values[12] + values[7] * mat.values[13] + values[11] * mat.values[14] + values[15] * mat.values[15]);
}



std::ostream& operator<<(std::ostream& stream, const Mat4& mat)
{
	return stream << "[" << mat.values[0] << ", " << mat.values[4] << ", " << mat.values[8] << ", " << mat.values[12] << "]" << "\n"
				  << "[" << mat.values[1] << ", " << mat.values[5] << ", " << mat.values[9] << ", " << mat.values[13] << "]" << "\n"
				  << "[" << mat.values[2] << ", " << mat.values[6] << ", " << mat.values[10] << ", " << mat.values[14] << "]" << "\n"
				  << "[" << mat.values[3] << ", " << mat.values[7] << ", " << mat.values[11] << ", " << mat.values[15] << "]";
}

float Mat4::determinant() const
{
	return values[0] * values[5] * values[10] * values[15]
		+ values[4] * values[9] * values[14] * values[3]
		+ values[8] * values[13] * values[2] * values[7]
		+ values[12] * values[1] * values[6] * values[11]
		- values[12] * values[9] * values[6] * values[3]
		- values[8] * values[5] * values[2] * values[15]
		- values[4] * values[1] * values[14] * values[11]
		- values[0] * values[13] * values[10] * values[6];
}
