#include "Vec4.h"
#include <iostream>
#include <math.h>


Vec4::Vec4()
	: x(0), y(0), z(0), w(0)
{
	std::cout << "Created Vec4 with empty constructor \n";
}

Vec4::Vec4(float value)
	: x(value), y(value), z(value), w(value)
{
	std::cout << "Created Vec4 with float constructor \n";
}

Vec4::Vec4(float x, float y)
	: x(x), y(y), z(0), w(0)
{
	std::cout << "Created Vec4 with 2 times float constructor \n";
}

Vec4::Vec4(const Vec2& vec)
	: x(vec.x), y(vec.y), z(0), w(0)
{
	std::cout << "Created Vec4 with Vec2 constructor \n";
}

Vec4::Vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
	std::cout << "Created Vec4 with 4 times float constructor \n";
}

Vec4 Vec4::operator+(float value) const
{
	return Vec4(x + value, y + value, z + value, w + value);
}

Vec4 Vec4::operator+(const Vec2& vec) const
{
	return Vec4(x + vec.x, y + vec.y, z, w);
}

Vec4 Vec4::operator+(const Vec4& vec) const
{
	return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vec4 Vec4::operator-(float value) const
{
	return Vec4(x - value, y - value, z - value, w - value);
}

Vec4 Vec4::operator-(const Vec2& vec) const
{
	return Vec4(x - vec.x, y - vec.y, z, w);
}

Vec4 Vec4::operator-(const Vec4& vec) const
{
	return Vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vec4 Vec4::operator*(float value) const
{
	return Vec4(x * value, y * value, z * value, w * value);
}

Vec4 Vec4::operator*(const Vec2& vec) const
{
	return Vec4(x * vec.x, y * vec.y, z, w);
}
Vec4 Vec4::operator*(const Vec4& vec) const
{
	return Vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

Vec4 Vec4::operator/(float value) const
{
	return Vec4(x / value, y / value, z / value, w / value);
}

Vec4 Vec4::operator/(const Vec2& vec) const
{
	return Vec4(x + vec.x, y + vec.y, z, w);
}

Vec4 Vec4::operator/(const Vec4& vec) const
{
	return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

void Vec4::operator+=(float value)
{
	x += value;
	y += value;
	z += value;
	w += value;
}

void Vec4::operator+=(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vec4::operator+=(const Vec4& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
}

void Vec4::operator-=(float value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
}

void Vec4::operator-=(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vec4::operator-=(const Vec4& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
}

void Vec4::operator*=(float value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
}

void Vec4::operator*=(const Vec2& vec)
{
	x *= vec.x;
	y *= vec.y;
}

void Vec4::operator*=(const Vec4& vec)
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;
}

void Vec4::operator/=(float value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
}

void Vec4::operator/=(const Vec2& vec)
{
	x /= vec.x;
	y /= vec.y;
}

void Vec4::operator/=(const Vec4& vec)
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	w /= vec.w;
}

void Vec4::negate()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}

float Vec4::length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

void Vec4::normalize() {
	float length = this->length();
	x /= length;
	y /= length;
	z /= length;
	w /= length;
}

std::ostream& operator<<(std::ostream& stream, const Vec4& vec)
{
	return stream << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
	return stream;
}
