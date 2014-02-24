#pragma once
#include <vector>
#include "Vertex.h"
#include "Vector3.h"
#include "Matrix.h"
using namespace std ;
class Shape 
{
public :
	Vector3 Position ;
	Shape(){Position = Vector3(0) ;} 
	virtual void Transform(Matrix Transformation) = 0;
	virtual void Draw() = 0 ;
	 void Debug() ;
};

class VShape : public Shape  
{
public :
	//IVertex** vertices;//arr of pointers
	vector<IVertex*> vertices ;
	int numOfVertices ;
	VShape(int numOfVertices) {  this->numOfVertices = numOfVertices ; vertices.resize(numOfVertices) ;} 
	void Transform(Matrix Transformation);
	void Debug();
	~VShape(){
		for(int i = 0 ; i < vertices.size() ; ++i)
		delete  vertices[i] ; 
		vertices.clear();
	} 
	
};


class Line : public VShape 
{
public :
	Line() : VShape(0) {}

	Line(IVertex *V1, IVertex *V2):VShape(2)
	{
		vertices[0] = V1;
		vertices[1] = V2;
	}
	
	void Draw();
};

class Triangle:public VShape
{
public:
	
	Triangle():VShape(0) {}
	
	Triangle(IVertex *V1, IVertex *V2, IVertex *V3):VShape(3)
	{
		vertices[0] = V1;
		vertices[1] = V2;
		vertices[2] = V3;
	}
	
	void Draw();
};


class TShape : public Shape
{
public :
	vector<Triangle*> Triangles ;
	int NumOfTriangles ;
	TShape(int NumOfTriangles) { this->NumOfTriangles = NumOfTriangles ; Triangles.resize(NumOfTriangles) ; } 
	void Draw() ;
	void DrawRange(int start , int end) ;
	void Debug() ;
	void DebugRange(int start , int end) ;
	~TShape() 
	{ 
		for(int i = 0 ; i < Triangles.size() ; ++i)
			delete Triangles[i]  ; 
	} 
private :
	void DebugSingleTriangle(int Index) ;
	void DrawSingleTriagle(int Index) ;
};

class Quad : public TShape
{
public :
	Quad():TShape(0){}
	Quad(IVertex*vertices [4]) : TShape(2)
	{
		Triangles[0] = new Triangle(vertices[0] , vertices[1] , vertices[2]); // UR
		Triangles[1] = new Triangle(vertices[1] ,vertices[2] , vertices[3]); // DL
	}
	Quad(IVertex *UR, IVertex *UL, IVertex *DR , IVertex *DL): TShape(2)
	{
		Triangles[0] = new Triangle(UR , UL , DR);
		Triangles[1] = new Triangle(UL ,DR , DL);
	}
	

};
