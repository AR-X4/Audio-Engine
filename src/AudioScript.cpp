#include "AudioScript.h"
#include "BufferManager.h"

AudioScript::AudioScript()
	:ID(SoundId::UNINITIALIZED), pBuffHead(nullptr)
{
}

AudioScript::~AudioScript()
{
}

void AudioScript::AddBuffer(SoundId IDIn)
{
	AudioBuffer* pIn = BufferManager::FindBuffer(IDIn);
	assert(pIn != nullptr);
	
	// add node
	if (this->pBuffHead == nullptr)
	{
		// push to the front
		this->pBuffHead = pIn;
		//pIn->SetScriptNext(nullptr);
	}
	else
	{
		// push to front
		pIn->SetScriptNext(this->pBuffHead);
		// update head
		this->pBuffHead = pIn;
	}
	assert(this->pBuffHead != nullptr);
}
	
	

AudioBuffer* AudioScript::GetHead()
{
	return this->pBuffHead;
}

void AudioScript::GetID(SoundId& IDIn)
{
	IDIn = this->ID;
}

//void AudioScript::SetID(SoundId& IDIn)
//{
//	this->ID = IDIn;
//}

void AudioScript::Set(SoundId IDIn)
{
	this->ID = IDIn;
}

void AudioScript::Dump()
{
	Trace::out("   Name: %d (%p) \n", this->ID, this);
}

void AudioScript::Wash()
{
	this->ID = SoundId::UNINITIALIZED;
	this->pBuffHead = nullptr;
}
