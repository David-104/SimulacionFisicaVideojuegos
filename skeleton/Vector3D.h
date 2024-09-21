#pragma once
#include <iostream>
using namespace std;
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
	Vector3D Normalized();
	friend ostream& operator<<(ostream& os, const Vector3D& v);
	Vector3D operator+(const Vector3D& v1);
	Vector3D operator-(const Vector3D& v1);
	Vector3D operator*(const Vector3D& v1);
	Vector3D operator*(float scalar);
	bool operator==(const Vector3D& v1);
};

