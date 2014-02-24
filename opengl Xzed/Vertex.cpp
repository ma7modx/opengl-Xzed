#pragma once
#include "Vertex.h"
#include "GameController.h"
#include "GraphicsManager.h"
#include "GraphicsHelpers.h"

VertexData IVertex::GetData()
{
	return VertexData::VERTEX;
}
Vertex::Vertex(Vector3 Position )
	{
		this->Position = Position ;
	}
void Vertex::SetVertex(Vector3 Position)
{
	this->Position = Position ;
	GameController::GetGameController()->Graphicsmanager->SetVertexPosition(Position);
}
void Vertex::SetVertex()
{
	SetVertex(Position) ;
}
VertexData Vertex::GetData() 
	{return VertexData::VERTEX ;}
///
void VertexColor::SetVertex(Vector3 Position, MColor color)
{
	this->color = color ;
	GameController::GetGameController()->Graphicsmanager->SetVertexColor(color);
	Vertex::SetVertex(Position) ;
	
}
void VertexColor::SetVertex()
{
	SetVertex(Position,  color);
}
VertexData VertexColor::GetData() 
	{return VertexData::VERTEX | VertexData::COLOR;}
	
///
void VertexTexture::SetVertex(Vector3 Position, Vector2 TexCoord )
{
	this->TexCoord = TexCoord ;
	GameController::GetGameController()->Graphicsmanager->SetVertexTexCoord(TexCoord) ;
	Vertex::SetVertex(Position) ;
	
}
void VertexTexture::SetVertex()
{
	SetVertex(Position , TexCoord) ;
}
VertexData VertexTexture::GetData() 
	{return VertexData::VERTEX | VertexData::TEXTURE ;}
	
///
VertexData VertexColorNormal::GetData() 
	{return VertexData::VERTEX | VertexData::COLOR | VertexData::NORMAL ;}
///
void VertexTextureNormal::SetVertex(Vector3 Position, Vector2 TexCoord, Vector3 Normal)
{
	this->Normal = Normal ;
	GameController::GetGameController()->Graphicsmanager->SetVertexNormal(Normal) ;
	VertexTexture::SetVertex(Position , TexCoord);
	
}
void VertexTextureNormal::SetVertex()
{
	SetVertex(Position , TexCoord , Normal);
}
VertexData VertexTextureNormal::GetData() 
	{return VertexData::VERTEX | VertexData::TEXTURE | VertexData::NORMAL ;}
	