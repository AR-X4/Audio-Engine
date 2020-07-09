#include "SetVolumeCommand.h"


SetVolumeCommand::SetVolumeCommand(Sound* pSoundIn, Time TriggTime, float VolIn)
	:pSound(pSoundIn), NewVol(VolIn)
{
	this->SetTriggerTime(TriggTime);
}


SetVolumeCommand::~SetVolumeCommand() {

}


void SetVolumeCommand::Execute() {

	ASound* pASnd = this->pSound->GetASound();

	assert(Handle::Status::SUCCESS == this->pSound->SetVolume(this->NewVol));
	pASnd->ChangeVolume(this->NewVol);
	
	Trace::out("Volume Set %f\n\n", this->NewVol);

}

