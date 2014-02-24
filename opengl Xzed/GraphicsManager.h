#pragma once
#include <string>
#include "Vector3.h"
#include "Window.h"
#include "GraphicsHelpers.h"

class GraphicsManager
{
public:
	Window widnow ;
	int iArgc; char** cppArgv ;

public :
	GraphicsManager(Window window){this->widnow = window ;}
	virtual void Start() = 0;
	virtual void LOOP() = 0;
	virtual void SetVertexPosition(Vector3 pos) = 0;
	virtual void SetVertexColor(MColor color) = 0;
	virtual void SetVertexTexCoord(Vector2 texcoord) = 0;
	virtual void SetVertexNormal(Vector3 Normal) = 0;
	virtual void AllocateTexture(unsigned int *TexID) = 0;
	virtual void BindTexture(int TexID) = 0 ;
	virtual void AssignTexture(int width,int height,int dipth , void *Pixels) = 0;
	virtual void BeginTriangle() = 0;
	virtual void EndTriangle() =  0;
	virtual void BeginLine() = 0;
	virtual void EndLine() =  0;
	virtual unsigned int LoadShader(const char *vertex_file_path,const char *fragment_file_path)=0;
	virtual void ActiveShader(unsigned int ID) = 0;
	virtual void GPUModeActive(VertexData Mode) = 0;
	virtual	void GPUModeDeactive(VertexData Mode) = 0;
	virtual void GPUModeDraw(int numOfVertices , int strideBetweenVertices , void* pointerToTheBeginingOfData[] , VertexData mode , Shapes shape ) = 0;
	virtual void StoreInBuffer (unsigned int& BufID , void* data , int sizeOfarray , GPUDrawMode Mode) = 0;//allocate and bind and save data
	virtual void BindBuffer(unsigned int BufID)= 0 ;
//	virtual void AllocateData() = 0 ;
};