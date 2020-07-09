#include "SetPanCommand.h"


SetPanCommand::SetPanCommand(Sound* pSoundIn, Time TriggTime, float PanIn)
	:pSound(pSoundIn), newPan(PanIn)
{
	this->SetTriggerTime(TriggTime);
}

SetPanCommand::~SetPanCommand() {

}

void SetPanCommand::Execute() {

	ASound* pASnd = this->pSound->GetASound();

	assert(Handle::Status::SUCCESS == this->pSound->SetPan(this->newPan));
	pASnd->ChangePan(this->newPan);
	
	Trace::out("Pan Set %f\n\n", this->newPan);

}

