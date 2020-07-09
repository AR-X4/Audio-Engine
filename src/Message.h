#ifndef MESSAGE_H
#define MESSAGE_H

#include "Command.h"
#include "Time.h"

class Message : public Command 
{
public:

	Message() {}
	virtual ~Message() {}
	Message(const Message&) = delete;
	Message& operator=(const Message&) = delete;

	virtual void Execute() = 0;

	Time GetTriggerTime() { return this->TriggerTime; }

protected:
	void SetTriggerTime(Time TriggerTimeIn) { this->TriggerTime = TriggerTimeIn; }

private:

	//data
	Time TriggerTime = Time(Duration::TIME_ZERO);

};



#endif
