#ifndef AUDIO_VOICE_H
#define AUDIO_VOICE_H

#include "XAudio2Wrapper.h"
#include "AudioBuffer.h"
#include "VoiceCallback.h"
#include "DLink.h"

class AudioVoice : public DLink
{
public:

	//big four
	AudioVoice();
	~AudioVoice();
	AudioVoice(const AudioVoice&) = delete;
	AudioVoice& operator=(const AudioVoice&) = delete;


	bool StreamEnd();

	void SetBuffer(AudioBuffer* BufferIn);
	void SetXAudio2Voice(IXAudio2SourceVoice* pVoiceIn);

	IXAudio2SourceVoice* GetXAudio2Voice();
	AudioBuffer* GetCurrentBuffer();
	VoiceCallback* GetCallBack();

	void SubmitBuffer();

	void GetID(SoundId& IDIn);
	//void SetID(SoundId& IDIn);

	void Set(SoundId IDIn);
	void Dump();
	void Wash();

private:
	//data
	SoundId	ID;
	IXAudio2SourceVoice* pVoice;
	AudioBuffer* pCurrentBuffer;
	VoiceCallback* pCallback;

};

#endif
