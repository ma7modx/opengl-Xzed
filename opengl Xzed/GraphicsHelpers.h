#pragma once
class VertexData 
{
public :
	int Mode ;
	VertexData() {}
	VertexData(int Mode) { this->Mode = Mode ; } 
static int VERTEX  , COLOR , NORMAL , TEXTURE ;
} ;

enum GPUDrawMode { STATIC  , DYNAMIC  , STREAM } ;
enum Shapes { TRIANGLE , LINE } ;
