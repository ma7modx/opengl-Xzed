#pragma once
#define PI 3.1415926536f
#define ToRadians(x) (float)(((x) * PI/ 180.0f))
#include <iostream>

using namespace std ;

class Vector3 ;
class Matrix
{
public:
	float Mtrx[4][4];

public:
	Matrix(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);

	Matrix();

	static Matrix Identity();

	void Show();


#pragma region Operators
	Matrix operator*(Matrix mtrx1);
	Matrix operator*(float num);
	float operator() (int i, int j) const;
	float& operator() (int i, int j);

	Matrix Translation(const Vector3 translation);

	Matrix Rotation( Vector3 eulerAngles);

	Matrix Scale( Vector3 scale);

	void ApplyOn(Vector3& vec);

	static void ApplyOn(Matrix mat , Vector3& vec);

#pragma endregion

	//~Matrix(){}
	// look at 
	// projection 
	//prespectivefield
};