#ifndef PRINT_PLAYTIME_COMMAND_H
#define PRINT_PLAYTIME_COMMAND_H

#include "Message.h"
#include "Sound.h"

class PrintPlayTimeCommand : public Message
{


public:
	PrintPlayTimeCommand(Sound* pSoundIn, Time TriggTime);
	~PrintPlayTimeCommand();

	PrintPlayTimeCommand() = delete;
	PrintPlayTimeCommand(const PrintPlayTimeCommand&) = delete;
	PrintPlayTimeCommand& operator=(const PrintPlayTimeCommand&) = delete;

	void Execute() override;

private:

	//data
	Sound* pSound;

};

#endif