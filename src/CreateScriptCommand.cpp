#include "CreateScriptCommand.h"
#include "ScriptManager.h"

CreateScriptCommand::CreateScriptCommand(SoundId SoundIdIn)
	:ID(SoundIdIn)
{

}

CreateScriptCommand::~CreateScriptCommand()
{

}

void CreateScriptCommand::Execute()
{
	ScriptManager::CreateScript(this->ID);
}
