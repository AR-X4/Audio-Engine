#ifndef ASOUND_MANAGER_H
#define ASOUND_MANAGER_H

#include "CircularData.h"
#include "Manager.h"
#include "ASound.h"
#include "Message.h"


class ASoundManager : public Manager
{
private:
	// Defaults
	ASoundManager(int reserveNum = 3, int reserveGrow = 1);
	ASoundManager(const ASoundManager&) = delete;
	ASoundManager& operator = (const ASoundManager&) = delete;
	ASoundManager() = delete;
	~ASoundManager();

public:
	// Public methods:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	//static void SendCommand(Message* pMsg);

	static ASound* CreateASound(Sound* pSoundIn);
	//static ASound* FindASound(SoundId IDin);
	static void DestroyASound(ASound* Nodein);

	static void Dump();
	static void Update();
	

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static ASoundManager* GetInstance();

	//DATA
	static ASoundManager* poInstance;
	//ASound* poNodeCompare;

};

#endif


// End of File 
