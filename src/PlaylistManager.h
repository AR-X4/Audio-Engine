#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include "Playlist.h"
#include "SoundCallRegistry.h"
#include "Manager.h"

class PlaylistManager : public Manager
{

private:
	PlaylistManager(int reserveNum = 3, int reserveGrow = 1);
	PlaylistManager() = delete;
	PlaylistManager(const PlaylistManager&) = delete;
	PlaylistManager& operator = (const PlaylistManager&) = delete;
	~PlaylistManager();

public:
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Playlist* CreatePlaylist(SoundId IDin);
	//static Playlist* FindPlaylist(SoundId IDin);
	static void DestroyPlaylist(Playlist* Nodein);

	static void Dump();

protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

private:
	static PlaylistManager* GetInstance();
	
	//DATA
	static PlaylistManager* poInstance;
	Playlist* poNodeCompare;

};

#endif