#pragma once
#include "Vector3.h"
class Vector4 : public Vector3
{
public:
	float W ; // W = 0 || 1
public:
	Vector4(){W = 1;}
	Vector4(float X, float Y, float Z, float W) : Vector3(X, Y, Z)
	{
		this->W = W;
	}


	float operator [] (int i) const
	{
		if (i == 0) return X;
		if (i == 1) return Y;
		if (i == 2) return Z;
		if (i == 3) return W;
	}
	float& operator [](int i) //'ll debug it
	{
		if (i == 0) return X;
		if (i == 1) return Y;
		if (i == 2) return Z;
		if (i == 3) return W;
	}
	~Vector4(){};
};

