#pragma once

#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <math.h>
#include <iostream>

class Vector2D
{
public:
	Vector2D()
	{
		X = 0;
		Y = 0;
	}

	Vector2D(float x, float y) : X(x), Y(y){};
	float getX() {return X;}
	float getY() {return Y;}

	void setX(float x) { X = x;}
	void setY(float y) { Y = y;}

	float length() {return sqrt(X*X + Y*Y);}

	Vector2D & operator+(const Vector2D& v2) const
	{
		return Vector2D(X + v2.X, Y + v2.Y);
	}

	Vector2D & operator-(const Vector2D& v2) const
	{
		return Vector2D(X - v2.X, Y - v2.Y);
	}

	Vector2D operator*(float scalar)
	{
		return Vector2D(X * scalar, Y * scalar);
	}

	Vector2D operator/(float scalar)
	{
		return Vector2D(X / scalar, Y / scalar);
	}

	Vector2D operator*=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	Vector2D operator/=(float scalar)
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.X += v2.X;
		v1.Y += v2.Y;

		return v1;
	}

	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.X -= v2.X;
		v1.Y -= v2.Y;

		return v1;
	}

	void printVector()
	{
		printf("(%d,", X);
		printf("%d)\n",Y);
	}

	~Vector2D(void){}

private:
	float X, Y;
};

#endif

