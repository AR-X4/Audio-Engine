#include "VoiceManager.h"

VoiceManager* VoiceManager::poInstance = nullptr;

VoiceManager* VoiceManager::GetInstance()
{
	assert(poInstance != nullptr);
	return poInstance;
}

VoiceManager::VoiceManager(int reserveNum, int reserveGrow)
{
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new AudioVoice();
	assert(this->poNodeCompare != nullptr);

}

VoiceManager::~VoiceManager()
{
	delete this->poNodeCompare;

}

void VoiceManager::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new VoiceManager(reserveNum, reserveGrow);
	}

}

void VoiceManager::Destroy()
{

	//Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	VoiceManager* pMan = VoiceManager::GetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;

}

AudioVoice* VoiceManager::CreateVoice(SoundId IDin)
{
	VoiceManager* pMan = VoiceManager::GetInstance();
	assert(pMan != nullptr);

	AudioVoice* pVoice = (AudioVoice*)pMan->BaseAdd();
	assert(pVoice != nullptr);

	// Create a new one given a wash
	pVoice->Set(IDin);

	return pVoice;
}

//AudioVoice* VoiceManager::FindVoice(SoundId IDin)
//{
//	VoiceManager* pMan = GetInstance();
//	assert(pMan != nullptr);
//
//	pMan->poNodeCompare->SetID(IDin);
//
//	AudioVoice* pVoice = (AudioVoice*)pMan->BaseFind(pMan->poNodeCompare);
//	assert(pVoice != nullptr);
//
//	return pVoice;
//}

void VoiceManager::DestroyVoice(AudioVoice* Nodein)
{
	VoiceManager* pMan = VoiceManager::GetInstance();
	assert(pMan != nullptr);

	assert(Nodein != nullptr);
	pMan->BaseRemove(Nodein);

	Trace::out("Destroyed Voice\n");
}

void VoiceManager::Dump()
{
	VoiceManager* pMan = VoiceManager::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

DLink* VoiceManager::DerivedCreateNode()
{
	DLink* pNode = new AudioVoice();
	assert(pNode != nullptr);

	return pNode;
}

bool VoiceManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	AudioVoice* pDataA = (AudioVoice*)pLinkA;
	AudioVoice* pDataB = (AudioVoice*)pLinkB;

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

void VoiceManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	AudioVoice* pNode = (AudioVoice*)pLink;
	pNode->Wash();
}

void VoiceManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	AudioVoice* pData = (AudioVoice*)pLink;
	pData->Dump();
}

void VoiceManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	AudioVoice* pData = (AudioVoice*)pLink;
	delete pData;
}






