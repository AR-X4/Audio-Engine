#ifndef SET_VOLUME_COMMAND_H
#define SET_VOLUME_COMMAND_H

#include "Message.h"
#include "Sound.h"

class SetVolumeCommand : public Message
{

public:
	SetVolumeCommand(Sound* pSoundIn, Time TriggTime, float VolIn);
	~SetVolumeCommand();

	SetVolumeCommand() = delete;
	SetVolumeCommand(const SetVolumeCommand&) = delete;
	SetVolumeCommand& operator=(const SetVolumeCommand&) = delete;

	void Execute() override;

private:

	//data
	Sound* pSound;
	float NewVol;
	
};

#endif