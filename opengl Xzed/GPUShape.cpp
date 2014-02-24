#include "GPUShape.h"
#include "GameController.h"

GPUShape::GPUShape(int numOfVerices , float pos[] , int vertexSize = sizeof (float)*3)
{
	this->numOfVertices = numOfVerices ;
	this->vertexSize = vertexSize ;

	Mode = VertexData::VERTEX ; 
	GameController::GetGameController()->Graphicsmanager->StoreInBuffer(BufID ,pos  , numOfVerices*vertexSize, GPUDrawMode::STATIC); 
}
GPUShape::GPUShape(int numOfVerices , IVertex vertex[])
{
	this->numOfVertices = numOfVerices ;
	cout <<"Size Of Vertex : "<<vertex[0].GetSize()<<endl ;
	DetermineOffset(&vertex[0]) ;
	vertexSize =vertex[0].GetSize() ;
	Mode = vertex[0].GetData();	

	GameController::GetGameController()->Graphicsmanager->StoreInBuffer(BufID , vertex  ,numOfVerices*vertex[0].GetSize(), GPUDrawMode::STATIC);
}
void GPUShape::DetermineOffset(IVertex* v)
{
	for(int i = 0 ; i<10 ; ++i)
	{
		if(v->GetOffset(i) == -1)
			continue ;
		if(v->GetOffset(i) >= 0 )
			Offsets[i] = (void*)v->GetOffset(i);
		else 
			break ;
		if(v->GetOffset(i) == v->GetOffset(i+1))
			break ;
	}
}
void GPUShape::Draw(Shapes shapes = Shapes::TRIANGLE)
{
	GameController::GetGameController()->Graphicsmanager->BindBuffer(BufID) ;
	GameController::GetGameController()->Graphicsmanager->GPUModeActive(Mode) ;

	GameController::GetGameController()->Graphicsmanager->GPUModeDraw(numOfVertices,vertexSize, Offsets , Mode, shapes) ;

	GameController::GetGameController()->Graphicsmanager->GPUModeDeactive(Mode) ;
	GameController::GetGameController()->Graphicsmanager->BindBuffer(0) ;
}
