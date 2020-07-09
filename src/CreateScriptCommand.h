#ifndef CREATE_SCRIPT_COMMAND_H
#define CREATE_SCRIPT_COMMAND_H


#include "Message.h"
#include "SoundCallRegistry.h"

class CreateScriptCommand : public Message
{

public:
	CreateScriptCommand(SoundId SoundIdIn);
	~CreateScriptCommand();

	CreateScriptCommand() = delete;
	CreateScriptCommand(const CreateScriptCommand&) = delete;
	CreateScriptCommand& operator=(const CreateScriptCommand&) = delete;

	void Execute() override;

private:
	SoundId ID;

};

#endif
