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

Vector3D Vector3D::operator+(const Vector3D& v1)
{
	return Vector3D(x + v1.x, y + v1.y, z + v1.z);
}
