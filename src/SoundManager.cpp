
#include "SoundManager.h"
#include "LoadWaveCommand.h"
#include "CreateSoundCommand.h"
#include "CreateScriptCommand.h"
#include "AddToScriptCommand.h"
#include "StopAllSoundsCommand.h"
#include "AudioThread.h"
#include "TimeEventManager.h"
#include "PrintPriorityCommand.h"
#include <thread>


//---Static---

Handle				SoundManager::table_handle;

SoundManager*		SoundManager::poInstance = nullptr;

SoundManager::SoundManager(int reserveNum, int reserveGrow)
	:bThreadKillSwitch(true), pPriorityHead(nullptr), PriorityTableCount(0)
{
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Sound();
	assert(this->poNodeCompare != nullptr);

	this->pA2G = new CircularData();
	assert(pA2G);

	this->pG2A = new CircularData();
	assert(pG2A);

	this->pF2G = new CircularData();
	assert(pF2G);

	this->pG2F = new CircularData();
	assert(pG2F);

}

SoundManager::~SoundManager()
{
	delete this->poNodeCompare;

	delete this->pA2G;
	delete this->pG2A;

	delete this->pF2G;
	delete this->pG2F;
}

CircularData* SoundManager::GetA2G()
{
	SoundManager* pMan = SoundManager::GetInstance();
	return pMan->pA2G;
}

CircularData* SoundManager::GetG2A()
{
	SoundManager* pMan = SoundManager::GetInstance();
	return pMan->pG2A;
}

bool SoundManager::AddToPriorityList(Sound* pSoundIn)
{
	assert(pSoundIn != nullptr);

	Handle::Lock tablelock(SoundManager::table_handle);
	if (tablelock)
	{
		SoundManager* pMan = SoundManager::GetInstance();
		assert(pMan != nullptr);

		if (pMan->pPriorityHead == nullptr)
		{
			// push to the front
			pMan->pPriorityHead = pSoundIn;
			//--->start time
			pSoundIn->StartTimer();

			pMan->PriorityTableCount++;

			Trace::out("--->NEW PRIORITY HEAD ENTRY\n");
			Trace::out("--->PRIORITY COUNT %d\n\n", pMan->PriorityTableCount);

			assert(pMan->PriorityTableCount <= pMan->PriorityTableSize);
			assert(pMan->pPriorityHead != nullptr);
			return true;
		}
		else {

			Sound* pCurrent = pMan->pPriorityHead;
			while (pCurrent != nullptr) {
				if (pCurrent->GetPriority() >= pSoundIn->GetPriority())
				{
					pSoundIn->SetPriorityPrev(pCurrent->GetPriorityPrev());
					
					if (pCurrent->GetPriorityPrev() == nullptr)
					{
						pMan->pPriorityHead = pSoundIn;
					}
					else
					{
						pCurrent->GetPriorityPrev()->SetPriorityNext(pSoundIn);
					}

					if (pMan->PriorityTableCount < pMan->PriorityTableSize) {
						pSoundIn->SetPriorityNext(pCurrent);
						pCurrent->SetPriorityPrev(pSoundIn);
					
						pMan->PriorityTableCount++;
						Trace::out("--->NEW PRIORITY ENTRY\n");
						Trace::out("--->PRIORITY COUNT %d\n\n", pMan->PriorityTableCount);
					}
					else {
					
						//replace sound
						pSoundIn->SetPriorityNext(pCurrent->GetPriorityNext());

						if (pCurrent->GetPriorityNext() != nullptr) {
							pCurrent->GetPriorityNext()->SetPriorityPrev(pSoundIn);
						}

						//kill sound
						pCurrent->Stop(Time());

						Trace::out("--->REPLACED PRIORITY ENTRY\n");
						Trace::out("--->PRIORITY COUNT %d\n\n", pMan->PriorityTableCount);
					}
					
					pSoundIn->StartTimer();

					assert(pMan->PriorityTableCount <= pMan->PriorityTableSize);
					assert(pMan->pPriorityHead != nullptr);
					return true;
				}
				else if (pCurrent->GetPriorityNext() == nullptr &&
						pMan->PriorityTableCount < pMan->PriorityTableSize) 
				{
					pSoundIn->SetPriorityPrev(pCurrent);
					pCurrent->SetPriorityNext(pSoundIn);

					pSoundIn->StartTimer();

					pMan->PriorityTableCount++;

					Trace::out("--->NEW PRIORITY ENTRY\n");
					Trace::out("--->PRIORITY COUNT %d\n\n", pMan->PriorityTableCount);

					assert(pMan->PriorityTableCount <= pMan->PriorityTableSize);
					assert(pMan->pPriorityHead != nullptr);
					return true;
				}
				pCurrent = pCurrent->GetPriorityNext();
			}
		}
	}
	else
	{
		assert(false);
	}

	
	return false;
}

