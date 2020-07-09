#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "CircularData.h"
#include "Manager.h"
#include "Sound.h"
#include "Message.h"
#include "UserCallback.h"
#include "FileCallback.h"


class SoundManager : public Manager
{

private:
	// Defaults
	SoundManager(int reserveNum = 3, int reserveGrow = 1);
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator = (const SoundManager&) = delete;
	SoundManager() = delete;
	~SoundManager();

	static void LaunchAudioThread();
	static void KillAudioThread();
	static void SendFileCommand(Message* pMsg);

public:
	// Public methods:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static void Update();

	static void SendAudioCommand(Message* pMsg);
	

	static Sound* CreateSound(SoundId IDin, UserCallback* Callback = nullptr, int SoundPriority = 0);
	static Sound* FindSound(SoundId IDin);
	static void DestroySound(Sound* Nodein);

	static void Dump();
	static void PrintPriority(Time TriggTime);
	static void DumpPriorityTable();

	static void LoadWave(const char* const FileNameIn, SoundId Idin, FileCallback* pFileCallback = nullptr);
	static void CreateScript(SoundId Idin);
	static void AddToScriptFront(SoundId ScriptID, SoundId BufferID);
	
	static CircularData* GetF2G();
	static CircularData* GetG2F();
	static CircularData* GetA2G();
	static CircularData* GetG2A();

	static bool AddToPriorityList(Sound* pSoundIn);
	static void StopAllSounds();
	static void StopAllSounds(Time TriggTime);

private:
	static void RemoveFromPriorityList(Sound* pSoundIn);
	

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	
	static SoundManager* GetInstance();


	//---DATA---
	static SoundManager* poInstance;
	Sound* poNodeCompare;

	CircularData* pA2G;  // Audio to Game
	CircularData* pG2A; // Game to Audio

	CircularData* pF2G;  // File to Game
	CircularData* pG2F; // Game to File

	bool bThreadKillSwitch;

	Sound* pPriorityHead;
	unsigned int PriorityTableCount;
	const unsigned int PriorityTableSize = 6;

public:
	// ------- STATIC ----------------
	
	static Handle			   table_handle;
	

};

#endif


// End of File 
