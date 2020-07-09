#include "StopAllSoundsCommand.h"
#include "SoundManager.h"

StopAllSoundsCommand::StopAllSoundsCommand(Time TriggTime)
{
	this->SetTriggerTime(TriggTime);

}

StopAllSoundsCommand::~StopAllSoundsCommand()
{
}

void StopAllSoundsCommand::Execute()
{


	SoundManager::StopAllSounds();


}
