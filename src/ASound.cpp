
#include "CircularData.h"
#include "ASoundManager.h"
#include "ASound.h"
#include "PlaylistManager.h"
#include "Sound.h"

#include "UserCallback.h"

ASound::ASound()
	: ID(SoundId::UNINITIALIZED), pPlaylist(nullptr), pSound(nullptr), pCallback(nullptr)
{
}

ASound::ASound(const ASound& tmp)
	:ID(tmp.ID), pPlaylist(tmp.pPlaylist), pSound(tmp.pSound)
{
	
}

const ASound& ASound::operator=(const ASound& tmp)
{
	//....
	this->pPlaylist = tmp.pPlaylist;

	return *this;
}

ASound::~ASound()
{
	if (this->pCallback != nullptr) {
		delete this->pCallback;
	}
}

//void ASound::ResetPlaylist()
//{
//	this->pPlaylist->Reset();
//}

Playlist* ASound::GetPlaylist()
{
	assert(this->pPlaylist != nullptr);
	return this->pPlaylist;
}

void ASound::AssociatePlaylist()
{
	this->pPlaylist = PlaylistManager::CreatePlaylist(this->ID);
	assert(this->pPlaylist != nullptr);

	this->pPlaylist->AssociateScript();
	this->pPlaylist->AssociateVoice();
}

Sound* ASound::GetSound()
{
	assert(this->pSound != nullptr);
	return this->pSound;
}

void ASound::Play()
{
	this->pPlaylist->Play();
}

void ASound::Stop()
{
	this->pPlaylist->Stop();
}

bool ASound::Update()
{
	return this->pPlaylist->Update();
}

void ASound::ChangePan(float PanIn)
{
	this->pPlaylist->ChangePan(PanIn);
}

void ASound::ChangeVolume(float VolIn)
{
	this->pPlaylist->ChangeVolume(VolIn);
}

void ASound::GetID(SoundId& IDIn)
{
	IDIn = this->ID;
}

void ASound::SetCallBack(UserCallback* pCallbackIn)
{
	this->pCallback = pCallbackIn;
}

UserCallback* ASound::GetCallback()
{
	return this->pCallback;
}

//void ASound::SetID(SoundId& IDIn)
//{
//	this->ID = IDIn;
//}

void ASound::Set(Sound* pSoundIn)
{
	//SoundId Id;
	//pSoundIn->GetID(Id);

	this->ID = pSoundIn->GetID();

	this->pSound = pSoundIn;
}

void ASound::Dump()
{
	Trace::out("   Name: %d (%p) \n", this->ID, this);
}

void ASound::Wash()
{
	this->ID = SoundId::UNINITIALIZED;
	this->pPlaylist = nullptr;
	this->pSound = nullptr;

	//if (this->pCallback != nullptr) {
		//delete this->pCallback;
		this->pCallback = nullptr;
	//}
}



// End of File 
