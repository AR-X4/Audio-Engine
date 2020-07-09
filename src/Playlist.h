#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "AudioVoice.h"
#include "AudioBuffer.h"
#include "SoundCallRegistry.h"
#include "AudioScript.h"
#include "CircularData.h"

class Playlist : public DLink
{

public:

	Playlist();
	Playlist(const Playlist&) = delete;
	Playlist& operator = (const Playlist&) = delete;
	~Playlist();

	bool Update();

	void Play();
	void Stop();

	void ChangePan(float PanIn);
	void ChangeVolume(float VolIn);

	AudioBuffer* GetCurrentBuffer();
	AudioVoice* GetVoice();

	void AssociateVoice();
	void AssociateScript();

	void GetID(SoundId& IDIn);
	//void SetID(SoundId& IDIn);

	void Set(SoundId IDIn);
	void Dump();
	void Wash();

private:
	//data
	SoundId	ID;
	AudioVoice* pVoice;
	AudioScript* pScript;
	AudioBuffer* pCurrentBuff;
	
	
};

#endif