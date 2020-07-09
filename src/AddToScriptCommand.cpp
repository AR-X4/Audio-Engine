#include "AddToScriptCommand.h"
#include "ScriptManager.h"

AddToScriptCommand::AddToScriptCommand(SoundId ScriptIDIn, SoundId BufferIDIn)
	:ScriptID(ScriptIDIn), BufferID(BufferIDIn)
{
}

AddToScriptCommand::~AddToScriptCommand()
{
}

void AddToScriptCommand::Execute()
{
	AudioScript* pScript = ScriptManager::FindScript(this->ScriptID);
	assert(pScript != nullptr);

	pScript->AddBuffer(this->BufferID);

}
