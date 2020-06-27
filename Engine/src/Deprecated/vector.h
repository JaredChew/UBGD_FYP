#pragma once

#include <math.h>

namespace Math {

	class Vector2 {

	public:
		float x;
		float y;

	public:
		Vector2(const float& x = 0.0f, const float& y = 0.0f);

		//Vector2(const Vector3& vector3);

		~Vector2();

		Vector2 operator + (const Vector2&) const;
		Vector2 operator - (const Vector2&) const;
		Vector2 operator * (const float&) const;
		Vector2 operator / (const float&) const;

		void operator += (const Vector2&);
		void operator -= (const Vector2&);
		void operator *= (const float&);
		void operator /= (const float&);

		void normalise();

		float magnitude() const;

		float dotProduct(const Vector2& b) const;
		Vector2 crossProduct(const Vector2&) const;

	};

	class Vector3 {

	public:
		float x;
		float y;
		float z;

	public:
		Vector3(const float &x = 0.0f, const float& y = 0.0f, const float& z = 0.0f);

		//Vector3(const Vector2& vector2);

		~Vector3();

		Vector3 operator + (const Vector3&) const;
		Vector3 operator - (const Vector3&) const;
		Vector3 operator * (const float&) const;
		Vector3 operator / (const float&) const;

		void operator += (const Vector3&);
		void operator -= (const Vector3&);
		void operator *= (const float&);
		void operator /= (const float&);

		void normalise();

		float magnitude() const;

		float dotProduct(const Vector3& b) const;
		Vector3 crossProduct(const Vector3&) const;

	};

	//class Vector4 { };

	//class Vector5 { };

}