#include "PlaySoundCommand.h"
#include "SoundManager.h"
#include "StopSoundCommand.h"


PlaySoundCommand::PlaySoundCommand(Sound* pSoundIn, Time TriggTime)
	:pSound(pSoundIn)
{
	this->SetTriggerTime(TriggTime);
}

PlaySoundCommand::~PlaySoundCommand() {

}

void PlaySoundCommand::Execute() {

	
	
	if (SoundManager::AddToPriorityList(this->pSound)) {

		ASound* pASnd = this->pSound->GetASound();

		pASnd->Play();

		Trace::out("Playing Voice\n\n");

	}
	else {
		//else no room in table, dont play
		Trace::out("PLAY CANCELLED\n\n");
		//destroy sound..?
		SoundManager::SendAudioCommand(new StopSoundCommand(this->pSound));
		
	}


}

