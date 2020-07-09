#include "PrintPriorityCommand.h"
#include "SoundManager.h"

PrintPriorityCommand::PrintPriorityCommand(Time TriggTime)
{
	this->SetTriggerTime(TriggTime);
}

PrintPriorityCommand::~PrintPriorityCommand()
{
}

void PrintPriorityCommand::Execute()
{
	SoundManager::DumpPriorityTable();
}
