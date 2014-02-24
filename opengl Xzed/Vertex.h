#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "MColor.h"
class VertexData; 

class IVertex
{
public :
	Vector3 Position;
	virtual short GetSize() {return 0 ;};
	virtual short GetOffset(int index) {return 0 ;} //offset of data
	virtual VertexData GetData() ;
	virtual void SetVertex(){}; 
};

class Vertex : public IVertex
{
public:
	Vertex(){}
	Vertex(Vector3 Position );

	void SetVertex();
	void SetVertex(Vector3 Position);
	short GetSize() { return sizeof(Vector3) + sizeof(float) ; }
	short GetOffset(int index) 
	{ return sizeof (float) ; }
	VertexData GetData() ;
	~Vertex()
	{
	
	}
};

class VertexColor : public Vertex
{
public:
	MColor color;

	VertexColor(){}
	VertexColor(Vector3 Position, MColor color) :Vertex(Position)
	{
		this->color = color;
	}
	
	void SetVertex();
	void SetVertex(Vector3 Position, MColor color);
	short GetSize() { return sizeof(Vector3)+sizeof(MColor)+sizeof(float) ; }
	short GetOffset(int index) 
	{ 
		if(index == 0)
			return sizeof (float) ; 
		else
			return 4+sizeof(Vector3);
	} 
	VertexData GetData() ;
	~VertexColor(){};
};

class VertexTexture : public Vertex
{
public: 
	Vector2 TexCoord;
public :
	VertexTexture() {}
	VertexTexture(Vector3 Position, Vector2 TexCoord ) : Vertex(Position)
	{
		this->TexCoord = TexCoord;
	}

	void SetVertex(Vector3 Position, Vector2 TexCoord );
	void SetVertex();
	short GetSize() { return sizeof(Vector3)+sizeof(Vector2) ; } 
	short GetOffset(int index)
	{
		if(index == 0)
			return 4 ;
		if(index == 1)
			return -1 ;
		else
			return 4+sizeof(Vector3) ;
	}
	VertexData GetData() ;
	~VertexTexture()
	{
	}
};

class VertexColorNormal : public VertexColor
{
public:
	Vector3 Normal;
public:
	VertexColorNormal(){}
	VertexColorNormal(Vector3 Position, MColor color, Vector3 Normal) : VertexColor(Position, color)
	{
		this->Normal = Normal;
		this->color = color;
	}
	
	void SetVertex();
	void SetVertex(Vector3 Position, MColor color, Vector3 Normal);
	short GetSize() { return 4+sizeof(Vector3)+sizeof(MColor)+sizeof(Vector3) ; } 
	short GetOffset(int index) 
	{ 
		if(index == 0)
		return 4 ;
		if(index == 1)
			return 4+sizeof(Vector3) ;
		else
			return 4+sizeof(Vector3)+ sizeof(MColor) ;
	}
	VertexData GetData() ;
	~VertexColorNormal()
	{
	}
};

class VertexTextureNormal : public VertexTexture
{
public :
	Vector3 Normal;
	Vector2 TexCoord;
public:
	VertexTextureNormal() {}
	VertexTextureNormal(Vector3 Position, Vector2 TexCoord, Vector3 Normal) : VertexTexture(Position , TexCoord)
	{
		this->Normal = Normal;
		this->TexCoord = TexCoord;
	}

	void SetVertex(Vector3 Position, Vector2 TexCoord, Vector3 Normal);
	void SetVertex();
	short GetSize() { return 4+sizeof(Vector3)+sizeof(Vector2)+sizeof(Vector3) ; } 
	short GetOffset(int index) 
	{ 
		if(index == 0)
		return 4 ;
		if(index == 1)
			return -1 ;
		if(index == 2)
			return 4+sizeof(Vector3) ;
		else
			return 4+sizeof(Vector3)+ sizeof(Vector2) ;
	}
	VertexData GetData() ;
	~VertexTextureNormal()
	{
	}
};