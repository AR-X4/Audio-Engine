#ifndef CREATE_SOUND_COMMAND_H
#define CREATE_SOUND_COMMAND_H

#include "Message.h"
#include "Sound.h"
#include "UserCallback.h"

class CreateSoundCommand : public Message
{


public:
	CreateSoundCommand(Sound* pSoundIn, UserCallback* pCallbackIn);
	~CreateSoundCommand();

	CreateSoundCommand() = delete;
	CreateSoundCommand(const CreateSoundCommand&) = delete;
	CreateSoundCommand& operator=(const CreateSoundCommand&) = delete;

	void Execute() override;

private:

	//data
	Sound* pSound;
	UserCallback* pCallback;

};

#endif