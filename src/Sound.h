//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SOUND_H
#define SOUND_H

#include "Handle.h"
#include "SoundCallRegistry.h"
#include "XAudio2Wrapper.h"
#include "DLink.h"
#include "ASound.h"
#include "Timer.h"

//class Handle;

class Sound : public DLink
{
public:

	// defaults
	Sound();
	Sound(const Sound&);
	Sound& operator=(const Sound&);
	~Sound();

	//---Commands---
	const Handle::Status Play(Time TriggTime);
	const Handle::Status Stop(Time TriggTime);
	//Handle::Status Pause();
	//Handle::Status UnPause();
	const Handle::Status NewPan(const float PanIn, Time TriggTime);
	const Handle::Status NewVolume(const float PanIn, Time TriggTime);
	const Handle::Status PrintPlayTime(Time TriggTime);
	
	//Handle::Status SetLooping();

	//---Accessors---
	const Handle::Status SetVolume(const float VolumeIn);
	const Handle::Status GetVolume(float& VolIn);
	const Handle::Status SetPan(const float PanIn);
	const Handle::Status GetPan(float& PanIn);
	//const Handle::Status SetPitch();

	SoundId& GetID();  //doesn't need handle protec, only called when creating sound...so always valid
	void SetASound(ASound* pIn);//doesn't need handle protec, only called when creating sound...so always valid
	int GetHandleID();//lock?
	ASound* GetASound();//doesn't need handle protec, only called in handle protected commands...?

	//---Called in Manager---
	void Set(SoundId IDIn, int SoundPriority = 0);
	void Dump();
	void Wash();

	//void RemoveFromPriorityTable();
	//Handle::Status GetTimeInMS(int& timeInMS);

	//bool AddToPriorityTable();//doesn't need handle protec, only called inside Play()
	//---Priority Table Methods---
	void SetPriorityNext(Sound* pSoundIn);
	void SetPriorityPrev(Sound* pSoundIn);
	Sound* GetPriorityNext();
	Sound* GetPriorityPrev();
	void StartTimer();
	int GetPlayTime();

	unsigned int GetPriority() const;

private:


	//Data
	SoundId	ID;
	ASound* pASound;
	float Volume;
	float Pan;
	unsigned int Priority;

	Time StartTime;
	Sound* pPriorityNext;
	Sound* pPriorityPrev;

	Handle handle;
};

#endif


// End of File 
