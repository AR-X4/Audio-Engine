#ifndef COMMAND_H
#define COMMAND_H

//Command Pattern Base Class

class Command
{

public:
	Command() {}
	virtual  ~Command() {}

	Command(const Command&) = delete;
	Command& operator=(const Command&) = delete;

	virtual void Execute() = 0;

};

#endif