#ifndef SET_PAN_COMMAND_H
#define SET_PAN_COMMAND_H

#include "Message.h"
#include "Sound.h"

class SetPanCommand : public Message
{


public:
	SetPanCommand(Sound* pSoundIn, Time TriggTime, float PanIn);
	~SetPanCommand();

	SetPanCommand() = delete;
	SetPanCommand(const SetPanCommand&) = delete;
	SetPanCommand& operator=(const SetPanCommand&) = delete;

	void Execute() override;

private:

	//data
	Sound* pSound;
	float newPan;

};

#endif