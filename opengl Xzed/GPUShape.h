#pragma once
#include "Shapes.h"
#include "GraphicsManager.h"
#include "ModelHelpers.h"

class GPUShape :public Shape
{
public :
	GPUShape(int numOfVerices , float pos [] , int numOfVertex);
	GPUShape(int numOfVerices , IVertex vertex[]);
	void Edit(int start , int end , float arr[]){}
	void Transform(Matrix Transformation){}
	void Draw(){Draw(Shapes::TRIANGLE) ;}
	void Debug(){Draw(Shapes::LINE);} 
	void Draw(Shapes shape) ;
	unsigned int GetNumOfVertices() { return numOfVertices ; }
	int GetBufferID() { return BufID ; } 
private :
	VertexData Mode;
	int vertexSize ;
	int numOfVertices;
	unsigned int BufID ; 
	void* Offsets[] ;
	void DetermineOffset(IVertex *v);
	

};