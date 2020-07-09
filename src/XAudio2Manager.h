#ifndef XAUDIO2MANAGER_H
#define XAUDIO2MANAGER_H

#include "XAudio2Wrapper.h"
#include "File.h"
#include "AudioBuffer.h"


//forward delcare
class VoiceCallback;
class AudioVoice;

class XAudio2Manager
{
	//methods
public:
	
	static void Create();
	static void Destroy();

	XAudio2Manager(const XAudio2Manager&) = delete;
	XAudio2Manager& operator = (const XAudio2Manager&) = delete;
	~XAudio2Manager();

	static void LoadWaveFile(const char* FileName, AudioBuffer& audioBuffer);
	static IXAudio2SourceVoice* CreateVoice(WAVEFORMATEXTENSIBLE wfx, VoiceCallback* pCallback);

	static void PlayVoice(AudioVoice* pVoiceIn);
	static void PauseVoice(IXAudio2SourceVoice* InVoice);
	static void UnPauseVoice(IXAudio2SourceVoice* InVoice);
	static void StopVoice(IXAudio2SourceVoice* InVoice);

	static void SetVolume(IXAudio2SourceVoice* InVoice, const float& volume);
	static void SetPitch(IXAudio2SourceVoice* InVoice, const float& pitch);
	static void SetLooping(bool bLoop, XAUDIO2_BUFFER& Buffer);
	static void SetPan(IXAudio2SourceVoice* InVoice, const float& pan);

	static float GetVolume(IXAudio2SourceVoice* InVoice);

private:

	//Singleton Methods
	static XAudio2Manager* GetInstance();
	XAudio2Manager();

	//helpers
	void Init();
	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

	//data
	IXAudio2* pXAudio2Engine;
	IXAudio2MasteringVoice* pMasterVoice;

};



#endif