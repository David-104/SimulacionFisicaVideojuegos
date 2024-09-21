#include "Vector3D.h"
#include <cmath>

float Vector3D::Module()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector3D::Normalize()
{
	float module = Module();
	x = x / module;
	y = y / module;
	z = z / module;
}

Vector3D Vector3D::Normalized()
{
	float module = Module();
	return Vector3D(x/module, y/module, z/module);
}

ostream& operator<<(ostream& os, const Vector3D& v)
{
	os << "(" << v.x << "," << v.y << "," << v.z << ")";
	return os;
}

Vector3D Vector3D::operator+(const Vector3D& v1)
{
	return Vector3D(x + v1.x, y + v1.y, z + v1.z);
}

Vector3D Vector3D::operator-(const Vector3D& v1)
{
	return Vector3D(x - v1.x, y - v1.y, z - v1.z);
}

Vector3D Vector3D::operator*(const Vector3D& v1)
{
	return Vector3D(y*v1.z - z*v1.y, z*v1.x - x*v1.z, x*v1.y - y*v1.x);
}

Vector3D Vector3D::operator*(float scalar)
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

bool Vector3D::operator==(const Vector3D& v1)
{
	return (x == v1.x && y == v1.y && z == v1.z);
}
