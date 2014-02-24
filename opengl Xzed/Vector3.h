#pragma once

class Matrix ;

class Vector3
{
public:
	float X, Y, Z;
	
	static Vector3 ZERO ;

	Vector3();
	Vector3(float val);
	Vector3(float X, float Y, float Z);

#pragma region Operators
	Vector3 operator +(Vector3 vec)
	{
		Vector3 res;
		res.X = X + vec.X;
		res.Y = Y + vec.Y;
		res.Z = Z + vec.Z;
		return res;
	}
	
	Vector3 operator *(float val);
	Vector3 operator /(float val);
	float operator *(Vector3 vec); // dot
	Vector3 operator ^(Vector3 vec); // cross product
	Vector3 operator*(Matrix mat);
	float operator [] (int i) const;
	float& operator [](int i); //'ll debug it
	
	float Magnitude();
	Vector3 LERP(Vector3 pos1 , Vector3 pos2 , float Gamma);//linear interpolation .. to find mid point between 2 pts
	float Dot( Vector3 v);
	Vector3 Cross( Vector3 v) ;
	Vector3 Normalized();
#pragma endregion;

	~Vector3(){};
};
