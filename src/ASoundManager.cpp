#include "ASoundManager.h"
#include "VoiceManager.h"
#include "PlaylistManager.h"
#include "SoundManager.h"

ASoundManager* ASoundManager::poInstance = nullptr;

ASoundManager::ASoundManager(int reserveNum, int reserveGrow)
{
	
	this->BaseInitialize(reserveNum, reserveGrow);

}

ASoundManager::~ASoundManager()
{
	
	
}

void ASoundManager::Create(int reserveNum, int reserveGrow)
{

	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new ASoundManager(reserveNum, reserveGrow);
	}

}

void ASoundManager::Destroy()
{

	//Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	ASoundManager* pMan = ASoundManager::GetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}

ASoundManager* ASoundManager::GetInstance()
{
	assert(poInstance != nullptr);
	return poInstance;
}

ASound* ASoundManager::CreateASound(Sound* pSoundIn)
{
	ASoundManager* pMan = ASoundManager::GetInstance();
	assert(pMan != nullptr);

	ASound* pASound = (ASound*)pMan->BaseAdd();
	assert(pASound != nullptr);

	assert(pSoundIn != nullptr);
	pASound->Set(pSoundIn);

	return pASound;
}

void ASoundManager::DestroyASound(ASound* Nodein)
{
	ASoundManager* pMan = ASoundManager::GetInstance();
	assert(pMan != nullptr);

	assert(Nodein != nullptr);
	pMan->BaseRemove(Nodein);

	Trace::out("Destroyed ASound\n\n");
}

//ASound* ASoundManager::FindASound(SoundId IDin)
//{
//	ASoundManager* pASoundMan = GetInstance();
//	assert(pASoundMan != nullptr);
//
//	pASoundMan->poNodeCompare->SetID(IDin);
//
//	ASound* pSnd = (ASound*)pASoundMan->BaseFind(pASoundMan->poNodeCompare);
//	assert(pSnd != nullptr);
//
//	return pSnd;
//}

void ASoundManager::Dump()
{
	ASoundManager* pMan = ASoundManager::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

void ASoundManager::Update()
{
	ASoundManager* pASoundMan = GetInstance();
	assert(pASoundMan != nullptr);

	//Walk Active list of ASounds and call Update()
	ASound* pCurrent = (ASound*)pASoundMan->BaseGetActiveHead();
	while (pCurrent != nullptr) {

		ASound* tmp = pCurrent;
		pCurrent = (ASound*)pCurrent->pNext;

		if (tmp->Update()) {
			//Sound is done playing...

			UserCallback* pCallback = tmp->GetCallback();

			//Send Callback
			if (pCallback != nullptr)
			{
				SoundManager::GetA2G()->PushBack(pCallback);
				
				//Sleep(2000);//change this
			}
			else {

				//Destroy voice
				VoiceManager::DestroyVoice(tmp->GetPlaylist()->GetVoice());
				//Destroy playlist
				PlaylistManager::DestroyPlaylist(tmp->GetPlaylist());
				//destroy sound
				SoundManager::DestroySound(tmp->GetSound());
				//Destroy ASound
				pASoundMan->DestroyASound(tmp);
			}
			
		}
	}
}

DLink* ASoundManager::DerivedCreateNode()
{
	DLink* pNode = new ASound();
	assert(pNode != nullptr);

	return pNode;
}

bool ASoundManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	ASound* pDataA = (ASound*)pLinkA;
	ASound* pDataB = (ASound*)pLinkB;

	bool status = false;
	SoundId A_id;
	SoundId B_id;

	pDataA->GetID(A_id);
	pDataB->GetID(B_id);

	if (A_id == B_id)
	{
		status = true;
	}

	return status;
}

void ASoundManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	ASound* pNode = (ASound*)pLink;
	pNode->Wash();
}

void ASoundManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	ASound* pData = (ASound*)pLink;
	pData->Dump();
}

void ASoundManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	ASound* pData = (ASound*)pLink;
	delete pData;
}


