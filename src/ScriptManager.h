#ifndef SCRIPT_MANAGER_H
#define SCRIPT_MANAGER_H

#include "AudioScript.h"
#include "SoundCallRegistry.h"
#include "Manager.h"

class ScriptManager : public Manager
{

private:
	ScriptManager(int reserveNum = 3, int reserveGrow = 1);
	ScriptManager() = delete;
	ScriptManager(const ScriptManager&) = delete;
	ScriptManager& operator = (const ScriptManager&) = delete;
	~ScriptManager();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static AudioScript* CreateScript(SoundId IDin);
	static AudioScript* FindScript(SoundId IDin);
	static void DestroyScript(AudioScript* Nodein);

	static void Dump();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static ScriptManager* GetInstance();

	//DATA
	static ScriptManager* poInstance;
	AudioScript* poNodeCompare;


};

#endif