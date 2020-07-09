#ifndef PLAY_SOUND_COMMAND_H
#define PLAY_SOUND_COMMAND_H

#include "Message.h"
#include "Sound.h"

class PlaySoundCommand : public Message
{

public:
	PlaySoundCommand(Sound* pSoundIn, Time TriggTime);
	~PlaySoundCommand();

	PlaySoundCommand() = delete;
	PlaySoundCommand(const PlaySoundCommand&) = delete;
	PlaySoundCommand& operator=(const PlaySoundCommand&) = delete;

	void Execute() override;

private:

	//data
	Sound* pSound;

};

#endif