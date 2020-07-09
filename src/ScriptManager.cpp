#include "ScriptManager.h"

ScriptManager* ScriptManager::poInstance = nullptr;

ScriptManager::ScriptManager(int reserveNum, int reserveGrow)
{
	this->BaseInitialize(reserveNum, reserveGrow);

	this->poNodeCompare = new AudioScript();
	assert(this->poNodeCompare != nullptr);

}

ScriptManager::~ScriptManager()
{
	delete this->poNodeCompare;
}

void ScriptManager::Create(int reserveNum, int reserveGrow)
{
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new ScriptManager(reserveNum, reserveGrow);
	}
}

void ScriptManager::Destroy()
{
	//Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	ScriptManager* pMan = ScriptManager::GetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}

AudioScript* ScriptManager::CreateScript(SoundId IDin)
{
	ScriptManager* pMan = GetInstance();
	assert(pMan != nullptr);

	AudioScript* pScript = (AudioScript*)pMan->BaseAdd();
	assert(pScript != nullptr);

	// Create a new one given a wash
	pScript->Set(IDin);

	return pScript;
}

AudioScript* ScriptManager::FindScript(SoundId IDin)
{
	ScriptManager* pMan = GetInstance();
	assert(pMan != nullptr);

	pMan->poNodeCompare->Set(IDin);

	AudioScript* pScript = (AudioScript*)pMan->BaseFind(pMan->poNodeCompare);
	assert(pScript != nullptr);

	return pScript;
}

void ScriptManager::DestroyScript(AudioScript* Nodein)
{
	ScriptManager* pMan = ScriptManager::GetInstance();
	assert(pMan != nullptr);

	assert(Nodein != nullptr);
	pMan->BaseRemove(Nodein);
}

void ScriptManager::Dump()
{
	ScriptManager* pMan = ScriptManager::GetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

DLink* ScriptManager::DerivedCreateNode()
{
	DLink* pNode = new AudioScript();
	assert(pNode != nullptr);

	return pNode;
}

bool ScriptManager::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	AudioScript* pDataA = (AudioScript*)pLinkA;
	AudioScript* pDataB = (AudioScript*)pLinkB;

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

void ScriptManager::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	AudioScript* pNode = (AudioScript*)pLink;
	pNode->Wash();
}

void ScriptManager::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	AudioScript* pData = (AudioScript*)pLink;
	pData->Dump();
}

void ScriptManager::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	AudioScript* pData = (AudioScript*)pLink;
	delete pData;
}

ScriptManager* ScriptManager::GetInstance()
{
	assert(poInstance != nullptr);
	return poInstance;
}
