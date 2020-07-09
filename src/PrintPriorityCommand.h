#ifndef PRINT_PRIORITY_COMMAND_H
#define PRINT_PRIORITY_COMMAND_H

#include "Message.h"

class PrintPriorityCommand : public Message
{


public:
	PrintPriorityCommand(Time TriggTime);
	~PrintPriorityCommand();

	PrintPriorityCommand() = delete;
	PrintPriorityCommand(const PrintPriorityCommand&) = delete;
	PrintPriorityCommand& operator=(const PrintPriorityCommand&) = delete;

	void Execute() override;

private:

	//data


};

#endif