#pragma once
#include <cmath>

//TODO: make more efficient

class Vector2
{
public:
	Vector2() : X(0.0f), Y(0.0f) {}
	Vector2(float n) : X(n), Y(n) {}
	Vector2(float x, float y) : X(x), Y(y) {}

	static inline float Dot(const Vector2& a, const Vector2& b)
	{
		return a.X * b.X + a.Y * b.Y;
	}
	static inline float Magnitude(const Vector2& vec)
	{
		return std::sqrt(vec.X * vec.X + vec.Y * vec.Y);
	}
	static inline Vector2 Normalize(const Vector2& vec)
	{
		float mag = Magnitude(vec);
		if (mag > 0.0f)
		{
			return vec * (1.0f / mag);
		}
		else
		{
			return Vector2(0.0f, 0.0f);
		}
	}

public:
	//////////////	ADD
	inline Vector2 operator+(const Vector2& vec)
	{
		return Vector2(this->X + vec.X, this->Y + vec.Y);
	}
	inline Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(this->X + vec.X, this->Y + vec.Y);
	}
	inline Vector2& operator+=(const Vector2& vec) {
		this->X += vec.X;
		this->Y += vec.Y;
		return *this;
	}
	//////////////	SUBSTRACT
	inline Vector2 operator-(const Vector2& vec)
	{
		return Vector2(this->X - vec.X, this->Y - vec.Y);
	}
	inline Vector2& operator-=(const Vector2& vec) {
		this->X -= vec.X;
		this->Y -= vec.Y;
		return *this;
	}
	//////////////	MULTIPLY
	inline Vector2 operator*(float scalar) const
	{
		return Vector2(this->X * scalar, this->Y * scalar);
	}
	inline Vector2& operator*=(float scalar) {
		this->X *= scalar;
		this->Y *= scalar;
		return *this;
	}
	inline Vector2& operator*=(const Vector2& vec) {
		this->X *= vec.X;
		this->Y *= vec.Y;
		return *this;
	}
	//////////////	DIVIDE
	inline Vector2 operator/(float scalar) const
	{
		return Vector2(this->X / scalar, this->Y / scalar);
	}
	inline Vector2& operator/=(float scalar) {
		this->X /= scalar;
		this->Y /= scalar;
		return *this;
	}
	inline Vector2& operator/=(const Vector2& vec) {
		this->X /= vec.X;
		this->Y /= vec.Y;
		return *this;
	}
	//////////////	COMPARE
	inline bool operator==(const Vector2& vec)
	{
		return (this->X == vec.X && this->Y == vec.Y);
	}


public:
	float X = 0.0f;
	float Y = 0.0f;
};