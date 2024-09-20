#pragma once
class Vector3D
{
	float x;
	float y;
	float z;
public:
	Vector3D(float x, float y, float z) : x(x), y(y), z(z){}
	Vector3D() : x(0.0), y(0.0), z(0.0){}
	float Module();
	void Normalize();
	Vector3D operator+(const Vector3D& v1);

};

