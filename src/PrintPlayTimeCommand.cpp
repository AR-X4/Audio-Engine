#include "PrintPlayTimeCommand.h"


PrintPlayTimeCommand::PrintPlayTimeCommand(Sound* pSoundIn, Time TriggTime)
	:pSound(pSoundIn)
{
	this->SetTriggerTime(TriggTime);
}

PrintPlayTimeCommand::~PrintPlayTimeCommand() {

}

void PrintPlayTimeCommand::Execute() {

	//int timeInMS;
	//this->pSound->GetTimeInMS(timeInMS);
	Trace::out("       Time: %ds \n", this->pSound->GetPlayTime()/1000);

}