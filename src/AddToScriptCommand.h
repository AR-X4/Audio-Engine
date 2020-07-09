#ifndef ADD_TO_SCRIPT_COMMAND_H
#define ADD_TO_SCRIPT_COMMAND_H

#include "Message.h"
#include "SoundCallRegistry.h"


class AddToScriptCommand : public Message
{
public:
	AddToScriptCommand(SoundId ScriptIDIn, SoundId BufferIDIn);
	~AddToScriptCommand();

	AddToScriptCommand() = delete;
	AddToScriptCommand(const AddToScriptCommand&) = delete;
	AddToScriptCommand& operator=(const AddToScriptCommand&) = delete;

	void Execute() override;

private:
	SoundId ScriptID;
	SoundId BufferID;


};

#endif