void SoundManager::StopAllSounds()
{

	Handle::Lock tablelock(SoundManager::table_handle);
	if (tablelock)
	{
		SoundManager* pMan = SoundManager::GetInstance();
		assert(pMan != nullptr);

		Sound* pCurrent = pMan->pPriorityHead;
		Sound* pDead;
		Handle::Status Status;
		while (pCurrent != nullptr) {
		
			pDead = pCurrent;
			pCurrent = pCurrent->GetPriorityNext();
			Status = pDead->Stop(Time());
			assert(Handle::Status::SUCCESS == Status);
		}
	}
	else {
		assert(false);
	}

}

void SoundManager::StopAllSounds(Time TriggTime)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	pMan->SendAudioCommand(new StopAllSoundsCommand(TriggTime));

}

void SoundManager::RemoveFromPriorityList(Sound* pSoundIn)
{
	assert(pSoundIn != nullptr);

	Handle::Lock tablelock(SoundManager::table_handle);
	if (tablelock)
	{
		SoundManager* pMan = SoundManager::GetInstance();
		assert(pMan != nullptr);

		Sound* pCurrent = pMan->pPriorityHead;
		while (pCurrent != nullptr) {

			if (pCurrent == pSoundIn) {

				pMan->PriorityTableCount--;

				if (pSoundIn->GetPriorityNext() != nullptr)
				{
					pSoundIn->GetPriorityNext()->SetPriorityPrev(pSoundIn->GetPriorityPrev());
				}
				if (pSoundIn->GetPriorityPrev() != nullptr) {

					pSoundIn->GetPriorityPrev()->SetPriorityNext(pSoundIn->GetPriorityNext());
				}
				else {

					pMan->pPriorityHead = pSoundIn->GetPriorityNext();
					if (pMan->pPriorityHead != nullptr) {
						pMan->pPriorityHead->SetPriorityPrev(nullptr);
					}
				}
				break;
			}
			pCurrent = pCurrent->GetPriorityNext();
		}
	}
	else {
		assert(false);
	}

}


CircularData* SoundManager::GetF2G()
{
	SoundManager* pMan = SoundManager::GetInstance();
	return pMan->pF2G;
}

CircularData* SoundManager::GetG2F()
{
	SoundManager* pMan = SoundManager::GetInstance();
	return pMan->pG2F;
}

void SoundManager::SendAudioCommand(Message* pMsg)
{
	SoundManager* pMan = SoundManager::GetInstance();

	pMan->pG2A->PushBack(pMsg);
}

void SoundManager::LaunchAudioThread()
{
	SoundManager* pMan = SoundManager::GetInstance();

	//Create Audio Thread
	std::thread AudioThread(Audio_Main, std::ref(pMan->bThreadKillSwitch));
	AudioThread.detach();
}

void SoundManager::KillAudioThread()
{
	SoundManager* pMan = SoundManager::GetInstance();
	pMan->bThreadKillSwitch = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(1));

}

void SoundManager::SendFileCommand(Message* pMsg)
{
	SoundManager* pMan = SoundManager::GetInstance();

	pMan->pG2F->PushBack(pMsg);
}

void SoundManager::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new SoundManager(reserveNum, reserveGrow);
		poInstance->LaunchAudioThread();
	}
}

void SoundManager::Destroy()
{

	// Get the instance
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	pMan->KillAudioThread();

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}

void SoundManager::Update()
{
	SoundManager* pMan = SoundManager::GetInstance();
	Message* pMsg;

	if (pMan->GetA2G()->PopFront(pMsg)) {
		pMsg->Execute();
		delete pMsg;
	}
}

SoundManager* SoundManager::GetInstance()
{
	assert(poInstance != nullptr);
	return poInstance;
}

