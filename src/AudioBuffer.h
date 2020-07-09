#ifndef AUDIO_BUFFER_H
#define AUDIO_BUFFER_H

#include "XAudio2Wrapper.h"
#include "DLink.h"
#include "SoundCallRegistry.h"

class AudioBuffer : public DLink
{
public:
	//big four
	AudioBuffer();
	AudioBuffer(const AudioBuffer& in);
	AudioBuffer& operator=(const AudioBuffer& in);
	~AudioBuffer();

	XAUDIO2_BUFFER& GetXAudio2Buffer();
	WAVEFORMATEXTENSIBLE& GetFormat();

	void SetScriptNext(AudioBuffer* pIn);
	AudioBuffer* GetScriptNext();


	void GetID(SoundId& IDIn);
	//void SetID(const SoundId& IDIn);

	void Set(SoundId IDIn);
	void Dump();
	void Wash();

	//data
private:
	SoundId	ID;

	XAUDIO2_BUFFER XAudio2_Buffer;
	WAVEFORMATEXTENSIBLE wfx;
	


	AudioBuffer* pScriptNext;
	
	
};


#endif
