#ifndef VOICE_MANAGER_H
#define VOICE_MANAGER_H

#include "AudioVoice.h"
#include "SoundCallRegistry.h"
#include "Manager.h"

class VoiceManager : public Manager
{

private:

	VoiceManager(int reserveNum = 3, int reserveGrow = 1);
	VoiceManager() = delete;
	VoiceManager(const VoiceManager&) = delete;
	VoiceManager& operator = (const VoiceManager&) = delete;
	~VoiceManager();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static AudioVoice* CreateVoice(SoundId IDin);
	//static AudioVoice* FindVoice(SoundId IDin);
	static void DestroyVoice(AudioVoice* Nodein);

	static void Dump();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static VoiceManager* GetInstance();

	//DATA
	static VoiceManager* poInstance;
	AudioVoice* poNodeCompare;


};

#endif