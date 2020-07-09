#include "AudioVoice.h"


AudioVoice::AudioVoice()
	:ID(SoundId::UNINITIALIZED), pVoice(nullptr), pCurrentBuffer(nullptr), pCallback(nullptr)
{
	
	
}

AudioVoice::~AudioVoice() 
{
	this->Wash();
}

bool AudioVoice::StreamEnd() {

	bool out = false;

	if (this->pCallback->finished == true) {
		out = this->pCallback->finished;
		this->pCallback->Reset();
	}

	return out;
}

void AudioVoice::SetXAudio2Voice(IXAudio2SourceVoice* pVoiceIn) {

	assert(pVoiceIn != nullptr);

	this->pVoice = pVoiceIn;

}

IXAudio2SourceVoice* AudioVoice::GetXAudio2Voice() {

	assert(this->pVoice != nullptr);
	return this->pVoice;

}

void AudioVoice::SetBuffer(AudioBuffer* BufferIn) {
	assert(BufferIn != nullptr);


	this->pCurrentBuffer = BufferIn;

}

AudioBuffer* AudioVoice::GetCurrentBuffer() {

	assert(this->pCurrentBuffer != nullptr);
	return this->pCurrentBuffer;

}

VoiceCallback* AudioVoice::GetCallBack() {

	return this->pCallback;
}

void AudioVoice::SubmitBuffer() {

	assert(this->pCurrentBuffer != nullptr);

	this->pVoice->SubmitSourceBuffer(&this->pCurrentBuffer->GetXAudio2Buffer());

}

void AudioVoice::GetID(SoundId& IDIn)
{
	IDIn = this->ID;
}

//void AudioVoice::SetID(SoundId& IDIn)
//{
//	this->ID = IDIn;
//}

void AudioVoice::Set(SoundId IDIn)
{
	this->ID = IDIn;
	this->pCallback = new VoiceCallback();
}

void AudioVoice::Dump()
{
	Trace::out("   Name: %d (%p) \n", this->ID, this);
}

void AudioVoice::Wash()
{
	this->ID = SoundId::UNINITIALIZED;

	delete this->pCallback;
	this->pCallback = nullptr;

	if (this->pVoice != nullptr) {
		this->pVoice->DestroyVoice();
		this->pVoice = nullptr;
	}

	this->pCurrentBuffer = nullptr;
}

