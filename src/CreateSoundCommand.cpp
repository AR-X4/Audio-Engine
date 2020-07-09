#include "CreateSoundCommand.h"
#include "ASoundManager.h"



CreateSoundCommand::CreateSoundCommand(Sound* pSoundIn, UserCallback* pCallbackIn)
	:pSound(pSoundIn), pCallback(pCallbackIn)
{
}

CreateSoundCommand::~CreateSoundCommand() {}

void CreateSoundCommand::Execute()
{

	//Create corresponding ASound
	ASound* pASnd = ASoundManager::CreateASound(this->pSound);
	this->pSound->SetASound(pASnd);
	Trace::out("Created ASound\n\n");

	//Assocaite Callback
	if (this->pCallback != nullptr)
	{
		pCallback->Set(this->pSound);
		pASnd->SetCallBack(this->pCallback);
	}
	
	//Assocaite corresponding Playlist... which associates corresponding script and voice
	pASnd->AssociatePlaylist();
	
}
