#include "Resource.h"
#include "GameController.h"
#include "ResourceManager.h"
Resource::Resource(string name , Resource* Data)
{
	GameController::GetGameController()->Resourcemanager->Register(name  , Data) ;
}