#ifndef TIME_EVENT_H
#define	TIME_EVENT_H

#include "DLink.h"
#include "Command.h"
#include "Time.h"


class TimeEvent : public DLink
{
public:
	enum ID
	{
		Demo1_A = 0x66660000,
		Demo1_B,
		Demo1_C,
		Uninitialized
	};

public:

	TimeEvent();
	TimeEvent(const TimeEvent&) = delete;
	TimeEvent& operator = (const TimeEvent&) = delete;
	~TimeEvent();

	void SetID(ID event_id);
	TimeEvent::ID GetID();

	Time GetTriggerTime();
	void Process();

	void Set(Command* pCommand, Time deltaTimeToTrigger);

	void Dump();
	void Wash();


private:
	void PrivClear();

	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

private:
	Command* pCommand;
	ID		id;

	Time	TriggerTime;
	Time	DeltaTime;
};


#endif

// --- End of File ---
