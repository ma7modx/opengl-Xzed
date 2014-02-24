#pragma once 
#include "Shapes.h"
#include <vector>
using namespace std ;

class GeometricModel : public TShape
{
public :
	GeometricModel():TShape(0){}
	GeometricModel(vector<Triangle*> Triangles) : TShape(Triangles.size()) 
	{
	for(int i = 0 ; i < Triangles.size() ; ++i)
			this->Triangles[i] = Triangles[i]; 
	}
};