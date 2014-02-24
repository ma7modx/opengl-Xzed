#include "GameController.h"
#include "GameplayManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "MemoryManager.h"
#include "GamePlayCaller.h"
#include <iostream>

GameController* GameController::Controller = NULL;

GameController::GameController(GraphicsManager* Graphicsmanager , MemoryManager* Memorymanager = new MemoryManager(1000))
	{
		Controller = this ;

		this->Memorymanager = Memorymanager ;
	
		(this->Graphicsmanager) = (Graphicsmanager) ;
		
		Graphicsmanager->Start();
		
		Resourcemanager = new ResourceManager() ;

		GamePlaymanager = new GamePlayManager() ;

		Graphicsmanager->LOOP();
	}
void GameController::GameUpdateLOOP()
	{
		int Exit = GamePlaymanager->GameUpdateLOOP() ;
		
		if(Exit == -1)
			GameEnd();
	}
void GameController::GameDrawLOOP()
	{
	//	std::cout <<"ay";
		// scene
		 GamePlaymanager->GameDrawLOOP() ;
	}
void GameController::GameEnd()
	{
		GamePlaymanager->GetGamePlay()->DeleteGameParts();
	}

  