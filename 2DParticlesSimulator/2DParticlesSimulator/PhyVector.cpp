#include "stdafx.h"
#include "PhyVector.h"

PhyVector& PhyVector::operator=(PhyVector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

PhyVector& PhyVector::operator+=(PhyVector u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

PhyVector& PhyVector::operator-=(PhyVector u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

PhyVector& PhyVector::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

PhyVector& PhyVector::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

PhyVector PhyVector::operator-()
{
	return PhyVector(-x, -y, -z);
}

PhyVector PhyVector::operator+(PhyVector u)
{
	return PhyVector(x + u.x, y + u.y, z + u.z);
}

PhyVector  PhyVector::operator-(PhyVector u)
{
	return PhyVector(x - u.x, y - u.y, z - u.z);
}

PhyVector  PhyVector::operator^(PhyVector u)
{
	return PhyVector(y * u.z - z * u.y, -x * u.z + z * u.x, x * u.y - y * u.x);
}

float  PhyVector::operator*(PhyVector u)
{
	return x * u.x + y * u.y + z * u.z;
}

PhyVector operator*(float s, PhyVector& u)
{
	return PhyVector(u.x * s, u.y * s, u.z * s);
}

PhyVector operator*(PhyVector& u, float s)
{
	return PhyVector(u.x * s, u.y * s, u.z * s);
}

PhyVector operator/(PhyVector& u, float s)
{
	return PhyVector(u.x / s, u.y / s, u.z / s);
}

std::ostream& operator<<(std::ostream& out, PhyVector& v)
{
	out << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
	return out;
}