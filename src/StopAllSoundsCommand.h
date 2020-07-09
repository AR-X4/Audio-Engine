#ifndef STOP_ALL_SOUNDS_COMMAND_H
#define STOP_ALL_SOUNDS_COMMAND_H

#include "Message.h"


class StopAllSoundsCommand : public Message
{


public:
	StopAllSoundsCommand(Time TriggTime = Time());
	~StopAllSoundsCommand();

	StopAllSoundsCommand() = delete;
	StopAllSoundsCommand(const StopAllSoundsCommand&) = delete;
	StopAllSoundsCommand& operator=(const StopAllSoundsCommand&) = delete;

	void Execute() override;



};

#endif