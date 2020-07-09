#ifndef STOP_SOUND_COMMAND_H
#define STOP_SOUND_COMMAND_H

#include "Message.h"
#include "Sound.h"

class StopSoundCommand : public Message
{


public:
	StopSoundCommand(Sound* pSoundIn, Time TriggTime = Time());
	~StopSoundCommand();

	StopSoundCommand() = delete;
	StopSoundCommand(const StopSoundCommand&) = delete;
	StopSoundCommand& operator=(const StopSoundCommand&) = delete;

	void Execute() override;

private:

	//data
	Sound* pSound;

};

#endif