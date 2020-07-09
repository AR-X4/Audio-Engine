#ifndef AUDIO_SCRIPT_H
#define AUDIO_SCRIPT_H

#include "AudioBuffer.h"
#include "SoundCallRegistry.h"

class AudioScript : public DLink
{
public:
	AudioScript();
	AudioScript(const AudioScript&) = delete;
	AudioScript& operator = (const AudioScript&) = delete;
	~AudioScript();

	void AddBuffer(SoundId IDIn);
	AudioBuffer* GetHead();

	void GetID(SoundId& IDIn);
	//void SetID(SoundId& IDIn);

	void Set(SoundId IDIn);
	void Dump();
	void Wash();

private:

	SoundId	ID;
	AudioBuffer* pBuffHead;

};

#endif