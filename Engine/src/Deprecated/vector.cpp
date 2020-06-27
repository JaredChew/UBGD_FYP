#include "vector.h"

using namespace Math;

Vector2::Vector2(const float& x, const float& y) {

	this->x = x;
	this->y = y;

}

Vector2::~Vector2() { }

Vector2 Vector2::operator + (const Vector2& passedValue) const {

	return Vector2(x + passedValue.x, y + passedValue.y);

}

Vector2 Vector2::operator - (const Vector2& passedValue) const {

	return Vector2(x - passedValue.x, y - passedValue.y);

}

Vector2 Vector2::operator * (const float& passedValue) const {

	return Vector2(x * passedValue, y * passedValue);

}

Vector2 Vector2::operator / (const float& passedValue) const {

	return Vector2(x / passedValue, y / passedValue);

}

void Vector2::operator += (const Vector2& passedValue) {

	x += passedValue.x;
	y += passedValue.y;

}

void Vector2::operator -= (const Vector2& passedValue) {

	x -= passedValue.x;
	y -= passedValue.y;

}

void Vector2::operator *= (const float& passedValue) {

	x *= passedValue;
	y *= passedValue;

}

void Vector2::operator /= (const float& passedValue) {

	x /= passedValue;
	y /= passedValue;

}

float Vector2::magnitude() const {

	return (float)sqrt((x * x) + (y * y));

}

void Vector2::normalise() {

	float size = magnitude();

	x /= magnitude();
	y /= magnitude();

}

float Vector2::dotProduct(const Vector2& passedValue) const {

	return ((this->x * passedValue.x) + (this->y * passedValue.y));

}

Vector2 Vector2::crossProduct(const Vector2& passedValue) const {

	return Vector2((x * passedValue.y), (y * passedValue.x));

}

/*	######	Vector2	######	*/

Vector3::Vector3(const float& x, const float& y, const float& z) {

	this->x = x;
	this->y = y;
	this->z = z;

}

Vector3::~Vector3() { }

Vector3 Vector3::operator + (const Vector3& passedValue) const {

	return Vector3(x + passedValue.x, y + passedValue.y, z + passedValue.z);

}

Vector3 Vector3::operator - (const Vector3& passedValue) const {

	return Vector3(x - passedValue.x, y - passedValue.y, z - passedValue.z);

}

Vector3 Vector3::operator * (const float& passedValue) const {

	return Vector3(x * passedValue, y * passedValue, z * passedValue);

}

Vector3 Vector3::operator / (const float& passedValue) const {

	return Vector3(x / passedValue, y / passedValue, z / passedValue);

}

void Vector3::operator += (const Vector3& passedValue) {

	x += passedValue.x;
	y += passedValue.y;
	z += passedValue.z;

}

void Vector3::operator -= (const Vector3& passedValue) {

	x -= passedValue.x;
	y -= passedValue.y;
	z -= passedValue.z;

}

void Vector3::operator *= (const float& passedValue) {

	x* passedValue;
	y* passedValue;
	z* passedValue;

}

void Vector3::operator /= (const float& passedValue) {

	x /= passedValue;
	y /= passedValue;
	z /= passedValue;

}

float Vector3::magnitude() const {

	return (float)sqrt((x * x) + (y * y) + (z * z));

}

void Vector3::normalise() {

	float size = magnitude();

	x /= size;
	y /= size;
	z /= size;

}

float Vector3::dotProduct(const Vector3& passedValue) const {

	return ((this->x * passedValue.x) + (this->y * passedValue.y) + (this->z * passedValue.z));

}

Vector3 Vector3::crossProduct(const Vector3& passedValue) const {

	return Vector3((y * passedValue.z) - (z * passedValue.y),
		(z * passedValue.x) - (x * passedValue.z),
		(x * passedValue.y) - (y * passedValue.x));

}