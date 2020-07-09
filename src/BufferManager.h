#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include "AudioBuffer.h"
#include "Manager.h"

class BufferManager : public Manager
{

private:

	BufferManager(int reserveNum = 3, int reserveGrow = 1);
	BufferManager() = delete;
	BufferManager(const BufferManager&) = delete;
	BufferManager& operator = (const BufferManager&) = delete;
	~BufferManager();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destory();

	static AudioBuffer* CreateBuffer(SoundId IDin);
	static AudioBuffer* FindBuffer(SoundId IDin);
	static void DestroyBuffer(AudioBuffer* Nodein);

	static void Dump();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static BufferManager* GetInstance();
	

	//Data
	static BufferManager* poInstance;
	AudioBuffer* poNodeCompare;

	
};

#endif BUFFER_MANAGER_H