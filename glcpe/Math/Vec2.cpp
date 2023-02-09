#include <iostream>
#include <math.h>
#include "Vec2.h"


Vec2::Vec2()
	: x(0), y(0)
{
	std::cout << "Created Vec2 with empty constructor \n" ;
}

Vec2::Vec2(float value)
	: x(value), y(value)
{
	std::cout << "Created Vec2 with float constructor \n";
}

Vec2::Vec2(float x, float y)
	: x(x), y(y)
{
	std::cout << "Created Vec2 with 2 times float constructor \n";
}

Vec2 Vec2::operator+(float value) const
{
	return Vec2(x + value, y + value);
}

Vec2 Vec2::operator+(const Vec2& vec) const
{
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(float value) const
{
	return Vec2(x - value, y - value);
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator*(float value) const
{
	return Vec2(x * value, y * value);
}

Vec2 Vec2::operator*(const Vec2& vec) const
{
	return Vec2(x * vec.x, y * vec.y);
}

Vec2 Vec2::operator/(float value) const
{
	return Vec2(x / value, y / value);
}

Vec2 Vec2::operator/(const Vec2& vec) const
{
	return Vec2(x / vec.x, y / vec.y);
}

void Vec2::operator+=(float value)
{
	x += value;
	y += value;
}

void Vec2::operator+=(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vec2::operator-=(float value)
{
	x -= value;
	y -= value;
}

void Vec2::operator-=(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vec2::operator*=(float value)
{
	x *= value;
	y *= value;
}

void Vec2::operator*=(const Vec2& vec)
{
	x *= vec.x;
	y *= vec.y;
}

void Vec2::operator/=(float value)
{
	x /= value;
	y /= value;
}

void Vec2::operator/=(const Vec2& vec)
{
	x /= vec.x;
	y /= vec.y;
}

void Vec2::negate()
{
	x = -x;
	y = -y;
}

float Vec2::length() const
{
	return sqrt(x * x + y * y);
}

void Vec2::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
}

std::ostream& operator<<(std::ostream& stream, const Vec2& vec)
{
	return stream << "[" << vec.x << ", " << vec.y << "]";
}