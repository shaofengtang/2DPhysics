#pragma once
#include <math.h>
#include <iostream>

const float tol = 0.0001f;

class PhyVector
{
public:
	float x;
	float y;
	float z;

	PhyVector(float xi = 0.0, float yi = 0.0, float zi = 0.0) : x(xi), y(yi), z(zi) {}
	PhyVector(const PhyVector& phyVector)
	{
		x = phyVector.x;
		y = phyVector.y;
		z = phyVector.z;
	}

	float Magnitude()
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	void Normalize()
	{
		float m = (float)sqrt(x * x + y * y + z * z);
		if (m <= tol) m = 1;
		x /= m;
		y /= m;
		z /= m;

		if (fabsf(x) < tol) x = 0.0f;
		if (fabsf(y) < tol) y = 0.0f;
		if (fabsf(z) < tol) z = 0.0f;
	}

	void Reverse()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	PhyVector& operator=(PhyVector& v);

	PhyVector& operator+=(PhyVector u);
	PhyVector& operator-=(PhyVector u);
	PhyVector& operator*=(float s);
	PhyVector& operator/=(float s);

	PhyVector operator-();
	PhyVector operator+(PhyVector u);
	PhyVector operator-(PhyVector u);
	PhyVector operator^(PhyVector u);
	float operator*(PhyVector u);

	friend PhyVector operator*(float s, PhyVector& u);
	friend PhyVector operator*(PhyVector& u, float s);
	friend PhyVector operator/(PhyVector& u, float s);

	friend std::ostream& operator<<(std::ostream& out, PhyVector& v);
};