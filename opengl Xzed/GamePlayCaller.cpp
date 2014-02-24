#include "_Game1.h"
#include "GamePlayCaller.h"

void GamePlayCaller::CreateGameParts()
	{
		x =new _Game1();
		auto z = x ;
	}
void GamePlayCaller::DeleteGameParts()
	{
		delete x ;
	}