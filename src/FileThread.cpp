#include "FileThread.h"
#include "Message.h"
#include "SoundManager.h"

void File_Main(bool& KillSwitch)
{

	//-----------------------------------
	//----------File Main Loop----------
	//-----------------------------------
	while (KillSwitch) {

		Message* pMsg;

		if (SoundManager::GetG2F()->PopFront(pMsg) == true)
		{
			pMsg->Execute();
			delete pMsg;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	}

	

	Trace::out("--->File Thread Killed\n\n");
}
