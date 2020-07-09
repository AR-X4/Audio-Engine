#ifndef ASOUND_H
#define ASOUND_H

#include "Handle.h"
#include "SoundCallRegistry.h"
#include "Playlist.h"
#include "DLink.h"


class Sound;
class UserCallback;

class ASound : public DLink
{
public:

	// defaults
	ASound();
	ASound(const ASound&);
	const ASound& operator=(const ASound&);
	~ASound();

	//commands
	Playlist* GetPlaylist();

	void AssociatePlaylist();

	Sound* GetSound();

	void Play();
	void Stop();

	bool Update();

	void ChangePan(float PanIn);
	void ChangeVolume(float VolIn);

	//Accessors
	void GetID(SoundId& IDIn);

	void SetCallBack(UserCallback* pCallbackIn);
	UserCallback* GetCallback();
	
	void Set(Sound* pSoundIn);
	void Dump();
	void Wash();

private:

	SoundId	ID;
	Playlist* pPlaylist;
	Sound* pSound;
	UserCallback* pCallback;

};

#endif