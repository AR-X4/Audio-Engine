#include "AudioBuffer.h"


AudioBuffer::AudioBuffer()
	:ID(SoundId::UNINITIALIZED), XAudio2_Buffer({}), wfx({}), pScriptNext(nullptr)
{
}

AudioBuffer::~AudioBuffer() {
	
	this->Wash();
}

AudioBuffer::AudioBuffer(const AudioBuffer& in) {

	this->ID = in.ID;
	this->XAudio2_Buffer = in.XAudio2_Buffer;
	this->wfx = in.wfx;
	this->pScriptNext = in.pScriptNext;
}


AudioBuffer& AudioBuffer::operator=(const AudioBuffer& in) {

	this->ID = in.ID;
	this->XAudio2_Buffer = in.XAudio2_Buffer;
	this->wfx = in.wfx;
	this->pScriptNext = in.pScriptNext;

	return *this;
}

XAUDIO2_BUFFER& AudioBuffer::GetXAudio2Buffer() {

	return this->XAudio2_Buffer;
}

WAVEFORMATEXTENSIBLE& AudioBuffer::GetFormat() {

	return this->wfx;
}

void AudioBuffer::SetScriptNext(AudioBuffer* pIn)
{
	this->pScriptNext = pIn;

}

AudioBuffer* AudioBuffer::GetScriptNext()
{
	return this->pScriptNext;
}

void AudioBuffer::GetID(SoundId& IDIn)
{
	IDIn = this->ID;
}

//void AudioBuffer::SetID(const SoundId& IDIn)
//{
//	this->ID = IDIn;
//}

void AudioBuffer::Set(SoundId IDIn)
{
	this->ID = IDIn;
}

void AudioBuffer::Dump()
{
	Trace::out("   Name: %d (%p) \n", this->ID, this);
}

void AudioBuffer::Wash()
{
	this->ID = SoundId::UNINITIALIZED;

	delete this->XAudio2_Buffer.pAudioData;
	this->XAudio2_Buffer = {};

	this->wfx = {};
	this->pScriptNext = nullptr;

}


