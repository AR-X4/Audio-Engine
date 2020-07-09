#include "StopSoundCommand.h"
#include "XAudio2Manager.h"
#include "ASoundManager.h"
#include "VoiceManager.h"
#include "PlaylistManager.h"
#include "SoundManager.h"


StopSoundCommand::StopSoundCommand(Sound* pSoundIn, Time TriggTime)
	:pSound(pSoundIn)
{
	this->SetTriggerTime(TriggTime);
}


StopSoundCommand::~StopSoundCommand() {

}


void StopSoundCommand::Execute() {

	ASound* pASnd = this->pSound->GetASound();
	pASnd->Stop();

	Trace::out("Stopped Voice\n\n");

	//destroy sound
	SoundManager::DestroySound(pASnd->GetSound());
	//Destroy voice
	VoiceManager::DestroyVoice(pASnd->GetPlaylist()->GetVoice());
	//Destroy playlist
	PlaylistManager::DestroyPlaylist(pASnd->GetPlaylist());
	//Destroy ASound
	ASoundManager::DestroyASound(pASnd);

}

