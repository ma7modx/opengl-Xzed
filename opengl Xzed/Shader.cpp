#include "Shader.h"
#include "GameController.h"
#include "GraphicsManager.h"
Shader::Shader(string name , const char *vertex_file_path,const char *fragment_file_path) :Resource(name , this)
	{
		ID = GameController::GetGameController()->Graphicsmanager->LoadShader(vertex_file_path , fragment_file_path) ;
	}
void Shader::Active()
{
	GameController::GetGameController()->Graphicsmanager->ActiveShader(ID);
}