Sound* SoundManager::CreateSound(SoundId IDin, UserCallback* Callback, int SoundPriority)
{

	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	Sound* pSound = (Sound*)pMan->BaseAdd();
	assert(pSound != nullptr);

	// Create a new one given a wash
	pSound->Set(IDin, SoundPriority);

	pMan->SendAudioCommand(new CreateSoundCommand(pSound, Callback));

	return pSound;
}

void SoundManager::DestroySound(Sound* Nodein)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	assert(Nodein != nullptr);

	pMan->RemoveFromPriorityList(Nodein);
	/*if (Nodein == pMan->pPriorityHead) {
		pMan->pPriorityHead = nullptr;
	}
	pMan->PriorityTableCount--;*/

	pMan->BaseRemove(Nodein);

	Trace::out("Destroyed Sound\n");
}

Sound* SoundManager::FindSound(SoundId IDin)
{
	SoundManager* pSoundMan = SoundManager::GetInstance();
	assert(pSoundMan != nullptr);

	pSoundMan->poNodeCompare->Set(IDin);

	Sound* pSnd = (Sound*)pSoundMan->BaseFind(pSoundMan->poNodeCompare);
	assert(pSnd != nullptr);

	return pSnd;
}

void SoundManager::Dump()
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

void SoundManager::PrintPriority(Time TriggTime)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan);

	Message* pMsg = new PrintPriorityCommand(TriggTime);

	SoundManager::SendAudioCommand(pMsg);
}

void SoundManager::DumpPriorityTable()
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan != nullptr);
	Handle::Lock tablelock(SoundManager::table_handle);
	if (tablelock)
	{
		Trace::out("---------------------------------\n");
		Trace::out(" Sound Priority Table \n");
		Trace::out("---------------------------------\n");

		Sound* pCurrent = pMan->pPriorityHead;
		while (pCurrent != nullptr) {

			int prev = 0;
			int next = 0;
			if (pCurrent->GetPriorityPrev() != nullptr) {
				prev = pCurrent->GetPriorityPrev()->GetHandleID();
			}
			if (pCurrent->GetPriorityNext() != nullptr) {
				next = pCurrent->GetPriorityNext()->GetHandleID();
			}

			Trace::out("handle: 0x%x SndID: %d priority:%4d  time: %d ms  Prev: 0x%x  Next: 0x%x\n",
				pCurrent->GetHandleID(),
				pCurrent->GetID(),
				pCurrent->GetPriority(),
				pCurrent->GetPlayTime(),
				prev,
				next);

			pCurrent = pCurrent->GetPriorityNext();
		}
	}
	else {
		assert(false);
	}

	Trace::out("---------------------------------\n");
}

void SoundManager::LoadWave(const char* const FileNameIn, SoundId Idin, FileCallback* pFileCallback)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan);


	Message* pMsg = new LoadWaveCommand(FileNameIn, Idin, pFileCallback);

	SoundManager::SendFileCommand(pMsg);

}

void SoundManager::CreateScript(SoundId Idin)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan);

	Message* pMsg = new CreateScriptCommand(Idin);

	SoundManager::SendAudioCommand(pMsg);
}

void SoundManager::AddToScriptFront(SoundId ScriptID, SoundId BufferID)
{
	SoundManager* pMan = SoundManager::GetInstance();
	assert(pMan);

	Message* pMsg = new AddToScriptCommand(ScriptID, BufferID);

	SoundManager::SendAudioCommand(pMsg);
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* SoundManager::DerivedCreateNode()
{
	DLink* pNode = new Sound();
	assert(pNode != nullptr);

	return pNode;
}

bool SoundManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Sound* pDataA = (Sound*)pLinkA;
	Sound* pDataB = (Sound*)pLinkB;

	bool status = false;
	//SoundId A_id;
	//SoundId B_id;

	//pDataA->GetID(A_id);
	//pDataB->GetID(B_id);

	if (pDataA->GetID() == pDataB->GetID())
	{
		status = true;
	}

	return status;
}

void SoundManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Sound* pNode = (Sound*)pLink;
	pNode->Wash();
}

void SoundManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Sound* pData = (Sound*)pLink;
	pData->Dump();
}

void SoundManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Sound* pData = (Sound*)pLink;
	delete pData;
}


// End of File 
