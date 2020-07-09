#include "Playlist.h"
#include "VoiceManager.h"
#include "ScriptManager.h"
#include "XAudio2Manager.h"


Playlist::Playlist()
	:ID(SoundId::UNINITIALIZED), pVoice(nullptr), pScript(nullptr), pCurrentBuff(nullptr)
{
	
}

Playlist::~Playlist() {


}

bool Playlist::Update() {

	//Check buffer is done
	if (this->pVoice->StreamEnd() && this->pCurrentBuff != nullptr) {

		//Get next buffer in list
		this->pCurrentBuff = this->pCurrentBuff->GetScriptNext();

		//if another buffer in list
		if (this->pCurrentBuff != nullptr) {
			this->pVoice->SetBuffer(this->pCurrentBuff);
			this->pVoice->SubmitBuffer();
		}
		else {
			//sound done playing
			return true;
			
		}
	}

	return false;
}

void Playlist::Play()
{
	XAudio2Manager::PlayVoice(this->pVoice);
}

void Playlist::Stop()
{
	XAudio2Manager::StopVoice(this->pVoice->GetXAudio2Voice());
}

void Playlist::ChangePan(float PanIn)
{
	XAudio2Manager::SetPan(this->pVoice->GetXAudio2Voice(), PanIn);
}

void Playlist::ChangeVolume(float VolIn)
{
	XAudio2Manager::SetVolume(this->pVoice->GetXAudio2Voice(), VolIn);
}

//void Playlist::Reset()
//{
//	//Set buffer back to beginning
//	this->pCurrentBuff = this->pScript->GetHead();
//
//	this->pVoice->SetBuffer(this->pCurrentBuff);
//	this->pVoice->SubmitBuffer();
//}

AudioBuffer* Playlist::GetCurrentBuffer()
{
	assert(this->pCurrentBuff != nullptr);
	return this->pCurrentBuff;
}

AudioVoice* Playlist::GetVoice()
{
	assert(this->pVoice != nullptr);
	return this->pVoice;
}

void Playlist::AssociateVoice()
{
	//create and associate voice
	this->pVoice = VoiceManager::CreateVoice(this->ID);
	assert(this->pVoice != nullptr);

	this->pVoice->SetXAudio2Voice(XAudio2Manager::CreateVoice(this->pCurrentBuff->GetFormat(), this->pVoice->GetCallBack()));
	this->pVoice->SetBuffer(this->pCurrentBuff);
	this->pVoice->SubmitBuffer();
}

void Playlist::AssociateScript()
{
	//find script
	this->pScript = ScriptManager::FindScript(this->ID);
	assert(this->pScript != nullptr);

	//set curr buff to script head
	this->pCurrentBuff = this->pScript->GetHead();
	assert(this->pCurrentBuff != nullptr);
}

void Playlist::GetID(SoundId& IDIn)
{
	IDIn = this->ID;
}

//void Playlist::SetID(SoundId& IDIn)
//{
//	this->ID = IDIn;
//}

void Playlist::Set(SoundId IDIn)
{
	this->ID = IDIn;
	
}

void Playlist::Dump()
{
	Trace::out("   Name: %d (%p) \n", this->ID, this);
}

void Playlist::Wash()
{
	this->ID = SoundId::UNINITIALIZED;
	this->pVoice = nullptr;
	this->pScript = nullptr;
	this->pCurrentBuff = nullptr;
}


