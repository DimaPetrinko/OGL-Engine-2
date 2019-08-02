#include <OGLEpch.h>
#include "Math.h"

namespace OGLEngine2
{
	Vector2::Vector2(float x, float y) 
	{
		this->x = x;
		this->y = y;
	}

	void Vector2::Normalize()
	{
		float m = Magnitude();
		x /= m;
		y /= m;
	}
	Vector2 Vector2::Normalized() const
	{
		float m = Magnitude();
		return Vector2(x / m, y / m);
	}
	float Vector2::Magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2 Vector2::operator+ (Vector2 other)
	{
		return Vector2(x + other.x, y + other.y);
	}
	void Vector2::operator+= (Vector2 other)
	{
		x += other.x;
		y += other.y;
	}

	Vector2 Vector2::operator- (Vector2 other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	void Vector2::operator-= (Vector2 other)
	{
		x -= other.x;
		y -= other.y;
	}

	Vector2 Vector2::operator* (float scale)
	{
		return Vector2(x * scale, y * scale);
	}
	void Vector2::operator*= (float scale)
	{
		x *= scale;
		y *= scale;
	}

	Vector2 Vector2::operator/ (float scale)
	{
		return Vector2(x / scale, y / scale);
	}
	void Vector2::operator/= (float scale)
	{
		x /= scale;
		y /= scale;
	}

	Vector2 Vector2::operator* (Vector2 other)
	{
		return Vector2(x * other.x, y * other.y);
	}
	void Vector2::operator*= (Vector2 other)
	{
		x *= other.x;
		y *= other.y;
	}

	Vector2 Vector2::operator/ (Vector2 other)
	{
		return Vector2(x / other.x, y / other.y);
	}
	void Vector2::operator/= (Vector2 other)
	{
		x /= other.x;
		y /= other.y;
	}

	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
	Vector2 Vector2::Cross(const Vector2& a)
	{
		return Vector2(a.y, -a.x);
	}
	/*Angle in radians*/
	float Vector2::Angle(const Vector2& a, const Vector2& b)
	{
		return std::acosf(Dot(a, b) / (a.Magnitude() * b.Magnitude()));
	}
}